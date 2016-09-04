#include "catch.hpp"
#include "cartesian_domain_2d_fixture.hpp"
#include "parcel.hpp"
#include <boost/math/constants/constants.hpp>

TEST_CASE("parcel can be initialized", "[Parcel]") {
  lady::Parcel<2> parcel;
  parcel.init(0, vec::fixed<2>({0, 0}), vec::fixed<2>({1, 1}));
  REQUIRE(parcel.x[0] == 0);
  REQUIRE(parcel.x[1] == 0);
  REQUIRE(parcel.H(0, 0) == parcel.H(1, 1));
  REQUIRE(parcel.H(0, 0) > 0);
  REQUIRE(parcel.H(1, 0) == 0);
  REQUIRE(parcel.H(0, 1) == 0);
  REQUIRE(parcel.detH > 0);
}

TEST_CASE_METHOD(CartesianDomain2dFixture, "conversion between space and body coordinates", "[Parcel]") {
  lady::Parcel<2> parcel;
  parcel.init(0, vec::fixed<2>({50, 50}), vec::fixed<2>({1, 1}));
  vec::fixed<2> x, y;
  double dtheta = 2 * boost::math::double_constants::pi / (10 - 1);
  for (int i = 0; i < 10; i++) {
    double theta = dtheta * i;
    y[0] = cos(theta);
    y[1] = sin(theta);
    parcel.getSpaceCoord(domain, y, x);
    REQUIRE(norm(x - parcel.x) == Approx(2)); // Initial parcel size is twice the given size.
  }
}
