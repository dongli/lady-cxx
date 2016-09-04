#include "alert.hpp"
#include "time_manager.hpp"

namespace lady {

Alert::Alert(const string &name, const string &freq) {
  this->name = name;
  this->freq = duration_from_string(freq);
  this->nextOnTime = TimeManager::startTime;
}

Alert::Alert(const string &name, const time_duration &freq) {
  this->name = name;
  this->freq = freq;
  this->nextOnTime = TimeManager::startTime;
}

Alert::~Alert() {
}

void Alert::update() {
  nextOnTime += freq;
}

bool Alert::isOn() const {
  return nextOnTime == TimeManager::currTime;
}

}
