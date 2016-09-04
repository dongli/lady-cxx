#include "quad_points.hpp"
#include "shape_function.hpp"
#include "parcel.hpp"
#include "cartesian_domain.hpp"

namespace lady {

template class QuadPoints<2>;
template class QuadPoints<3>;

template <int NUM_DIM>
vector<vec::fixed<NUM_DIM>> QuadPoints<NUM_DIM>::y;
template <int NUM_DIM>
vec QuadPoints<NUM_DIM>::w;
template <int NUM_DIM>
vec QuadPoints<NUM_DIM>::f;
template <int NUM_DIM>
size_t QuadPoints<NUM_DIM>::num;

template <int NUM_DIM>
QuadPoints<NUM_DIM>::QuadPoints() {
}

template <int NUM_DIM>
QuadPoints<NUM_DIM>::~QuadPoints() {
}

template <int NUM_DIM>
void QuadPoints<NUM_DIM>::init() {
  num = pow(ShapeFunction<NUM_DIM>::nodes.size(), NUM_DIM);
  y.resize(num);
  w.set_size(num);
  f.set_size(num);
  w.ones();
  int ai[NUM_DIM];
  double offset;
  for (int qi = 0; qi < num; qi++) {
    offset = 0;
    for (int di = NUM_DIM-1; di >= 0; di--) {
      if (di != NUM_DIM-1) {
        offset += ai[di+1] * pow(ShapeFunction<NUM_DIM>::nodes.size(), di+1);
      }
      ai[di] = floor(static_cast<double>(qi-offset) / pow(ShapeFunction<NUM_DIM>::nodes.size(), di));
      y[qi][di] = ShapeFunction<NUM_DIM>::nodes[ai[di]];
      w[qi] *= ShapeFunction<NUM_DIM>::weights[ai[di]];
    }
    ShapeFunction<NUM_DIM>::eval(y[qi], f[qi]);
  }
}

template <int NUM_DIM>
void QuadPoints<NUM_DIM>::init(Parcel<NUM_DIM> *parcel) {
  hostParcel = parcel;
  x.resize(num);
  v.resize(x.size());
  rho.set_size(x.size());
  T.set_size(x.size());
}

template <int NUM_DIM>
template <class DomainType>
void QuadPoints<NUM_DIM>::update(const DomainType &domain) {
  vec::fixed<NUM_DIM> y, v;
  double f;
  rho.zeros();
  T.zeros();
  for (int qi = 0; qi < num; qi++) {
    this->v[qi].zeros();
    hostParcel->getSpaceCoord(domain, this->y[qi], x[qi]);
    for (int ni = 0; ni < hostParcel->numNeighbor; ni++) {
      Parcel<NUM_DIM> *neighbor = hostParcel->neighbors[ni];
      neighbor->getBodyCoord(domain, x[qi], y);
      ShapeFunction<NUM_DIM>::eval(y, f);
      if (std::abs(f) < 1.0e-16) continue;
      neighbor->getLocalVelocity(y, v);
      f *= neighbor->m / neighbor->detH;
      this->rho[qi] += f;
      this->T[qi] += f * neighbor->u;
      this->v[qi] += f * v;
    }
    // Include host parcel effects.
    hostParcel->getLocalVelocity(QuadPoints<NUM_DIM>::y[qi], v);
    f = QuadPoints<NUM_DIM>::f[qi] * hostParcel->m / hostParcel->detH;
    this->rho[qi] += f;
    this->T[qi] += f * hostParcel->u;
    this->v[qi] += f * v;

    this->T[qi] /= CV * this->rho[qi];
    this->v[qi] /= this->rho[qi];
  }
}

template void QuadPoints<2>::update<CartesianDomain<2>>(const CartesianDomain<2> &domain);
template void QuadPoints<3>::update<CartesianDomain<3>>(const CartesianDomain<3> &domain);

}
