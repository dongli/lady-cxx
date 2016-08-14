#include "catch.hpp"
#include "dycore_cartesian_2d_fixture.hpp"

TEST_CASE_METHOD(DycoreCartesian2dFixture, "dycore should calculate parcel forces", "[Dycore]") {
  SECTION("use uniform data") {
    p().fill(1);
    T().fill(2);
    dycore.inputData(p, T);
    dycore.updateQuadPoints(0);
    dycore.calcForces(0);
    for (int pi = 0; pi < dycore.parcels[0].size(); pi++) {
      REQUIRE(dycore.parcels[0][pi].Fp[0] == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Fp[1] == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mp(0, 0) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mp(0, 1) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mp(1, 0) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mp(1, 1) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Fr[0] == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Fr[1] == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mr(0, 0) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mr(0, 1) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mr(1, 0) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Mr(1, 1) == Approx(0));
      REQUIRE(dycore.parcels[0][pi].Qr == Approx(0));
    }
  }
}
