#pragma once
#include <include/lexer.hpp>
#include <string>
namespace my_compiler {

class Compiler {
 public:
  Compiler(const std::string& src);
  void Compile();
 private:
  Lexer lexer_;
};

}  // namespace my_compiler