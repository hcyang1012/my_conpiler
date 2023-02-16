#pragma once
#include <glog/logging.h>

#include <fstream>
#include <string>
namespace my_compiler {
namespace io {
std::string read_file(const std::string& file_name);
}  // namespace io

}  // namespace my_compiler