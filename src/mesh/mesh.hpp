#ifndef __LADY_Mesh
#define __LADY_Mesh

#include "common.hpp"

namespace lady {

class Mesh {
protected:
  mat _gridCoords;
  mat _gridSizes;
public:
  Mesh();
  virtual ~Mesh();

  int numGrid() const { return _gridCoords.n_cols; }

  const mat& gridCoords() const { return _gridCoords; }

  Vec gridCoord(int i) const { return _gridCoords.col(i); }

  Vec gridSize(int i) const { return _gridSizes.col(i); }
};

}

#endif
