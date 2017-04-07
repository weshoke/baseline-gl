#ifndef BASELINE_DRAW_DRAW_H
#define BASELINE_DRAW_DRAW_H

#include <array>

namespace baseline {
namespace draw {
void ClearWindowWithDepth(std::array<uint32_t, 2> window_size, uint32_t color);
}
}

#endif
