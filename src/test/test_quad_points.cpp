#include "catch.hpp"
#include "dycore_cartesian_2d_fixture.hpp"

TEST_CASE_METHOD(DycoreCartesian2dFixture, "initialize quadrature points", "[Dycore]") {
  SECTION("set static variables") {
    int qi = 0;
    for (int j = 0; j < lady::ShapeFunction<2>::nodes.size(); j++) {
      for (int i = 0; i < lady::ShapeFunction<2>::nodes.size(); i++) {
        REQUIRE(lady::QuadPoints<2>::y[qi][0] == lady::ShapeFunction<2>::nodes[i]);
        REQUIRE(lady::QuadPoints<2>::y[qi][1] == lady::ShapeFunction<2>::nodes[j]);
        qi++;
      }
    }
    for (int qi = 0; qi < lady::QuadPoints<2>::num; qi++) {
      double f;
      lady::ShapeFunction<2>::eval(lady::QuadPoints<2>::y[qi], f);
      REQUIRE(lady::QuadPoints<2>::f[qi] == Approx(f));
    }
  }
  SECTION("update physical variables") {
    p().fill(1);
    T().fill(2);
    dycore.inputData(p, T);
    dycore.run();
    for (int pi = 0; pi < dycore.parcels[0].size(); pi++) {
      for (int qi = 0; qi < lady::QuadPoints<2>::num; qi++) {
        REQUIRE(dycore.quadPoints[0][pi].rho[qi] == Approx(1.0 / 2.0 / lady::RD));
        REQUIRE(dycore.quadPoints[0][pi].T[qi] == Approx(2));
      }
    }
  }
}
