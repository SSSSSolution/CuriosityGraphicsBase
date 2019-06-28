#ifndef GRAPHICS_CUBE_H
#define GRAPHICS_CUBE_H

#include "worldbaseobject.h"
#include "texture2d.h"

namespace curiosity {
    namespace graphics {

    class CubeObject : public WorldBaseObject {
    public:
        CubeObject(const Vec3 &position = Vec3(0.0f, 0.0f, 0.0f),
                   const Vec3 &scaleFactor = Vec3(1.0f, 1.0f, 1.0f),
                   program = NULL);
        virtual ~CubeObject();

        virtual void draw();
        void setTexture(std::string name);

    private:
        Texture2D texture;
    };

    }
}

#endif
