#include "parcel.hpp"
#include "shape_function.hpp"

namespace lady {

template class Parcel<2>;
template class Parcel<3>;

template <int NUM_DIM>
Parcel<NUM_DIM>::Parcel() {
}

template <int NUM_DIM>
Parcel<NUM_DIM>::~Parcel() {
}

template <int NUM_DIM>
void Parcel<NUM_DIM>::init(int id, const vec::fixed<NUM_DIM> &x, const vec::fixed<NUM_DIM> &size) {
  this->id = id;
  this->x = x;
  this->H.zeros();
  this->H.diag() = size * 2;
  afterMatrixChanged();
}

template <int NUM_DIM>
void Parcel<NUM_DIM>::getLocalVelocity(const vec::fixed<NUM_DIM> &y, vec::fixed<NUM_DIM> &v) const {
  v = this->v + dH * y;
}

template <int NUM_DIM>
void Parcel<NUM_DIM>::getShapeFunctionDerivatives(const vec::fixed<NUM_DIM> &y, double f, vec::fixed<NUM_DIM> &dfdx) const {
  ShapeFunction<NUM_DIM>::diff(y, dfdx);
  dfdx = invH.t() * dfdx / detH;
}

template <int NUM_DIM>
void Parcel<NUM_DIM>::getShapeFunctionDerivatives(const vec::fixed<NUM_DIM> &y, double f, vec::fixed<NUM_DIM> &dfdxi, mat::fixed<NUM_DIM, NUM_DIM> &dfdHi) const {
  ShapeFunction<NUM_DIM>::diff(y, dfdxi);
  dfdxi = - invH.t() * dfdxi / detH;
  dfdHi = dfdxi * y.t() - f * invH.t();
}

template <int NUM_DIM>
void Parcel<NUM_DIM>::afterMatrixChanged() {
  detH = det(H);
  invH = inv(H);
  svd(U, S, V, H);
}

}
