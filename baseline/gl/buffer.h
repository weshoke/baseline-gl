#ifndef BASELINE_GL_BUFFER_H
#define BASELINE_GL_BUFFER_H

#include "glad/glad.h"
#include <utility>
#include <vector>

namespace baseline {
    namespace gl {
        class Buffer {
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

                ~Binding() { Unbind(); }
                template <class Data>
                Binding &&Data(const Data &data, GLenum usage = GL_STATIC_DRAW)
                {
                    using T = typename Data::value_type;
                    glBufferData(target(), sizeof(T) * data.size(), data.data(), usage);
                    return std::move(*this);
                }

                void Detach() { id_ = 0u; }
                GLenum target() const { return target_; }
                GLuint id() const { return id_; }
                operator GLint() { return id(); }
               private:
                static void Bind(GLenum target, GLuint id) { glBindBuffer(target, id); }
                void Unbind()
                {
                    if (id() != 0u) {
                        Bind(target(), 0u);
                    }
                }
                GLenum target_;
                GLuint id_;
            };

            Buffer()
            : id_(0u)
            {
                Gen();
            }
            Buffer(const Buffer &) = delete;

            Buffer(Buffer &&src) { id_ = std::exchange(src.id_, 0u); }
            Buffer &operator=(Buffer &&src)
            {
                Delete();
                id_ = std::exchange(src.id_, 0u);
                return *this;
            }
            ~Buffer() { Delete(); }
            Binding Bind(GLenum target) { return Binding(target, id()); }
            template <class F>
            Buffer &&Bind(GLenum target, F &&f)
            {
                f(Binding(target, id()));
                return std::move(*this);
            }

            GLuint id() const { return id_; }
            operator GLint() { return id(); }
           private:
            void Gen() { glGenBuffers(1, &id_); }
            void Delete()
            {
                if (id_ != 0u) {
                    glDeleteBuffers(1, &id_);
                }
            }

            GLuint id_;
        };
    }
}

#endif
