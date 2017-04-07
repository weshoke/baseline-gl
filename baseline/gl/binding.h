#ifndef BASELINE_GL_BINDING_H
#define BASELINE_GL_BINDING_H

namespace baseline {
    namespace gl {
        template <class Entity>
        class Binding {
           public:
            Binding(GLuint id)
            : id_(id)
            {
                Entity::Bind(this->id());
            }

            Binding(const Binding& src) = delete;
            Binding(Binding&& src) { id_ = std::exchange(src.id_, 0u); }
            Binding& operator=(Binding&& src)
            {
                Unbind();
                id_ = std::exchange(src.id_, 0u);
            }
            ~Binding() { Unbind(); }
            GLuint id() const { return id_; }
            operator GLuint() { return id(); }
           private:
            void Unbind()
            {
                if (id() != 0u) {
                    Entity::Bind(0u);
                }
            }
            GLuint id_;
        };
    }
}

#endif
