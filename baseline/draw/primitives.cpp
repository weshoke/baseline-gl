#include "primitives.h"

namespace baseline {
    namespace draw {
        template <>
        int32_t Size<Vec2>()
        {
            return 2;
        }
        template <>
        int32_t Size<Vec3>()
        {
            return 3;
        }
    }
}
