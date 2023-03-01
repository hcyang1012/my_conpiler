
#include <glog/logging.h>

#include <include/ast.hpp>
#include <include/lexer.hpp>
#include <include/parser.hpp>
#include <include/token.hpp>
#include <memory>

namespace my_compiler {
Parser::Parser(Lexer& lexer) : lexer_(lexer) {
  current_token_ = lexer_.NextToken();
}

std::shared_ptr<Token> Parser::Eat(const Token::Type type) {
  if (current_token_->GetType() != type) {
    LOG(FATAL) << "[Parser]: Unexpected token : " << *current_token_
               << ", was expecting: " << *Token::Build(type);
  }

  current_token_ = lexer_.NextToken();
  return current_token_;
}

std::shared_ptr<Ast> Parser::Parse() { return ParseCompound(); }

std::shared_ptr<AstCompound> Parser::ParseCompound() {
  bool should_close = false;
  if (current_token_->GetType() == Token::Type::TOKEN_LBRACE) {
    Eat(Token::Type::TOKEN_LBRACE);
    should_close = true;
  }
  auto compound = AstCompound::Build();
  while (current_token_->GetType() != Token::Type::TOKEN_EOF &&
         current_token_->GetType() != Token::Type::TOKEN_RBRACE) {
    compound->AddChildren(ParseExpression());
    if (current_token_->GetType() == Token::Type::TOKEN_SEMI) {
      Eat(Token::Type::TOKEN_SEMI);
    }
  }

  if (should_close == true) {
    Eat(Token::Type::TOKEN_RBRACE);
  }

  return compound;
}

std::shared_ptr<Ast> Parser::ParseExpression() {
  switch (current_token_->GetType()) {
    case Token::Type::TOKEN_ID:
      return ParseId();
    case Token::Type::TOKEN_LPAREN:
      return ParseList();
    case Token::Type::TOKEN_INT:
      return ParseInt();
    default:
      LOG(FATAL) << "[Parser]: Unexpected token " << *current_token_;
  }
}
std::shared_ptr<Ast> Parser::ParseId() {
  std::string value = current_token_->Value();
  Eat(Token::Type::TOKEN_ID);

  if (current_token_->GetType() == Token::Type::TOKEN_EQUALS) {
    Eat(Token::Type::TOKEN_EQUALS);
    return AstAssignment::Build(value, ParseExpression());
  }
  std::shared_ptr<Ast> ast = AstVariable::Build(value);
  auto ast_variable = std::dynamic_pointer_cast<AstVariable>(ast);

  if (current_token_->GetType() == Token::Type::TOKEN_COLON) {
    Eat(Token::Type::TOKEN_COLON);
    while (current_token_->GetType() == Token::Type::TOKEN_ID) {
      ast_variable->AppendDataType(current_token_->Value());
      Eat(Token::Type::TOKEN_ID);

      if (current_token_->GetType() == Token::Type::TOKEN_LT) {
        Eat(Token::Type::TOKEN_LT);
        ast_variable->AppendDataType(current_token_->Value());
        Eat(Token::Type::TOKEN_ID);
        Eat(Token::Type::TOKEN_GT);
      }
    }
  } else {
    if (current_token_->GetType() == Token::Type::TOKEN_LPAREN) {
      ast = AstCall::Build();
      auto ast_call = std::dynamic_pointer_cast<AstCall>(ast);
      ast_call->AddChildren(ParseList());
    }
  }
  return ast;
}

std::shared_ptr<Ast> Parser::ParseList() {
  Eat(Token::Type::TOKEN_LPAREN);
  std::shared_ptr<Ast> ast = AstCompound::Build();
  std::shared_ptr<AstCompound> ast_compound =
      std::dynamic_pointer_cast<AstCompound>(ast);
  ast_compound->AddChildren(ParseExpression());
  while (current_token_->GetType() == Token::Type::TOKEN_COMMA) {
    Eat(Token::Type::TOKEN_COMMA);
    ast_compound->AddChildren(ParseExpression());
  }
  Eat(Token::Type::TOKEN_RPAREN);

  if (current_token_->GetType() == Token::Type::TOKEN_COLON) {
    Eat(Token::Type::TOKEN_COLON);
    while (current_token_->GetType() == Token::Type::TOKEN_ID) {
      ast_compound->AppendDataType(current_token_->Value());
      Eat(Token::Type::TOKEN_ID);

      if (current_token_->GetType() == Token::Type::TOKEN_LT) {
        Eat(Token::Type::TOKEN_LT);
        ast_compound->AppendDataType(current_token_->Value());
        Eat(Token::Type::TOKEN_ID);
        Eat(Token::Type::TOKEN_GT);
      }
    }
  }

  if (current_token_->GetType() == Token::Type::TOKEN_RIGHT_ARROW) {
    Eat(Token::Type::TOKEN_RIGHT_ARROW);
    ast = AstFunction::Build(ParseCompound());
  }

  return ast;
}

std::shared_ptr<AstCompound> Parser::ParseFunctionBlock() {
  Eat(Token::Type::TOKEN_LBRACE);
  auto ast = AstCompound::Build();
  while (current_token_->GetType() != Token::Type::TOKEN_RBRACE) {
    ast->AddChildren(ParseExpression());
  }
  Eat(Token::Type::TOKEN_RBRACE);
  return ast;
}

std::shared_ptr<AstInt> Parser::ParseInt() {
  int value = std::stoi(current_token_->Value());
  Eat(Token::Type::TOKEN_INT);
  auto ast_int = AstInt::Build(value);
  return ast_int;
}
}  // namespace my_compiler
