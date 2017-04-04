#ifndef BASELINE_GL_SHADER_H
#define BASELINE_GL_SHADER_H

#include "glad/glad.h"
#include "primitives.h"
#include <iostream>
#include <string>
#include <utility>

namespace baseline {
    namespace gl {
        class Shader {
           public:
            Shader(GLenum type)
            : id_(Create(type))
            {
            }

            Shader(const Shader& src) = delete;
            Shader(Shader&& src) { id_ = std::exchange(src.id_, 0u); }
            Shader& operator=(Shader&& src)
            {
                Delete();
                id_ = std::exchange(src.id_, 0u);
                return *this;
            }
            ~Shader() { Delete(); }
            Shader&& Source(const std::string& source)
            {
                const auto* data = source.data();
                glShaderSource(id(), 1, &data, nullptr);
                return std::move(*this);
            }

            Shader&& Source(const std::vector<std::string>& source)
            {
                auto ptrs = std::vector<const GLchar*>();
                ptrs.reserve(source.size());
                std::transform(
                    source.begin(), source.end(), std::back_inserter(ptrs), [](const auto& s) {
                        return s.data();
                    });

                glShaderSource(id(), ptrs.size(), ptrs.data(), nullptr);
                return std::move(*this);
            }

            Shader&& Compile()
            {
                glCompileShader(id());
                return std::move(*this);
            }

            Shader&& Verify()
            {
                if (!Compiled()) {
                    std::cout << Log() << "\n";
                }
                return std::move(*this);
            }

            GLint Get(GLenum pname) const
            {
                GLint v;
                glGetShaderiv(id(), pname, &v);
                return v;
            }

            bool Compiled() const { return !!Get(GL_COMPILE_STATUS); }
            std::string Log() const
            {
                return GlslLog(id(), Get(GL_INFO_LOG_LENGTH), glGetShaderInfoLog);
            }
            GLuint id() const { return id_; }
            operator GLuint() { return id(); }
           private:
            static GLuint Create(GLenum type) { return glCreateShader(type); }
            void Delete()
            {
                if (id() != 0u) {
                    glDeleteShader(id());
                }
            }
            GLuint id_;
        };
    }
}

#endif
