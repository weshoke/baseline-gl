#ifndef BASELINE_DRAW_SURFACE_H
#define BASELINE_DRAW_SURFACE_H

#include "camera.h"
#include "context.h"
#include "gl/framebuffer.h"
#include "gl/renderbuffer.h"
#include "gl/texture.h"
#include "primitives.h"

namespace baseline {
    namespace draw {
        class Surface {
           public:
            Surface(std::array<uint32_t, 2> size,
                    gl::Framebuffer&& framebuffer,
                    gl::Renderbuffer&& depth_buffer,
                    std::vector<Context::TextureRef>&& color_buffers);

            static Surface Create(uint32_t width, uint32_t height);
            static Surface Create(GLenum internal_format,
                                  GLenum format,
                                  GLenum type,
                                  uint32_t width,
                                  uint32_t height);

            template <class F>
            void Draw(const Camera& camera, F&& draw)
            {
                auto binding = framebuffer_.Bind(GL_FRAMEBUFFER);
                draw::ClearWindowWithDepth(size(), clear_color());
                draw::Context::Get().ApplyCamera(camera);
                draw::Context::Get().ScreenSize(size());
                draw();
            }

            std::vector<Vec4> Image();

            uint32_t PixelCount() const { return size()[0] * size()[1]; }
            Context::TextureRef ColorBuffer(uint32_t idx = 0) { return color_buffers_[idx]; }
            const std::array<uint32_t, 2>& size() const { return size_; }
            uint32_t clear_color() const { return clear_color_; }
           private:
            std::array<uint32_t, 2> size_;
            uint32_t clear_color_;
            gl::Framebuffer framebuffer_;
            gl::Renderbuffer depth_buffer_;
            std::vector<Context::TextureRef> color_buffers_;
        };
    }
}

#endif
