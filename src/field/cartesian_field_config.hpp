#ifndef __LADY_CartesianFieldConfig
#define __LADY_CartesianFieldConfig

#include "cartesian_mesh.hpp"
#include "structured_field_config.hpp"

namespace lady {

template <int NUM_DIM>
class CartesianFieldConfig : public StructuredFieldConfig<NUM_DIM, CartesianMeshConfig> {
public:
  CartesianFieldConfig(const CartesianMeshConfig<NUM_DIM> &meshConfig);
  virtual ~CartesianFieldConfig();
};

}

#endif
