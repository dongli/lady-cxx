#include "catch.hpp"
#include "dycore_cartesian_2d_fixture.hpp"

TEST_CASE_METHOD(DycoreCartesian2dFixture, "use RangeSearch in MLPACK to find out neighbor points", "[Dycore]") {
  for (int pi = 0; pi < dycore.parcels[0].size(); pi++) {
    REQUIRE(dycore.parcels[0][pi].numNeighbor == 24);
    uvec i(dycore.parcels[0][pi].numNeighbor);
    for (int ni = 0; ni < dycore.parcels[0][pi].numNeighbor; ni++) {
      i[ni] = dycore.parcels[0][pi].neighbors[ni]->id;
    }
    switch (pi) {
      case 0:
        REQUIRE(any(i ==  1)); REQUIRE(any(i ==  2)); REQUIRE(any(i ==  3));
        REQUIRE(any(i ==  4)); REQUIRE(any(i ==  5)); REQUIRE(any(i ==  6));
        REQUIRE(any(i == 10)); REQUIRE(any(i == 10)); REQUIRE(any(i == 15));
        REQUIRE(any(i == 20)); REQUIRE(any(i == 21)); REQUIRE(any(i == 24));
        break;
      case 1:
        REQUIRE(any(i ==  0)); REQUIRE(any(i ==  2)); REQUIRE(any(i ==  3));
        REQUIRE(any(i ==  4)); REQUIRE(any(i ==  5)); REQUIRE(any(i ==  6));
        REQUIRE(any(i ==  7)); REQUIRE(any(i == 11)); REQUIRE(any(i == 16));
        REQUIRE(any(i == 20)); REQUIRE(any(i == 21)); REQUIRE(any(i == 22));
        break;
      case 13:
        REQUIRE(any(i ==  3)); REQUIRE(any(i ==  7)); REQUIRE(any(i ==  8));
        REQUIRE(any(i ==  9)); REQUIRE(any(i == 10)); REQUIRE(any(i == 11));
        REQUIRE(any(i == 12)); REQUIRE(any(i == 14)); REQUIRE(any(i == 17));
        REQUIRE(any(i == 18)); REQUIRE(any(i == 19)); REQUIRE(any(i == 23));
        break;
    }
  }
}
