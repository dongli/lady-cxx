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
QuadPoints<NUM_DIM>::QuadPoints() {
}

template <int NUM_DIM>
QuadPoints<NUM_DIM>::~QuadPoints() {
}

template <int NUM_DIM>
void QuadPoints<NUM_DIM>::init() {
  y.resize(pow(ShapeFunction<NUM_DIM>::nodes.size(), NUM_DIM));
  w.set_size(y.size());
  w.ones();
  int ai[NUM_DIM];
  double offset;
  for (int qi = 0; qi < y.size(); qi++) {
    offset = 0;
    for (int di = NUM_DIM-1; di >= 0; di--) {
      if (di != NUM_DIM-1) {
        offset += ai[di+1] * pow(ShapeFunction<NUM_DIM>::nodes.size(), di+1);
      }
      ai[di] = floor(static_cast<double>(qi-offset) / pow(ShapeFunction<NUM_DIM>::nodes.size(), di));
      y[qi][di] = ShapeFunction<NUM_DIM>::nodes[ai[di]];
      w[qi] *= ShapeFunction<NUM_DIM>::weights[ai[di]];
    }
  }
}

template <int NUM_DIM>
void QuadPoints<NUM_DIM>::init(Parcel<NUM_DIM> *parcel) {
  hostParcel = parcel;
  x.resize(pow(ShapeFunction<NUM_DIM>::nodes.size(), NUM_DIM));
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
  for (int qi = 0; qi < this->y.size(); qi++) {
    hostParcel->getSpaceCoord(domain, this->y[qi], x[qi]);
    for (int ni = 0; ni < hostParcel->numNeighbor; ni++) {
      Parcel<NUM_DIM> *neighbor = hostParcel->neighbors[ni];
      neighbor->getBodyCoord(domain, x[qi], y);
      ShapeFunction<NUM_DIM>::eval(y, f);
      if (f == 0) continue;
      neighbor->getLocalVelocity(y, v);
      f *= neighbor->m / neighbor->detH;
      this->rho[qi] += f;
      this->T[qi] += f * neighbor->u;
      this->v[qi] += f * v;
    }
    this->T[qi] /= CV * this->rho[qi];
    this->v[qi] /= this->rho[qi];
  }
}

template void QuadPoints<2>::update<CartesianDomain<2>>(const CartesianDomain<2> &domain);

}
