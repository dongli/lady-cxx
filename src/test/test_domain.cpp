#include "catch.hpp"
#include "cartesian_domain.hpp"

TEST_CASE("domain should provide some functions", "[CartesianDomain]") {
  lady::logger::init();

  lady::DomainConfig<2> domainConfig;
  lady::CartesianDomain<2> domain;

  domainConfig.axisStartCoords = { 0.0, 0.0 };
  domainConfig.axisEndCoords = { 1.0, 1.0 };
  domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
  domain.init(domainConfig);

  arma::vec::fixed<2> x, y, z;

  SECTION("should sub and add coordinates") {
    x = { 0.1, 0.1 };
    y = { 0.9, 0.1 };
    z = domain.subCoord(x, y);
    REQUIRE(z[0] == Approx(0.2));
    REQUIRE(z[1] == Approx(0.0));

    x = { 0.13, 0.54 };
    y = { 0.03, 0.69 };
    z = domain.subCoord(x, y);
    REQUIRE(z[0] == Approx(0.1));
    REQUIRE(z[1] == Approx(-0.15));

    x = { 0.45, 0.98 };
    y = { 0.56, 0.31 };
    z = domain.addCoord(x, y);
    REQUIRE(z[0] == Approx(0.01));
    REQUIRE(z[1] == Approx(0.29));

    x = { 0.1, 0.1 };
    y = { 1.9, 0.1 };
    z = domain.addCoord(x, y);
    REQUIRE(z[0] == Approx(1.0));
    REQUIRE(z[1] == Approx(0.2));

    x = { 0.1, 0.1 };
    y = { 1.91, 0.1 };
    REQUIRE_THROWS_AS(domain.addCoord(x, y), std::runtime_error);

    x = { 0.1, 0.1 };
    y = { 2.91, 0.1 };
    REQUIRE_THROWS_AS(domain.subCoord(x, y), std::runtime_error);
  }
  SECTION("should calculate distance") {
    x = { 0.1, 0.0 };
    y = { 0.9, 0.0 };
    REQUIRE(domain.distance(x, y) == Approx(0.2));
  }
}
