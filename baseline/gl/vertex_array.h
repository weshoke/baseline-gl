#ifndef BASELINE_GL_VERTEX_ARRAY_H
#define BASELINE_GL_VERTEX_ARRAY_H

#include "binding.h"
#include "glad/glad.h"
#include "name.h"

namespace baseline {
    namespace gl {
        class VertexArrayBinding : public Binding<VertexArrayBinding> {
           private:
            friend Binding<VertexArrayBinding>;
            static void Bind(GLuint id) { glBindVertexArray(id); }
        };

        class VertexArray : public Name<VertexArray, VertexArrayBinding> {
           private:
            using Base = Name<VertexArray, VertexArrayBinding>;
            friend Base;
            static void Gen(Base& base) { glGenVertexArrays(1, &base.id()); }
            static void Delete(Base& base) { glDeleteVertexArrays(1, &base.id()); }
        };
    }
}

#endif
