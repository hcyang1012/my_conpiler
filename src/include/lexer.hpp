#pragma once
#include <include/token.hpp>
#include <memory>
#include <string>
namespace my_compiler {
class Lexer {
 public:
  Lexer(const std::string& src);

  void Advance();
  void SkipWhiteSpace();
  std::shared_ptr<Token> NextToken();
  std::shared_ptr<Token> AdvanceWith(std::shared_ptr<Token> token);
  std::shared_ptr<Token> AdvanceCurrent(Token::Type type);
  std::shared_ptr<Token> ParseId();
  std::shared_ptr<Token> ParseNumber();
  char Peek(size_t offset);

 private:
  bool is_white_space(const char value) {
    return (value == kCharCR || value == kCharNewLine ||
            value == kCharWhiteSpace || value == kCharTab);
  }
  const std::string src_;
  size_t current_idx_;
  char current_char_;

  const char kCharNull = '\0';
  const char kCharCR = '\r';
  const char kCharNewLine = '\n';
  const char kCharWhiteSpace = ' ';
  const char kCharTab = '\t';
};
}  // namespace my_compiler