#include "catch.hpp"
#include "dycore_cartesian_2d_fixture.hpp"

TEST_CASE_METHOD(DycoreCartesian2dFixture, "dycore can be initialized with data", "[Dycore]") {
  SECTION("use uniform data") {
    p().fill(1);
    T().fill(2);
    dycore.inputData(p, T);
    dycore.regrid(0);
    for (int gi = 0; gi < dycore.mesh.numGrid(); gi++) {
      REQUIRE(p(gi) == Approx(dycore.p(gi)));
      REQUIRE(T(gi) == Approx(dycore.T(gi)));
    }
  }
}
