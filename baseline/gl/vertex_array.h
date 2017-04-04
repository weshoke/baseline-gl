#ifndef BASELINE_GL_VERTEX_ARRAY_H
#define BASELINE_GL_VERTEX_ARRAY_H

#include "glad/glad.h"
#include <utility>

namespace baseline {
    namespace gl {
        class VertexArray {
           public:
            class Binding {
               public:
                Binding(GLuint id)
                : id_(id)
                {
                    Bind(this->id());
                }

                Binding(const Binding& src) = delete;
                Binding(Binding&& src) { id_ = std::exchange(src.id_, 0u); }
                Binding& operator=(Binding&&) = delete;
                ~Binding() { Unbind(); }
                GLuint id() const { return id_; }
                operator GLuint() { return id(); }
               private:
                static void Bind(GLuint id) { glBindVertexArray(id); }
                void Unbind()
                {
                    if (id() != 0u) {
                        Bind(0u);
                    }
                }
                GLuint id_;
            };

            VertexArray()
            : id_(0u)
            {
                Gen();
            }

            VertexArray(const VertexArray& src) = delete;

            VertexArray(VertexArray&& src) { id_ = std::exchange(src.id_, 0u); }
            VertexArray& operator=(VertexArray&& src)
            {
                Delete();
                id_ = std::exchange(src.id_, 0u);
                return *this;
            }

            ~VertexArray() { Delete(); }
            Binding Bind() { return Binding(id()); }
            GLuint id() const { return id_; }
            operator GLuint() { return id(); }
           private:
            void Gen() { glGenVertexArrays(1, &id_); }
            void Delete()
            {
                if (id_ != 0u) {
                    glDeleteVertexArrays(1, &id_);
                }
            }
            GLuint id_;
        };
    }
}

#endif
