#include "time_manager.hpp"

namespace lady {

ptime TimeManager::startTime;
ptime TimeManager::currTime;
ptime TimeManager::endTime;
time_duration TimeManager::timeStepSize;
long unsigned int TimeManager::timeStep;
map<string, Alert> TimeManager::alerts;
time_facet* TimeManager::facet;
stringstream TimeManager::stream;

void TimeManager::init(const TimeConfig &timeConfig) {
  startTime = time_from_string(timeConfig.startTime);
  currTime = startTime;
  endTime = time_from_string(timeConfig.endTime);
  timeStepSize = milliseconds(timeConfig.timeStepSize * 1000); // TODO: Is this OK for other values?
  timeStep = 0;

  facet = new time_facet();
  facet->format("%Y-%m-%d_%H:%M:%S");
  stream.imbue(std::locale(std::locale::classic(), facet));
}

bool TimeManager::isFirstStep() {
  return currTime == startTime;
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
  timeStep++;
}

double TimeManager::elapsedSeconds() {
  auto diff = currTime - startTime;
  return diff.seconds();
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

void TimeManager::setAlert(const string &name, const time_duration &freq) {
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

string TimeManager::startTimeToString() {
  stream.str("");
  stream << startTime;
  return stream.str();
}

string TimeManager::currTimeToString() {
  stream.str("");
  stream << currTime;
  return stream.str();
}

string TimeManager::timeStepToString() {
  stream.str("");
  stream << setw(5) << setfill('0') << timeStep;
  return stream.str();
}

}
