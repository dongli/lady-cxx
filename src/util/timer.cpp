#include "timer.hpp"

namespace lady {

map<string, cpu_timer> Timer::timers;

void Timer::start(const string &name) {
  if (timers.find(name) == timers.end()) {
    cpu_timer timer;
    timers[name] = timer;
  }
  timers[name].start();
}

void Timer::stop(const string &name) {
  cpu_timer &timer = timers[name];
  timer.stop();
}

void Timer::print() {
  double total = 0;
  for (auto &timer : timers) {
    total += timer.second.elapsed().wall;
  }
  stringstream ss;
  ss << "Total: " << total / 1.0e9 << "s";
  for (auto &timer : timers) {
    ss << " " << timer.first << ": " << timer.second.elapsed().wall / total * 100 << "%";
  }
  LOG_NOTE << ss.str();
}

}
