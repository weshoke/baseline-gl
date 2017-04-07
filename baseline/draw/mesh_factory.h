#ifndef BASELINE_DRAW_MESH_FACTORY_H
#define BASELINE_DRAW_MESH_FACTORY_H

#include "mesh.h"

namespace baseline {
namespace draw {
Mesh CreateIcosohedron();
Mesh CreateExtrudedPolygon(uint32_t sides, float height = 1.f);
}
}

#endif
