#include "catch.hpp"
#include "parcel.hpp"

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
