#ifndef BASELINE_GL_NAME_H
#define BASELINE_GL_NAME_H

namespace baseline {
    namespace gl {
        template <class Entity, class Binding>
        class Name {
           public:
            friend Entity;

            Name()
            : id_(0u)
            {
                Entity::Gen(*this);
            }
            Name(const Name& src) = delete;
            Name(Name&& src) { id_ = std::exchange(src.id_, 0u); }
            Name& operator=(Name&& src)
            {
                Entity::Delete();
                id_ = std::exchange(src.id_, 0u);
                return *this;
            }

            ~Name() { Delete(); }
            Binding Bind() { return Binding(id()); }
            GLuint id() const { return id_; }
            operator GLuint() { return id(); }
           private:
            GLuint& id() { return id_; }
            void Delete()
            {
                if (id() != 0u) {
                    Entity::Delete(*this);
                }
            }

            GLuint id_;
        };
    }
}

#endif
