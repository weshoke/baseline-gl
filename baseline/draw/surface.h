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
                    std::vector<Context::TextureRef>&& color_buffers)
            : size_(size)
            , clear_color_(0u)
            , framebuffer_(std::move(framebuffer))
            , depth_buffer_(std::move(depth_buffer))
            , color_buffers_(std::move(color_buffers))
            {
            }

            static Surface Create(uint32_t width, uint32_t height)
            {
                return Create(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, width, height);
            }

            static Surface Create(
                GLenum internal_format, GLenum format, GLenum type, uint32_t width, uint32_t height)
            {
                auto color_buffer = std::make_shared<gl::Texture>();
                color_buffer->Bind()
                    .Image(internal_format, format, type, width, height)
                    .Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
                    .Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                auto depth_buffer = gl::Renderbuffer();
                depth_buffer.Bind().Storage(GL_DEPTH_COMPONENT, width, height);

                auto framebuffer = gl::Framebuffer();
                framebuffer.Bind(GL_FRAMEBUFFER)
                    .Renderbuffer(GL_DEPTH_ATTACHMENT, depth_buffer)
                    .Texture(GL_COLOR_ATTACHMENT0, *color_buffer);

                return Surface({width, height},
                               std::move(framebuffer),
                               std::move(depth_buffer),
                               {color_buffer});
            }

            template <class F>
            void Draw(const Camera& camera, F&& draw)
            {
                auto binding = framebuffer_.Bind(GL_FRAMEBUFFER);
                viz::draw::ClearWindowWithDepth(size(), clear_color());
                viz::draw::Context::Get().ApplyCamera(camera);
                viz::draw::Context::Get().ScreenSize(size());
                draw();
            }

            //            std::vector<uint32_t> Image()
            //            {
            //                auto image = std::vector<uint32_t>(PixelCount(), 0u);
            //                color_buffers_[0]->Bind().GetImage(GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
            //                image);
            //                return image;
            //            }

            std::vector<Vec4> Image()
            {
                auto image = std::vector<Vec4>(PixelCount());
                color_buffers_[0]->Bind().GetImage(GL_RGBA, GL_FLOAT, image);
                return image;
            }

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
