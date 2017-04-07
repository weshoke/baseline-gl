#include "surface.h"

namespace baseline {
    namespace draw {
        Surface::Surface(std::array<uint32_t, 2> size,
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

        Surface Surface::Create(uint32_t width, uint32_t height)
        {
            return Create(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, width, height);
        }

        Surface Surface::Create(
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

            return Surface(
                {width, height}, std::move(framebuffer), std::move(depth_buffer), {color_buffer});
        }

        std::vector<Vec4> Surface::Image()
        {
            auto image = std::vector<Vec4>(PixelCount());
            color_buffers_[0]->Bind().GetImage(GL_RGBA, GL_FLOAT, image);
            return image;
        }
    }
}
