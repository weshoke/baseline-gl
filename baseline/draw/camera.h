#ifndef BASELINE_DRAW_CAMERA_H
#define BASELINE_DRAW_CAMERA_H

#include "frustum.h"
#include "primitives.h"

namespace baseline {
    namespace draw {
        class Camera {
           public:
            enum class Mode { Projective = 0, Orthographic };

            Camera(const Vec3 &eye, const Vec3 &look_at, const Vec3 &up, float lens_angle)
            : Camera(eye, look_at, up, lens_angle, 1.f, 0.1f, 100.f)
            {
            }

            Camera(const Vec3 &eye,
                   const Vec3 &look_at,
                   const Vec3 &up,
                   float lens_angle,
                   float aspect)
            : Camera(eye, look_at, up, lens_angle, aspect, 0.1f, 100.f)
            {
            }

            Camera(const Vec3 &eye,
                   const Vec3 &look_at,
                   const Vec3 &up,
                   float lens_angle,
                   float aspect,
                   float near,
                   float far)
            : mode_(Mode::Projective)
            , eye_(eye)
            , look_at_(look_at)
            , up_(up)
            , lens_angle_(lens_angle)
            , aspect_(aspect)
            , frustum_(near, far)
            {
            }

            Camera(const Vec3 &eye, const Vec3 &look_at, const Vec3 &up, const Frustum &frustum)
            : mode_(Mode::Orthographic)
            , eye_(eye)
            , look_at_(look_at)
            , up_(up)
            , lens_angle_(0.f)
            , aspect_(0.f)
            , frustum_(frustum)
            {
            }

            static Camera Default(float aspect = 1.f)
            {
                return Camera(
                    Vec3(0.f, 0.f, -6.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f), 35.f, aspect);
            }

            static Camera Ortho(const Frustum &frustum)
            {
                return Camera(
                    Vec3(0.f, 0.f, 0.f), Vec3(0.f, 0.f, 1.f), Vec3(0.f, 1.f, 0.f), frustum);
            }

            Vec3 Look() const { return (look_at() - eye()).Normalized(); }
            Vec3 Pan() const { return math::CrossProduct(up(), Look()); }
            template <class Rot>
            void Spin(const Rot &rot)
            {
                auto to_eye = eye() - look_at();
                eye_ = look_at() + to_eye.Spin(rot);
                up_ = up_.Spin(rot);
            }

            void Translate(const Vec3 &v)
            {
                eye_ = eye_ + v;
                look_at_ = look_at_ + v;
            }

            Matrix4 ViewMatrix() const { return Matrix4::LookAt(eye(), look_at(), up()); }
            Matrix4 ProjectionMatrix() const
            {
                if (mode() == Mode::Projective) {
                    return Matrix4::Perspective(lens_angle(), aspect(), near(), far());
                }
                return Matrix4::Ortho(left(), right(), bottom(), top(), near(), far());
            }

            Mode mode() const { return mode_; }
            const Vec3 &eye() const { return eye_; }
            const Vec3 &look_at() const { return look_at_; }
            const Vec3 &up() const { return up_; }
            float lens_angle() const { return lens_angle_; }
            float aspect() const { return aspect_; }
            const Frustum &frustum() const { return frustum_; }
           protected:
            Mode mode_;
            Vec3 eye_;
            Vec3 look_at_;
            Vec3 up_;
            Frustum frustum_;
        };
    }
}
#endif
