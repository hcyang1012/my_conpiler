#include <glog/logging.h>

#include <include/compiler.hpp>
#include <include/logging.hpp>
#include <memory>

namespace my_compiler {

Compiler::Compiler(const std::string& src) : lexer_(src) {}

void Compiler::Compile() {
  std::unique_ptr<Token> token = nullptr;
  while ((token = lexer_.NextToken())->GetType() != Token::Type::TOKEN_EOF) {
    VLOG(LOG_LEVEL::INFO) << *token;
  }
}
}  // namespace my_compiler
