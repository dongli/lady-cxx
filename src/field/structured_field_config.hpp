#ifndef __LADY_StructuredFieldConfig
#define __LADY_StructuredFieldConfig

#include "field_config.hpp"

namespace lady {

enum StructuredFieldElementStagger {
  CENTER, VERTEX, FACE_CENTER
};

template <int NUM_DIM, template <int ...> class MeshConfigTemplate>
class StructuredFieldConfig : public FieldConfig<NUM_DIM, MeshConfigTemplate> {
public:
  StructuredFieldElementStagger stagger;

  StructuredFieldConfig(const MeshConfigTemplate<NUM_DIM> &meshConfig);
  virtual ~StructuredFieldConfig();
};

}

#endif
