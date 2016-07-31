#include "quad_points.hpp"
#include "shape_function.hpp"
#include "parcel.hpp"

namespace lady {

vector<Vec> QuadPoints::y;
vec QuadPoints::w;

QuadPoints::QuadPoints() {
}

QuadPoints::~QuadPoints() {
}

void QuadPoints::init() {
  y.resize(pow(ShapeFunction::nodes.size(), NUM_DIM));
  w.set_size(y.size());
  w.ones();
  int ai[NUM_DIM];
  double offset;
  for (int qi = 0; qi < y.size(); qi++) {
    offset = 0;
    for (int di = NUM_DIM-1; di >= 0; di--) {
      if (di != NUM_DIM-1) {
        offset += ai[di+1] * pow(ShapeFunction::nodes.size(), di+1);
      }
      ai[di] = floor(static_cast<double>(qi-offset) / pow(ShapeFunction::nodes.size(), di));
      y[qi][di] = ShapeFunction::nodes[ai[di]];
      w[qi] *= ShapeFunction::weights[ai[di]];
    }
  }
}

void QuadPoints::init(Parcel *parcel) {
  hostParcel = parcel;
  x.resize(pow(ShapeFunction::nodes.size(), NUM_DIM));
  v.resize(x.size());
  rho.set_size(x.size());
  T.set_size(x.size());
}

void QuadPoints::update() {
  Vec y, v;
  double f;
  rho.zeros();
  T.zeros();
  for (int qi = 0; qi < this->y.size(); qi++) {
    hostParcel->getSpaceCoord(this->y[qi], x[qi]);
    for (int ni = 0; ni < hostParcel->numNeighbor; ni++) {
      Parcel *neighbor = hostParcel->neighbors[ni];
      neighbor->getBodyCoord(x[qi], y);
      ShapeFunction::eval(y, f);
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

}
