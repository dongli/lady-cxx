#include "timer.hpp"

namespace lady {

int Timer::timerLevel = 0;
map<string, std::pair<int, cpu_timer>> Timer::timers;

void Timer::start(const string &name) {
  if (timers.find(name) == timers.end()) {
    cpu_timer timer;
    timers[name] = std::make_pair(timerLevel, timer);
  }
  timers[name].second.start();
  timerLevel++;
}

void Timer::stop(const string &name) {
  cpu_timer &timer = timers[name].second;
  timer.stop();
  timerLevel--;
}

void Timer::print() {
  double total = 0;
  for (auto &timer : timers) {
    if (timer.second.first != 0) continue;
    total += timer.second.second.elapsed().wall;
  }
  stringstream ss;
  ss << "Total time cost: " << total / 1.0e9 << "s" << endl;
  for (auto &timer : timers) {
    for (int indent = 0; indent < timer.second.first; indent++) {
      ss << "  ";
    }
    ss << timer.first << ": " << timer.second.second.elapsed().wall / total * 100 << "%" << endl;
  }
  LOG_NOTE << ss.str();
}

}
