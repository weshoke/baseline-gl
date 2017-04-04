#ifndef BASELINE_GL_UNIFORM_H
#define BASELINE_GL_UNIFORM_H

#include "glad/glad.h"

namespace baseline {
    namespace gl {
        class Uniform {
           public:
            Uniform()
            : id_(-1)
            {
            }

            Uniform(GLint id)
            : id_(id)
            {
            }

            GLint id() const { return id_; }
            operator GLint() { return id(); }
            bool IsValid() const { return id_ >= 0; }
            operator bool() { return IsValid(); }
           private:
            GLint id_;
        };
    }
}

#endif
