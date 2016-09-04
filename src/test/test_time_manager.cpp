#include "catch.hpp"

#define private public
#define protected public

#include "time_manager.hpp"

TEST_CASE("initialize time manager", "[TimeManager]") {
  lady::TimeConfig timeConfig;

  timeConfig.startTime = "2016-08-21 11:54:00";
  timeConfig.endTime = "2016-08-21 23:54:00";
  timeConfig.timeStepSize = 30;
  lady::TimeManager::init(timeConfig);
  REQUIRE(lady::TimeManager::startTime.date().year() == 2016);
  REQUIRE(lady::TimeManager::startTime.date().month() == 8);
  REQUIRE(lady::TimeManager::startTime.date().day() == 21);
  REQUIRE(lady::TimeManager::startTime.time_of_day().hours() == 11);
  REQUIRE(lady::TimeManager::startTime.time_of_day().minutes() == 54);
  REQUIRE(lady::TimeManager::startTime.time_of_day().seconds() == 0);
  REQUIRE(lady::TimeManager::endTime.date().year() == 2016);
  REQUIRE(lady::TimeManager::endTime.date().month() == 8);
  REQUIRE(lady::TimeManager::endTime.date().day() == 21);
  REQUIRE(lady::TimeManager::endTime.time_of_day().hours() == 23);
  REQUIRE(lady::TimeManager::endTime.time_of_day().minutes() == 54);
  REQUIRE(lady::TimeManager::endTime.time_of_day().seconds() == 0);
  REQUIRE(lady::TimeManager::currTime == lady::TimeManager::startTime);
  REQUIRE(lady::TimeManager::timeStepSize.seconds() == 30);
}

TEST_CASE("set alerts", "[TimeManager]") {
  lady::TimeConfig timeConfig;

  timeConfig.startTime = "2016-08-21 12:00:00";
  timeConfig.endTime = "2016-08-21 13:00:00";
  timeConfig.timeStepSize = 60;
  lady::TimeManager::init(timeConfig);

  lady::TimeManager::setAlert("test", "00:05:00");
  REQUIRE_THROWS_AS(lady::TimeManager::setAlert("test", "00:35:30");, std::runtime_error);

  boost::posix_time::ptime refTime = lady::TimeManager::startTime;
  while (!lady::TimeManager::isFinished()) {
    boost::posix_time::time_duration diffTime = lady::TimeManager::currTime - refTime;
    if (diffTime.minutes() == 5 || diffTime.minutes() == 0) {
      REQUIRE(lady::TimeManager::alert("test").isOn() == true);
      refTime = lady::TimeManager::currTime;
    } else {
      REQUIRE(lady::TimeManager::alert("test").isOn() == false);
    }
    lady::TimeManager::advance();
  }
}
