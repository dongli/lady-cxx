#include "parcel.hpp"
#include "shape_function.hpp"

namespace lady {

Parcel::Parcel() {
}

Parcel::~Parcel() {
}

void Parcel::init(int id, const Vec &x, const Vec &size) {
  this->id = id;
  this->x = x;
  this->H.zeros();
  this->H.diag() = size * 1.5;
  afterMatrixChanged();
}

void Parcel::getBodyCoord(const Vec &x, Vec &y) const {
  y = invH * (x - this->x);
}

void Parcel::getSpaceCoord(const Vec &y, Vec &x) const {
  x = this->x + H * y;
}

void Parcel::getLocalVelocity(const Vec &y, Vec &v) const {
  v = this->v + dH * y;
}

void Parcel::getShapeFunctionDerivatives(const Vec &y, double f, Vec &dfdx, Vec &dfdH) const {
  ShapeFunction::diff(y, dfdx);
  dfdx = - invH.t() * dfdx / detH;
  dfdH = dfdx * y.t() - f * invH.t();
}

void Parcel::afterMatrixChanged() {
  detH = det(H);
  invH = inv(H);
  svd(U, S, V, H);
}

}
