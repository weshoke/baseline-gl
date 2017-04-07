#include "analyzed_program.h"

namespace baseline {
namespace draw {
  AnalyzedProgram::AnalyzedProgram(gl::Program &&program) : program_(std::move(program)) {
    Setup();
  }

  AnalyzedProgram::AnalyzedProgram(AnalyzedProgram &&src)
      : program_(std::move(src.program_)),
        uniform_names_(std::move(src.uniform_names_)) {}

  AnalyzedProgram & AnalyzedProgram::operator=(AnalyzedProgram &&src) {
    program_ = std::move(src.program_);
    uniform_names_ = std::move(src.uniform_names_);
    return *this;
  }

  gl::Uniform AnalyzedProgram::GetUniform(const std::string &name) {
    auto it = uniform_names_.find(name);
    return it == uniform_names_.end() ? gl::Uniform() : std::get<1>(*it);
  }


  void AnalyzedProgram::Setup() { StoreNonBlockUniformNames(); }
  void AnalyzedProgram::StoreNonBlockUniformNames() {
    auto count = program().Get(GL_ACTIVE_UNIFORMS);
    uniform_names_.reserve(count);
    for (auto i = 0; i < count; ++i) {
      constexpr auto max_name_size = GLsizei{512};
      auto name = std::array<char, max_name_size>();
      auto name_size = GLsizei{0};
      glGetActiveUniformName(program(), i, max_name_size, &name_size,
                             name.data());
      auto block_index = glGetUniformBlockIndex(program(), name.data());
      if (block_index == GL_INVALID_INDEX) {
        auto uniform_name = std::string(name.data());
        uniform_names_.emplace(uniform_name,
                               program().GetUniform(uniform_name));
      }
    }
  }
}
}
