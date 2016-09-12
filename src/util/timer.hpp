#ifndef __LADY_TIMER
#define __LADY_TIMER

#include "common.hpp"

namespace lady {

class Timer {
public:
  static map<string, cpu_timer> timers;

  static void start(const string &name);

  static void stop(const string &name);

  static void print();
};

}

#endif
