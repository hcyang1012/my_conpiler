#pragma once
#include <memory>
#include <string>
namespace my_compiler {
class Token {
 public:
  enum Type {
    TOKEN_ID,
    TOKEN_EQUALS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_RIGHT_ARROW,
    TOKEN_INT,
    TOKEN_SEMI,
    TOKEN_EOF
  };

  Token(const Type& type);
  Token(const std::string& value, const Type& type);

  const std::string& TypeName() const;
  const Type& GetType() const;
  const std::string& Value() const;
  static std::shared_ptr<Token> Build(const Type& type,
                                      const std::string& value = "");
  static std::shared_ptr<Token> Build(const Type& type, const char value);

  std::string ToString() const;

 private:
  Type type_;
  std::string value_;
};

std::ostream& operator<<(std::ostream& os, const Token& token);

class TokenId : public Token {
 public:
  TokenId(const std::string& value);
};

class TokenEquals : public Token {
 public:
  TokenEquals(const std::string& value);
};

class TokenLParen : public Token {
 public:
  TokenLParen(const std::string& value);
};

class TokenRParen : public Token {
 public:
  TokenRParen(const std::string& value);
};

class TokenLBrace : public Token {
 public:
  TokenLBrace(const std::string& value);
};

class TokenRBrace : public Token {
 public:
  TokenRBrace(const std::string& value);
};

class TokenColon : public Token {
 public:
  TokenColon(const std::string& value);
};

class TokenComma : public Token {
 public:
  TokenComma(const std::string& value);
};

class TokenLT : public Token {
 public:
  TokenLT(const std::string& value);
};

class TokenGT : public Token {
 public:
  TokenGT(const std::string& value);
};

class TokenRightArrow : public Token {
 public:
  TokenRightArrow(const std::string& value);
};

class TokenInt : public Token {
 public:
  TokenInt(const std::string& value);
};

class TokenSemi : public Token {
 public:
  TokenSemi(const std::string& value);
};

class TokenEof : public Token {
 public:
  TokenEof();
};
}  // namespace my_compiler