#include "catch.hpp"
#include "dycore_cartesian_2d_fixture.hpp"

TEST_CASE_METHOD(DycoreCartesian2dFixture, "dycore should calculate parcel forces", "[Dycore]") {
  SECTION("use uniform data") {
    p().fill(1);
    T().fill(2);
    dycore.inputBaroclinicData(p, T);
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
  SECTION("use cylinder pressure") {
    arma::vec::fixed<2> x0 = { 0.5, 0.5 };
    for (size_t gi = 0; gi < dycore.mesh().numGrid(); gi++) {
      auto x = dycore.mesh().gridCoord(gi);
      if (norm(x - x0) < 0.25) {
        p(gi) = 2;
      } else {
        p(gi) = 1;
      }
    }
    T().fill(2);
    dycore.inputBaroclinicData(p, T);
    dycore.updateQuadPoints(0);
    dycore.calcForces(0);
    // TODO: How to test the result?
  }
}
