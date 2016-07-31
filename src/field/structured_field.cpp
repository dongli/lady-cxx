#include "structured_field.hpp"
#include "structured_mesh_config.hpp"

namespace lady {

StructuredField::StructuredField() {
}

StructuredField::~StructuredField() {
}

void StructuredField::init(const StructuredFieldConfig &fieldConfig) {
  if (NUM_DIM == 2) {
    _data.set_size(fieldConfig.meshConfig().numGridAlongEachAxis[0],
                   fieldConfig.meshConfig().numGridAlongEachAxis[1]);
  } else if (NUM_DIM == 3) {
    _data.set_size(fieldConfig.meshConfig().numGridAlongEachAxis[0],
                   fieldConfig.meshConfig().numGridAlongEachAxis[1],
                   fieldConfig.meshConfig().numGridAlongEachAxis[2]);
  }
}

}
