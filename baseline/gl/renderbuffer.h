#ifndef BASELINE_GL_RENDERBUFFER_H
#define BASELINE_GL_RENDERBUFFER_H

#include "gl/texture.h"
#include "glad/glad.h"
#include <vector>

namespace baseline {
    namespace gl {
        class Renderbuffer {
           public:
            class Binding {
               public:
                Binding(GLenum target, GLuint id)
                : target_(target)
                , id_(id)
                {
                    Bind(this->target(), this->id());
                }

                Binding(const Binding &src) = delete;

                Binding(Binding &&src)
                : target_(src.target_)
                {
                    id_ = std::exchange(src.id_, 0u);
                }

                Binding &operator=(Binding &&) = delete;

                Binding &&Storage(GLenum internal_format, GLsizei width, GLsizei height)
                {
                    glRenderbufferStorage(target(), internal_format, width, height);
                    return std::move(*this);
                }
                ~Binding() { Unbind(); }
                GLenum target() const { return target_; }
                GLuint id() const { return id_; }
                operator GLuint() const { return id(); }
               private:
                static void Bind(GLenum target, GLuint id) { glBindRenderbuffer(target, id); }
                void Unbind()
                {
                    if (id() != 0u) {
                        Bind(target(), 0u);
                    }
                }
                GLenum target_;
                GLuint id_;
            };

            Renderbuffer()
            : id_(0u)
            {
                Gen();
            }

            Renderbuffer(const Renderbuffer &src) = delete;
            Renderbuffer(Renderbuffer &&src) { id_ = std::exchange(src.id_, 0u); }
            Renderbuffer &operator=(Renderbuffer &&src)
            {
                Delete();
                id_ = std::exchange(src.id_, 0u);
                return *this;
            }
            ~Renderbuffer() { Delete(); }
            Binding Bind() { return Binding(GL_RENDERBUFFER, id()); }
            GLuint id() const { return id_; }
            operator GLuint() const & { return id(); }
           private:
            void Gen() { glGenRenderbuffers(1, &id_); }
            void Delete()
            {
                if (id_ != 0u) {
                    glDeleteRenderbuffers(1, &id_);
                }
            }
            GLuint id_;
        };
    }
}

#endif
