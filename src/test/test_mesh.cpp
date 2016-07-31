#include "catch.hpp"
#include "lady"

TEST_CASE("structured mesh should be initialised with even grids", "[StructuredMesh]") {
  lady::DomainConfig domainConfig;
  lady::StructuredMeshConfig meshConfig(domainConfig);
  lady::StructuredMesh mesh;

  domainConfig.axisStartCoords = { 0, 0 };
  domainConfig.axisEndCoords = { 1, 1 };
  meshConfig.numGridAlongEachAxis = { 10, 10 };
  mesh.init(meshConfig);
}
