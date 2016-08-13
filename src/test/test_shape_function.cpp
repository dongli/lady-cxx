#include "catch.hpp"
#include "cartesian_domain.hpp"
#include "parcel.hpp"
#include "shape_function.hpp"

TEST_CASE("check shape function", "[ShapeFunction]") {
  lady::DomainConfig<2> domainConfig;
  lady::CartesianDomain<2> domain;
  lady::Parcel<2> parcel;
  arma::vec::fixed<2> x, y, dfdy, dfdx, dfdxi;
  arma::mat::fixed<2, 2> dfdHi;
  double f;

  domainConfig.axisStartCoords = { 0.0, 0.0 };
  domainConfig.axisEndCoords = { 1.0, 1.0 };
  domainConfig.axisBoundaryTypes = { lady::PERIODIC, lady::PERIODIC };
  domain.init(domainConfig);
  parcel.init(0, vec::fixed<2>({ 0, 0 }), vec::fixed<2>({ 0.2, 0.2 }));

  x = { 1, 1 };
  parcel.getBodyCoord(domain, x, y);
  REQUIRE(y[0] == 0);
  REQUIRE(y[1] == 0);
  lady::ShapeFunction<2>::eval(y, f);
  REQUIRE(f == lady::ShapeFunction<2>::C);
  lady::ShapeFunction<2>::diff(y, dfdy);
  REQUIRE(dfdy[0] == 0);
  REQUIRE(dfdy[1] == 0);

  x = { 0.1, 0.1 };
  parcel.getBodyCoord(domain, x, y);
  REQUIRE(y[0] == Approx(0.25));
  REQUIRE(y[1] == Approx(0.25));
  lady::ShapeFunction<2>::eval(y, f);
  lady::ShapeFunction<2>::diff(y, dfdy);
  parcel.getShapeFunctionDerivatives(y, f, dfdx);
  parcel.getShapeFunctionDerivatives(y, f, dfdxi, dfdHi);
  REQUIRE(dfdx[0] == -dfdxi[0]);
  REQUIRE(dfdx[1] == -dfdxi[1]);
}
