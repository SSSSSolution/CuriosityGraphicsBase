#ifndef GRAPHICS_LIGHTSOURCE_H
#define GRAPHCIS_LIGHTSOURCE_H
#include "graphicsglobal.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class LightSource {
    public:
        virtual void enable(bool) = 0;

    protected:
        Vec3 diffuse_;
        Vec3 ambient_;
        Vec3 specular_;
    };

    class DirLight : public LightSource {
    public:
        DirLight();
        virtual void enable(bool b);

    protected:
        Vec3 direction_;
    };

    }
}

#endif
