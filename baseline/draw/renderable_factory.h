#ifndef SPACE_BASELINE_DRAW_RENDERABLE_FACTORY_H
#define SPACE_BASELINE_DRAW_RENDERABLE_FACTORY_H

#include "draw.h"
#include "geom/line_segment.h"
#include "geom/sphere.h"
#include "mesh.h"
#include "renderable.h"
#include <vector>

namespace baseline {
    namespace draw {
        Renderable::Ref CreateGrid2d(const Vec3 &start,
                                     const Vec3 &end,
                                     uint32_t divisions,
                                     uint32_t color);
        Renderable::Ref CreateAxes(float length, uint32_t color);

        template <class T>
        Renderable::Ref Create(const std::vector<T> &points, GLenum primitive, uint32_t color)
        {
            return std::make_shared<ExplicitRenderable>(
                Pipeline::Create("color", points), primitive, color);
        }

        template <class Vec>
        Renderable::Ref Create(const space::geom::LineSegment<Vec> &line_segment, uint32_t color)
        {
            return std::make_shared<ExplicitRenderable>(
                Pipeline::Create("color", line_segment.points()), GL_LINES, color);
        }

        template <class Vec>
        Renderable::Ref Create(const space::geom::Line<Vec> &line,
                               uint32_t color,
                               float extent = 5.f)
        {
            using LineSegment = space::geom::LineSegment<Vec>;
            return Create(LineSegment(line.Point(-extent), line.Point(extent)), color);
        }

        template <class Vec>
        Renderable::Ref Create(const space::geom::Ray<Vec> &ray, uint32_t color, float extent = 5.f)
        {
            using LineSegment = space::geom::LineSegment<Vec>;
            return Create(LineSegment(ray.start(), ray.Point(extent)), color);
        }

        Renderable::Ref Create(const Circle2d &circle, uint32_t color);
        Renderable::Ref Create(const Circle &circle, uint32_t color);

        Renderable::Ref Create(const Point2d &p, uint32_t color);
        Renderable::Ref Create(const Point &p, uint32_t color);
        Renderable::Ref Create(const Vec2 &p, uint32_t color, float radius = 0.05f);
        Renderable::Ref Create(const Vec3 &p, uint32_t color, float radius = 0.05f);
        Renderable::Ref Create(const space::geom::Sphere<Vec3> &sphere, uint32_t color);

        Renderable::Ref Create(
            Mesh &&mesh,
            uint32_t color,
            const std::string &program,
            GLenum primitve,
            Matrix4 model = Matrix4::Identity(),
            UniformMap uniforms = UniformMap(),
            std::vector<Context::TextureRef> textures = std::vector<Context::TextureRef>());
    }
}

#endif
