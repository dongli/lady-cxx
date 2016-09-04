#ifndef __LADY_Alert
#define __LADY_Alert

#include "common.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

namespace lady {

class Alert {
private:
  time_duration freq;
  ptime nextOnTime;
  string name;
public:
  Alert() {}
  Alert(const string &name, const string &freq);
  Alert(const string &name, const time_duration &freq);
  ~Alert();

  void update();

  bool isOn() const;
};

}

#endif
