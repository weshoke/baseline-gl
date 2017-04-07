#include "uniform_map.h"
#include "glad/glad.h"

namespace baseline {
    namespace draw {

        UniformMap &UniformMap::Add(const std::string &name, Value value)
        {
            uniforms_.emplace(name, Entry{ValueTypeFromValue(value), AppendValue(value)});
            return *this;
        }

        void UniformMap::Apply(AnalyzedProgram &program)
        {
            for (const auto &p : uniforms_) {
                auto uniform = program.GetUniform(std::get<0>(p));
                if (uniform.IsValid()) {
                    auto entry = std::get<1>(p);
                    Apply(uniform, entry.value_type, EntryPointer(entry));
                }
            }
        }

        const float *UniformMap::EntryPointer(Entry entry) const
        {
            return values_.data() + entry.index;
        }
        uint32_t UniformMap::ValueTypeCount(ValueType value_type)
        {
            switch (value_type) {
                case ValueType::Int:
                    return 1u;
                case ValueType::Float:
                    return 1u;
                case ValueType::Vec2:
                    return 2u;
                case ValueType::Vec3:
                    return 3u;
                case ValueType::Vec4:
                    return 4u;
                case ValueType::Matrix3:
                    return 9u;
                case ValueType::Matrix4:
                    return 16u;
            }
            return 0u;
        }

        const void *UniformMap::ValueData(const Value &value)
        {
            // TODO: use ValueType enums
            switch (value.index()) {
                case 0:
                    return &mpark::get<0>(value);
                case 1:
                    return &mpark::get<1>(value);
                case 2:
                    return mpark::get<2>(value).Data();
                case 3:
                    return mpark::get<3>(value).Data();
                case 4:
                    return mpark::get<4>(value).Data();
                case 5:
                    return mpark::get<5>(value).Data();
                case 6:
                    return mpark::get<6>(value).Data();
                default:
                    break;
            }
            return nullptr;
        }

        uint32_t UniformMap::AppendValue(const Value &value)
        {
            auto offset = size_t(values_.size());
            auto count = ValueTypeCount(ValueTypeFromValue(value));
            values_.resize(offset + count);
            // TODO: in term of bytes
            std::memcpy(values_.data() + offset, ValueData(value), count * sizeof(float));
            return offset;
        }

        void UniformMap::Apply(gl::Uniform uniform, ValueType value_type, const void *value)
        {
            switch (value_type) {
                case ValueType::Int:
                    glUniform1iv(uniform, 1, (const GLint *)value);
                    break;
                case ValueType::Float:
                    glUniform1fv(uniform, 1, (const GLfloat *)value);
                    break;
                case ValueType::Vec2:
                    glUniform2fv(uniform, 1, (const GLfloat *)value);
                    break;
                case ValueType::Vec3:
                    glUniform3fv(uniform, 1, (const GLfloat *)value);
                    break;
                case ValueType::Vec4:
                    glUniform4fv(uniform, 1, (const GLfloat *)value);
                    break;
                case ValueType::Matrix3:
                    glUniformMatrix3fv(uniform, 1, GL_FALSE, (const GLfloat *)value);
                    break;
                case ValueType::Matrix4:
                    glUniformMatrix4fv(uniform, 1, GL_FALSE, (const GLfloat *)value);
                    break;
            }
        }
    }
}
