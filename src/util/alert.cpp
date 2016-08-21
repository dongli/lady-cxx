#include "alert.hpp"
#include "time_manager.hpp"

namespace lady {

Alert::Alert(const string &name, const string &freq) {
  this->name = name;
  this->freq = duration_from_string(freq);
  this->nextOnTime = TimeManager::startTime + this->freq;
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
