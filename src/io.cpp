#include <include/io.hpp>

namespace my_compiler {
namespace io {
std::string read_file(const std::string& file_name) {
  std::ifstream if_file(file_name, std::ifstream::in);
  if (!if_file.is_open()) {
    LOG(FATAL) << "Can't open the file << " << file_name;
  }

  std::string result;
  std::string line;
  while (std::getline(if_file,line)) {
    result += line;
  }
  return result;
}
}  // namespace io
}  // namespace my_compiler