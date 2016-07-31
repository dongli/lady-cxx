#ifndef __LADY_DomainConfig
#define __LADY_DomainConfig

#include "common.hpp"

namespace lady {

enum AxisBoundaryType {
  OPEN, PERIODIC, RIGID
};

class DomainConfig {
public:
  field<AxisBoundaryType> axisBoundaryTypes;
  Vec axisStartCoords;
  Vec axisEndCoords;

  DomainConfig() {
    axisBoundaryTypes.set_size(NUM_DIM);
  }
};

}

#endif
