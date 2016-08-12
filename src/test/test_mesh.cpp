#include "catch.hpp"
#include "cartesian_mesh.hpp"

TEST_CASE("structured mesh should be initialised with even grids", "[StructuredMesh]") {
  SECTION("should work in 2D") {
    lady::DomainConfig<2> domainConfig;
    lady::StructuredMeshConfig<2> meshConfig(domainConfig);
    lady::StructuredMesh<2> mesh;

    domainConfig.axisStartCoords = { 0, 0 };
    domainConfig.axisEndCoords = { 1, 1 };
    meshConfig.numGridAlongEachAxis = { 10, 10 };
    mesh.init(meshConfig);

    double dx = 0.1, dy = 0.1;
    int l = 0;
    for (int j = 0; j < 10; j++) {
      for (int i = 0; i < 10; i++) {
        REQUIRE(mesh.gridCoord(l)[0] == dx * (i + 0.5));
        REQUIRE(mesh.gridCoord(l)[1] == dy * (j + 0.5));
        l++;
      }
    }
  }
  SECTION("should work in 3D") {
    lady::DomainConfig<3> domainConfig;
    lady::StructuredMeshConfig<3> meshConfig(domainConfig);
    lady::StructuredMesh<3> mesh;

    domainConfig.axisStartCoords = { 0, 0, 0 };
    domainConfig.axisEndCoords = { 1, 1, 1 };
    meshConfig.numGridAlongEachAxis = { 10, 10, 10 };
    mesh.init(meshConfig);

    double dx = 0.1, dy = 0.1, dz = 0.1;
    int l = 0;
    for (int k = 0; k < 10; k++) {
      for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
          REQUIRE(mesh.gridCoord(l)[0] == dx * (i + 0.5));
          REQUIRE(mesh.gridCoord(l)[1] == dy * (j + 0.5));
          REQUIRE(mesh.gridCoord(l)[2] == dz * (k + 0.5));
          l++;
        }
      }
    }
  }
}
