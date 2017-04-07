#ifndef BASELINE_DRAW_RENDERABLE_FACTORY_H
#define BASELINE_DRAW_RENDERABLE_FACTORY_H

#include "draw.h"
#include "mesh.h"
#include "renderable.h"
#include <vector>

namespace baseline {
namespace draw {
Renderable::Ref Create(Mesh &&mesh, uint32_t color, const std::string &program,
                       GLenum primitve, Matrix4 model = Matrix4::Identity(),
                       UniformMap uniforms = UniformMap(),
                       std::vector<Context::TextureRef> textures =
                           std::vector<Context::TextureRef>());
}
}

#endif
