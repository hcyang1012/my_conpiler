#include <glog/logging.h>

#include <include/token.hpp>
#include <iomanip>
#include <map>
#include <ostream>
#include <sstream>
#include <string>

namespace my_compiler {

static std::map<Token::Type, std::string> token_names{
    {Token::Type::TOKEN_ID, "ID"},
    {Token::Type::TOKEN_EQUALS, "EQUALS"},
    {Token::Type::TOKEN_LPAREN, "LPAREN"},
    {Token::Type::TOKEN_RPAREN, "RPAREN"},
    {Token::Type::TOKEN_LBRACE, "LBRACE"},
    {Token::Type::TOKEN_RBRACE, "RBRACE"},
    {Token::Type::TOKEN_COLON, "COLON"},
    {Token::Type::TOKEN_COMMA, "COMMA"},
    {Token::Type::TOKEN_LT, "LT"},
    {Token::Type::TOKEN_GT, "GT"},
    {Token::Type::TOKEN_RIGHT_ARROW, "RIGHT_ARROW"},
    {Token::Type::TOKEN_INT, "INT"},
    {Token::Type::TOKEN_SEMI, "SEMI"},
    {Token::Type::TOKEN_EOF, "EOF"},
};

Token::Token(const Token::Type& type) : type_(type), value_("") {}
Token::Token(const std::string& value, const Token::Type& type)
    : type_(type), value_(value) {}

const Token::Type& Token::GetType() const { return type_; }
const std::string& Token::TypeName() const { return token_names.at(GetType()); }
const std::string& Token::Value() const { return value_; }
std::unique_ptr<Token> Token::Build(const Token::Type& type,
                                    const std::string& value) {
  switch (type) {
    case TOKEN_ID:
      return std::make_unique<TokenId>(value);
    case TOKEN_EQUALS:
      return std::make_unique<TokenEquals>(value);
    case TOKEN_LPAREN:
      return std::make_unique<TokenLParen>(value);
    case TOKEN_RPAREN:
      return std::make_unique<TokenRParen>(value);
    case TOKEN_LBRACE:
      return std::make_unique<TokenLBrace>(value);
    case TOKEN_RBRACE:
      return std::make_unique<TokenRBrace>(value);
    case TOKEN_COLON:
      return std::make_unique<TokenColon>(value);
    case TOKEN_COMMA:
      return std::make_unique<TokenComma>(value);
    case TOKEN_LT:
      return std::make_unique<TokenLT>(value);
    case TOKEN_GT:
      return std::make_unique<TokenGT>(value);
    case TOKEN_RIGHT_ARROW:
      return std::make_unique<TokenRightArrow>(value);
    case TOKEN_INT:
      return std::make_unique<TokenInt>(value);
    case TOKEN_SEMI:
      return std::make_unique<TokenSemi>(value);
    case TOKEN_EOF:
      return std::make_unique<TokenEof>();
    default:
      LOG(ERROR) << "Invalid token type : " << type;
      return nullptr;
  }
}
std::unique_ptr<Token> Token::Build(const Type& type, const char value) {
  return Build(type, std::string(1, value));
}

std::string Token::ToString() const {
  std::stringstream ss;
  ss << "TOKEN('" << Value() << "')\t" << TypeName();
  return ss.str();
}
TokenId::TokenId(const std::string& value)
    : Token(value, Token::Type::TOKEN_ID) {}
TokenEquals::TokenEquals(const std::string& value)
    : Token(value, Token::Type::TOKEN_EQUALS) {}
TokenLParen::TokenLParen(const std::string& value)
    : Token(value, Token::Type::TOKEN_LPAREN) {}
TokenRParen::TokenRParen(const std::string& value)
    : Token(value, Token::Type::TOKEN_RPAREN) {}
TokenLBrace::TokenLBrace(const std::string& value)
    : Token(value, Token::Type::TOKEN_LBRACE) {}
TokenRBrace::TokenRBrace(const std::string& value)
    : Token(value, Token::Type::TOKEN_RBRACE) {}
TokenColon::TokenColon(const std::string& value)
    : Token(value, Token::Type::TOKEN_COLON) {}
TokenComma::TokenComma(const std::string& value)
    : Token(value, Token::Type::TOKEN_COMMA) {}
TokenLT::TokenLT(const std::string& value)
    : Token(value, Token::Type::TOKEN_LT) {}
TokenGT::TokenGT(const std::string& value)
    : Token(value, Token::Type::TOKEN_GT) {}
TokenRightArrow::TokenRightArrow(const std::string& value)
    : Token(value, Token::Type::TOKEN_RIGHT_ARROW) {}
TokenInt::TokenInt(const std::string& value)
    : Token(value, Token::Type::TOKEN_INT) {}
TokenSemi::TokenSemi(const std::string& value)
    : Token(value, Token::Type::TOKEN_SEMI) {}
TokenEof::TokenEof() : Token(Token::Type::TOKEN_EOF) {}

std::ostream& operator<<(std::ostream& os, const Token& token) {
  os << token.ToString();
  return os;
}

}  // namespace my_compiler
