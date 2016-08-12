#include "logger.hpp"

namespace lady { namespace logger {

void init() {
  register_simple_formatter_factory<SeverityLevel, char>("Severity");
  add_console_log(std::cout, keywords::format = "[%Severity%]: %Message%");
}

record_ostream& operator<<(record_ostream &os, const ErrorHandling &e) {
  throw std::runtime_error(os.str());
}

std::string basename(const std::string &path) {
  return path.substr(path.find_last_of("/\\")+1);
}

}}
