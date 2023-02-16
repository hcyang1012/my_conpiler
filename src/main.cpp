#include <glog/logging.h>

#include <include/compiler.hpp>
#include <include/io.hpp>
#include <iostream>
int main(int argc, char *argv[]) {
  FLAGS_logtostderr = true;
  ::google::InitGoogleLogging(argv[0]);
  if (argc < 2) {
    LOG(FATAL) << "Please specify file to read";
  }

  my_compiler::Compiler compiler(my_compiler::io::read_file(argv[1]));
  compiler.Compile();
}
