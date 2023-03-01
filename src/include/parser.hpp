#pragma once
#include <include/ast.hpp>
#include <include/lexer.hpp>
#include <include/token.hpp>
#include <memory>
namespace my_compiler {
class Parser {
 public:
  Parser(Lexer& lexer);
  std::shared_ptr<Ast> Parse();
  std::shared_ptr<Token> Eat(const Token::Type type);
  std::shared_ptr<AstCompound> ParseCompound();
  std::shared_ptr<Ast> ParseExpression();
  std::shared_ptr<Ast> ParseId();
  std::shared_ptr<Ast> ParseList();
  std::shared_ptr<AstInt> ParseInt();

 private:
  Lexer& lexer_;
  std::shared_ptr<Token> current_token_ = nullptr;
};
}  // namespace my_compiler