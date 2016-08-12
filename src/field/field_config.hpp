#ifndef __LADY_FieldConfig
#define __LADY_FieldConfig

#include "common.hpp"

namespace lady {

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
class FieldConfig {
public:
  typedef MeshConfigTemplate<NUM_DIM> MeshConfigType;
private:
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
