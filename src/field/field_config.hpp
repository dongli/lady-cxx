#ifndef __LADY_FieldConfig
#define __LADY_FieldConfig

#include "common.hpp"
#include "mesh_config.hpp"

namespace lady {

template <class MeshConfigType>
class FieldConfig {
  const MeshConfigType *_meshConfig;
public:
  FieldConfig(const MeshConfigType &meshConfig) {
    _meshConfig = &meshConfig;
  }
  virtual ~FieldConfig() {}

  const MeshConfigType& meshConfig() const { return *_meshConfig; }
};

}

#endif
