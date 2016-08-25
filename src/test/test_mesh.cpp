#include "catch.hpp"

#define private public
#define protected public
#include "cartesian_mesh.hpp"

TEST_CASE("cartesian mesh should be initialised with even grids", "[StructuredMesh]") {
  SECTION("should work in 2D") {
    lady::DomainConfig<2> domainConfig;
    lady::CartesianMeshConfig<2> meshConfig(domainConfig);
    lady::CartesianMesh<2> mesh;

    domainConfig.axisStartCoords = { 0, 0 };
    domainConfig.axisEndCoords = { 1, 1 };
    meshConfig.numGridAlongEachAxis = { 10, 10 };
    mesh.init(meshConfig);

    REQUIRE(mesh.numGridAlongX() == 10);
    REQUIRE(mesh.numGridAlongY() == 10);

    double dx = 0.1, dy = 0.1;
    int l = 0;
    for (int j = 0; j < mesh.numGridAlongY(); j++) {
      for (int i = 0; i < mesh.numGridAlongX(); i++) {
        REQUIRE(mesh.gridCoord(l)[0] == dx * (i + 0.5));
        REQUIRE(mesh.gridCoord(l)[1] == dy * (j + 0.5));
        l++;
      }
    }
  }
  SECTION("should work in 3D") {
    lady::DomainConfig<3> domainConfig;
    lady::CartesianMeshConfig<3> meshConfig(domainConfig);
    lady::CartesianMesh<3> mesh;

    domainConfig.axisStartCoords = { 0, 0, 0 };
    domainConfig.axisEndCoords = { 1, 1, 1 };
    meshConfig.numGridAlongEachAxis = { 10, 10, 10 };
    mesh.init(meshConfig);

    double dx = 0.1, dy = 0.1, dz = 0.1;
    int l = 0;
    for (int k = 0; k < mesh.numGridAlongZ(); k++) {
      for (int j = 0; j < mesh.numGridAlongY(); j++) {
        for (int i = 0; i < mesh.numGridAlongX(); i++) {
          REQUIRE(mesh.gridCoord(l)[0] == dx * (i + 0.5));
          REQUIRE(mesh.gridCoord(l)[1] == dy * (j + 0.5));
          REQUIRE(mesh.gridCoord(l)[2] == dz * (k + 0.5));
          l++;
        }
      }
    }
  }
}
