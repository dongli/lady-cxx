#ifndef __LADY_StructuredFieldConfig
#define __LADY_StructuredFieldConfig

#include "field_config.hpp"

namespace lady {

enum StructuredFieldElementStagger {
  CENTER, VERTEX, FACE_CENTER
};

class StructuredFieldConfig : public FieldConfig<StructuredMeshConfig> {
public:
  StructuredFieldElementStagger stagger;

  StructuredFieldConfig(const StructuredMeshConfig &meshConfig);
  virtual ~StructuredFieldConfig();
};

}

#endif
