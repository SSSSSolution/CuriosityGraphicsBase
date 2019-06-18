#include "drawableobject.h"

namespace curiosity {
    namespace graphics {

    DrawableObject::DrawableObject(Vec3 &position, unsigned int length)
        :   position_(position), length_(length) {
    }

    }
}
