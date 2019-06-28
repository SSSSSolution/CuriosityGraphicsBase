#ifndef GRAPHICS_IMOVEABLE_H
#define GRAPHICS_IMOVEABLE_H

#include "object_interface/idrawable.h"

namespace curiosity {
    namespace graphics {

    class IMoveable : public IDrawable {
    public:
        virtual ~IMoveable() {}
        virtual void move() = 0;
    };

    }
}

#endif
