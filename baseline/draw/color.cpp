#include "color.h"

namespace baseline {
    namespace draw {
        uint32_t Color(Vec3 rgb, float a)
        {
            return detail::Convert(rgb[0]) << 24 | detail::Convert(rgb[1]) << 16 |
                   detail::Convert(rgb[2]) << 8 | detail::Convert(a);
        }

        uint32_t Color(Vec4 rgba)
        {
            return detail::Convert(rgba[0]) << 24 | detail::Convert(rgba[1]) << 16 |
                   detail::Convert(rgba[2]) << 8 | detail::Convert(rgba[3]);
        }

        Vec4 ColorComponents(uint32_t color)
        {
            return Vec4(detail::Convert(color >> 24),
                        detail::Convert(color >> 16),
                        detail::Convert(color >> 8),
                        detail::Convert(color));
        }

        const uint32_t Colors::orange = Color(0xff5f2eu);
        const uint32_t Colors::yellow = Color(0xfcbe32u);
        const uint32_t Colors::navy = Color(0x004e66u);
        const uint32_t Colors::sky = Color(0x47b8e0u);
        const uint32_t Colors::grass = Color(0x3ac569u);
        const uint32_t Colors::red = Color(0xff3333u);
        const uint32_t Colors::cream = Color(0xf0f5f9u);
        const uint32_t Colors::grey = Color(0xbbbbbbu);
        const uint32_t Colors::black = Color(0x000000u);
        const uint32_t Colors::slate_grey = Color(0x708090u);
        const uint32_t Colors::indigo = Color(0x4b0082u);
        const uint32_t Colors::dark_violet = Color(0x9400d3u);
        const uint32_t Colors::orchid = Color(0xda70d6u);
        const uint32_t Colors::tomato = Color(0xff6347u);
        const uint32_t Colors::porcelain = Color(0xedededu);
        const uint32_t Colors::plum = Color(0xdda0ddu);
        const uint32_t Colors::light_cyan = Color(0xe0ffffu);
        const uint32_t Colors::lemon_chiffon = Color(0xfffacdu);
        const uint32_t Colors::cadet_blue = Color(0x5f9ea0u);
        const uint32_t Colors::hot_pink = Color(0xff69b4u);
        const uint32_t Colors::white = Color(0xffffffu);
        const uint32_t Colors::chromium = Color(0xedededu);
    }
}
