#ifndef SPACE_BASELINE_DRAW_RENDERABLE_H
#define SPACE_BASELINE_DRAW_RENDERABLE_H

#include "context.h"
#include "draw.h"
#include "geom/matrix4.h"
#include "pipeline.h"
#include "uniform_map.h"
#include <memory>
#include <vector>

namespace baseline {
    namespace draw {
        class Renderable {
           public:
            using Ref = std::shared_ptr<Renderable>;

            virtual void Draw() = 0;
        };

        class ExplicitRenderable final : public Renderable {
           public:
            ExplicitRenderable(
                Pipeline &&pipeline,
                GLenum primitive,
                uint32_t color,
                Matrix4 model = Matrix4::Identity(),
                UniformMap uniforms = UniformMap(),
                std::vector<Context::TextureRef> textures = std::vector<Context::TextureRef>());
            virtual ~ExplicitRenderable() {}
            void Draw();

           private:
            Pipeline pipeline_;
            uint64_t primitive_;
            uint32_t color_;
            Matrix4 model_;
            UniformMap uniforms_;
            std::vector<Context::TextureRef> textures_;
        };
    }
}

#endif
