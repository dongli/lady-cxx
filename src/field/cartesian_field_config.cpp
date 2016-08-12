#include "cartesian_field_config.hpp"

namespace lady {

template class CartesianFieldConfig<2>;
template class CartesianFieldConfig<3>;

template <int NUM_DIM>
CartesianFieldConfig<NUM_DIM>::CartesianFieldConfig(const CartesianMeshConfig<NUM_DIM> &meshConfig)
: StructuredFieldConfig<NUM_DIM, CartesianMeshConfig>(meshConfig) {
}

template <int NUM_DIM>
CartesianFieldConfig<NUM_DIM>::~CartesianFieldConfig() {
}

}
