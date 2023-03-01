#include <glog/logging.h>

#include <include/ast.hpp>
#include <include/compiler.hpp>
#include <include/logging.hpp>
#include <memory>

namespace my_compiler {

Compiler::Compiler(const std::string& src) : lexer_(src), parser_(lexer_) {}

void Compiler::Compile() {
  auto root = parser_.Parse();
  VLOG(LOG_LEVEL::INFO) << root;
  // std::shared_ptr<Token> token = nullptr;
  // while ((token = lexer_.NextToken())->GetType() != Token::Type::TOKEN_EOF) {
  //   VLOG(LOG_LEVEL::INFO) << *token;
  // }
}
}  // namespace my_compiler
