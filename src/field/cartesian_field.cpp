#include "cartesian_field.hpp"

namespace lady {

template class CartesianField<2>;
template class CartesianField<3>;

template <int NUM_DIM>
CartesianField<NUM_DIM>::CartesianField() {
}

template <int NUM_DIM>
CartesianField<NUM_DIM>::~CartesianField() {
}

}
