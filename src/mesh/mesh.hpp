#ifndef __LADY_Mesh
#define __LADY_Mesh

#include "common.hpp"
#include "mesh_config.hpp"

namespace lady {

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
class Mesh {
public:
  typedef MeshConfigTemplate<NUM_DIM> MeshConfigType;
protected:
  mat _gridCoords;
  mat _gridSizes;
  MeshConfigType meshConfig;
public:
  Mesh();
  virtual ~Mesh();

  virtual void init(const MeshConfigType &meshConfig);

  int numGrid() const { return _gridCoords.n_cols; }

  const mat& gridCoords() const { return _gridCoords; }

  vec::fixed<NUM_DIM> gridCoord(int i) const { return _gridCoords.col(i); }

  vec::fixed<NUM_DIM> gridSize(int i) const { return _gridSizes.col(i); }
};

}

#endif
