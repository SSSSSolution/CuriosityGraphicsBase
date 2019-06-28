#include "cubeobject.h"
#include "resourcemanager.h"

namespace curiosity {
    namespace graphics {

    CubeObject::CubeObject(const Vec3 &position, const Vec3 &scaleFactor, program)
        : WorldBaseObject(position, scaleFactor, program) {
    }

    virtual ~CubeObject() {

    }

    CubeObject::draw() {
        program->use();
        texture.bind();

    }

    void CubeObject::setTexture(std::string name) {
        texture = ResourceManager::getTexture2D(name);
    }

    }
}
