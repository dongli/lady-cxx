#include "cartesian_domain.hpp"

namespace lady {

Vec CartesianDomain::diffCoord(const Vec &x, const Vec &y) const {
  Vec res = x - y;
  double tmp1, tmp2;
  for (int di = 0; di < NUM_DIM; di++) {
    if (_domainConfig->axisBoundaryTypes[di] == PERIODIC) {
      tmp1 = fabs(res[di]);
      tmp2 = _domainConfig->axisEndCoords[di] - _domainConfig->axisStartCoords[di] - tmp1;
      if (tmp1 > tmp2) {
        res[di] = res[di] > 0 ? -tmp2 : tmp2;
      }
    }
  }
  return res;
}

double CartesianDomain::distance(const Vec &x, const Vec &y) const {
  return norm(diffCoord(x, y));
}

}
