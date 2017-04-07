#ifndef BASELINE_DRAW_FRUSTUM_H
#define BASELINE_DRAW_FRUSTUM_H

namespace baseline {
    namespace draw {
        class Frustum {
           public:
            Frustum(float near = 0.1f, float far = 100.f)
            : Frustum(0.f, 0.f, 0.f, 0.f, near, far)
            {
            }

            Frustum(float left, float right, float bottom, float top, float near, float far)
            : left_(left)
            , right_(right)
            , bottom_(bottom)
            , top_(top)
            , near_(near)
            , far_(far)
            {
            }

            static Frustum Default() { return Frustum(-1.f, 1.f, -1.f, 1.f, -100.f, 100.f); }
            float left() const { return left_; }
            float right() const { return right_; }
            float bottom() const { return bottom_; }
            float top() const { return top_; }
            float near() const { return near_; }
            float far() const { return far_; }
           protected:
            float left_;
            float right_;
            float bottom_;
            float top_;
            float near_;
            float far_;
        };
    }
}
#endif
