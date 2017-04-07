#ifndef BASELINE_DRAW_UNIFORM_MAP_H
#define BASELINE_DRAW_UNIFORM_MAP_H

#include "analyzed_program.h"
#include "glad/glad.h"
#include "mpark/variant.hpp"
#include "primitives.h"
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

namespace baseline {
    namespace draw {
        class UniformMap {
           public:
            // Large union type that wastes space but provides a nice interface
            // Under the hood, values will be packed into a tight buffer.
            using Value = mpark::variant<GLint, GLfloat, Vec2, Vec3, Vec4, Matrix3, Matrix4>;

           private:
            enum class ValueType { Int = 0, Float, Vec2, Vec3, Vec4, Matrix3, Matrix4 };

            struct Entry {
                ValueType value_type;
                uint32_t index;
            };

            static constexpr ValueType ValueTypeFromValue(const Value &value)
            {
                return static_cast<ValueType>(value.index());
            }

           public:
            UniformMap() {}
            UniformMap &Add(const std::string &name, Value value);

            void Apply(AnalyzedProgram &program);

           private:
            const float *EntryPointer(Entry entry) const;
            static uint32_t ValueTypeCount(ValueType value_type);
            static const void *ValueData(const Value &value);
            uint32_t AppendValue(const Value &value);

            static void Apply(gl::Uniform uniform, ValueType value_type, const void *value);

            std::vector<float> values_;
            std::unordered_map<std::string, Entry> uniforms_;
        };
    }
}

#endif
