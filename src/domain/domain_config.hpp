#ifndef __LADY_DomainConfig
#define __LADY_DomainConfig

#include "common.hpp"

namespace lady {

enum AxisBoundaryType {
  OPEN, PERIODIC, RIGID
};

template <int NUM_DIM>
class DomainConfig {
public:
  field<AxisBoundaryType> axisBoundaryTypes;
  vec::fixed<NUM_DIM> axisStartCoords;
  vec::fixed<NUM_DIM> axisEndCoords;
  vec::fixed<NUM_DIM> axisSpans;

  DomainConfig();

  DomainConfig<NUM_DIM>& operator=(const DomainConfig<NUM_DIM> &);
};

}

#endif
