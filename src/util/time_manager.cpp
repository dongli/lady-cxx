#include "time_manager.hpp"

namespace lady {

ptime TimeManager::startTime;
ptime TimeManager::currTime;
ptime TimeManager::endTime;
time_duration TimeManager::timeStepSize;
map<string, Alert> TimeManager::alerts;

void TimeManager::init(const TimeConfig &timeConfig) {
  startTime = time_from_string(timeConfig.startTime);
  currTime = startTime;
  endTime = time_from_string(timeConfig.endTime);
  timeStepSize = seconds(timeConfig.timeStepSize);
}

bool TimeManager::isFinished() {
  return currTime > endTime;
}

void TimeManager::advance() {
  // Update alerts.
  for (auto &alert : alerts) {
    if (alert.second.isOn()) {
      alert.second.update();
    }
  }
  currTime += timeStepSize;
}

void TimeManager::printTime() {
  LOG_NOTE << ">>> " << currTime << " <<<";
}

void TimeManager::setAlert(const string &name, const string &freq) {
  if (alerts.find(name) == alerts.end()) {
    Alert alert(name, freq);
    alerts[name] = alert;
  } else {
    LOG_ERROR << "Duplicate alert \"" << name << "\"!" << THROW_EXCEPTION;
  }
}

const Alert& TimeManager::alert(const string &name) {
  auto res = alerts.find(name);
  if (res == alerts.end()) {
    LOG_ERROR << "No alert \"" << name << "\" is found!";
  }
  return res->second;
}

}
