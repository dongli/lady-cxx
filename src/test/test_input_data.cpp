#include "catch.hpp"
#include "dycore_cartesian_2d_fixture.hpp"

TEST_CASE_METHOD(DycoreCartesian2dFixture, "dycore can be initialized with data", "[Dycore]") {
  SECTION("use uniform data") {
    p().fill(1);
    T().fill(2);
    dycore.inputBaroclinicData(p, T);
    dycore.regridBaroclinicData(0);
    for (size_t pi = 0; pi < dycore.parcels[0].size(); pi++) {
      REQUIRE(dycore.parcels[0][pi].m > 0);
    }
    for (int gi = 0; gi < dycore.mesh().numGrid(); gi++) {
      REQUIRE(p(gi) == Approx(dycore.p(gi)));
      REQUIRE(T(gi) == Approx(dycore.T(gi)));
    }
  }
}
