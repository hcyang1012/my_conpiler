#include <glog/logging.h>

#include <algorithm>
#include <cctype>
#include <include/lexer.hpp>
#include <memory>

namespace my_compiler {
Lexer::Lexer(const std::string& src)
    : src_(src), current_idx_(0), current_char_(src_.at(0)) {}

void Lexer::Advance() {
  if (current_idx_ < src_.length() && current_char_ != kCharNull) {
    current_idx_++;
    current_char_ = src_[current_idx_];
  }
}

void Lexer::SkipWhiteSpace() {
  while (is_white_space(current_char_)) {
    Advance();
  }
}
std::shared_ptr<Token> Lexer::NextToken() {
  while (current_char_ != kCharNull) {
    SkipWhiteSpace();
    if (std::isalpha(current_char_)) {
      return ParseId();
    }

    if (std::isdigit(current_char_)) {
      return ParseNumber();
    }

    switch (current_char_) {
      case '=': {
        if (Peek(1) == '>') {
          return AdvanceWith(
              AdvanceWith(Token::Build(Token::Type::TOKEN_RIGHT_ARROW, "=>")));
        } else {
          return AdvanceWith(Token::Build(Token::Type::TOKEN_EQUALS, "="));
        }
      } break;
      case '(':
        return AdvanceCurrent(Token::Type::TOKEN_LPAREN);
      case ')':
        return AdvanceCurrent(Token::Type::TOKEN_RPAREN);
      case '{':
        return AdvanceCurrent(Token::Type::TOKEN_LBRACE);
      case '}':
        return AdvanceCurrent(Token::Type::TOKEN_RBRACE);
      case ':':
        return AdvanceCurrent(Token::Type::TOKEN_COLON);
      case ',':
        return AdvanceCurrent(Token::Type::TOKEN_COMMA);
      case '<':
        return AdvanceCurrent(Token::Type::TOKEN_LT);
      case '>':
        return AdvanceCurrent(Token::Type::TOKEN_GT);
      case ';':
        return AdvanceCurrent(Token::Type::TOKEN_SEMI);
      case '\0':
        break;
      default:
        LOG(FATAL) << "[Lexer]: Invalid character at " << current_idx_ << " : "
                   << current_char_;
    }
  }
  return Token::Build(Token::Type::TOKEN_EOF);
}

std::shared_ptr<Token> Lexer::AdvanceWith(std::shared_ptr<Token> token) {
  Advance();
  return token;
}

std::shared_ptr<Token> Lexer::AdvanceCurrent(Token::Type type) {
  auto result = Token::Build(type, std::string(1, current_char_));
  Advance();
  return result;
}
std::shared_ptr<Token> Lexer::ParseId() {
  std::string value = "";
  while (std::isalnum(current_char_)) {
    value.push_back(current_char_);
    Advance();
  }
  return Token::Build(Token::Type::TOKEN_ID, value);
}

std::shared_ptr<Token> Lexer::ParseNumber() {
  std::string value = "";
  while (std::isdigit(current_char_)) {
    value.push_back(current_char_);
    Advance();
  }
  return Token::Build(Token::Type::TOKEN_INT, value);
}

char Lexer::Peek(size_t offset) {
  return src_[std::min((current_idx_ + offset), src_.length())];
}
}  // namespace my_compiler
