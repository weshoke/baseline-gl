#include "renderable_factory.h"
#include "mesh_factory.h"
#include "pipeline.h"
#include "primitives.h"
#include <memory>

namespace baseline {
namespace draw {
Renderable::Ref Create(Mesh &&mesh, uint32_t color, const std::string &program,
                       GLenum primitve, Matrix4 model, UniformMap uniforms,
                       std::vector<Context::TextureRef> textures) {
  return std::make_shared<ExplicitRenderable>(
      Pipeline::Create(program, std::move(mesh)), primitve, color, model,
      uniforms, textures);
}
}
}
