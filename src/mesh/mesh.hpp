#ifndef __LADY_Mesh
#define __LADY_Mesh

#include "common.hpp"
#include "mesh_config.hpp"

namespace lady {

template <int NUM_DIM>
class Mesh {
protected:
  mat _gridCoords;
  mat _gridSizes;
public:
  Mesh();
  virtual ~Mesh();

  virtual void init(const MeshConfig<NUM_DIM> &meshConfig) = 0;

  int numGrid() const { return _gridCoords.n_cols; }

  const mat& gridCoords() const { return _gridCoords; }

  vec::fixed<NUM_DIM> gridCoord(int i) const { return _gridCoords.col(i); }

  vec::fixed<NUM_DIM> gridSize(int i) const { return _gridSizes.col(i); }
};

}

#endif
