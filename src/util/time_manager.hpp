#ifndef __LADY_TimeManager
#define __LADY_TimeManager

#include "alert.hpp"

namespace lady {

class TimeConfig {
public:
  string startTime;
  string endTime;
  double timeStepSize;
};

class TimeManager {
public:
  static ptime startTime;
  static ptime currTime;
  static ptime endTime;
  static time_duration timeStepSize;
  static long timeStep;
  static map<string, Alert> alerts;

  static void init(const TimeConfig &timeConfig);

  static bool isFinished();

  static void advance();

  static void printTime();

  static void setAlert(const string &name, const string &freq);

  static const Alert& alert(const string &name);

  static string currTimeToString();

  static string timeStepToString();

private:
  static time_facet *facet;
  static stringstream stream;
};

}

#endif
