#ifndef GRAPHICS_KDTREE_H
#define GRAPHICS_KDTREE_H
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class KdTree3 {
    public:
        KdTree3() {}
        virtual ~KdTree3();

    public:
        Vec3 high;
        Vec3 low;

        KdTree3 *left;
        KdTree3 *right;
        KdTree3 *parent;
    };

    }
}

#endif
