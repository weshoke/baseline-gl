#ifndef BASELINE_DRAW_ANALYZED_PROGRAM_H
#define BASELINE_DRAW_ANALYZED_PROGRAM_H

#include "gl/program.h"
#include <memory>
#include <unordered_map>

namespace baseline {
    namespace draw {
        class AnalyzedProgram {
           public:
            AnalyzedProgram(gl::Program &&program);
            AnalyzedProgram(AnalyzedProgram &&src);
            AnalyzedProgram &operator=(AnalyzedProgram &&src);

            gl::Uniform GetUniform(const std::string &name);
            gl::Program &program() { return program_; }
            operator GLuint() { return GLuint(program()); }
           private:
            void Setup();
            void StoreNonBlockUniformNames();

            gl::Program program_;
            std::unordered_map<std::string, gl::Uniform> uniform_names_;
        };
    }
}

#endif
