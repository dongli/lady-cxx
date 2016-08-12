#ifndef __LADY_Logger
#define __LADY_Logger

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <iostream>
#include <iomanip>

namespace lady { namespace logger {

  using namespace boost::log;

  enum ErrorHandling { EXCEPTION, EXIT };

  enum SeverityLevel { DEBUG, NOTE, WARN, ERROR };
  template< typename CharT, typename TraitsT >
  inline std::basic_ostream<CharT, TraitsT>& operator<< (std::basic_ostream<CharT, TraitsT>& os, SeverityLevel lvl)
  {
    static const char* const str[] = { "DEBUG", "NOTE", "WARN", "ERROR" };
    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
      os << str[lvl];
    else
      os << static_cast<int>(lvl);
    return os;
  }

  static sources::severity_logger<SeverityLevel> instance;

  void init();

  template <typename ValueType>
  ValueType set_get_attr(const char *name, const ValueType &value) {
    auto attr = attribute_cast<attributes::mutable_constant<ValueType>>(
      core::get()->get_global_attributes()[name]
    );
    attr.set(value);
    return attr.get();
  }

  std::string basename(const std::string &path);

  record_ostream& operator<<(record_ostream &os, const ErrorHandling &e);
}}

#define LOG_ERROR BOOST_LOG_SEV(lady::logger::instance, lady::logger::ERROR) \
    << lady::logger::basename(__FILE__) << ":" << __LINE__ << ": "

#define THROW_EXCEPTION lady::logger::EXCEPTION
#define EXIT lady::logger::EXIT

#endif
