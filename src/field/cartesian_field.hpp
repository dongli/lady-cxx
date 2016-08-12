#ifndef __LADY_CartesianField
#define __LADY_CartesianField

#include "cartesian_mesh.hpp"
#include "structured_field.hpp"

namespace lady {

template <int NUM_DIM>
class CartesianField : public StructuredField<NUM_DIM, CartesianMesh> {
public:
  CartesianField();
  virtual ~CartesianField();
};

}

#endif
