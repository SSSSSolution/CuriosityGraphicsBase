#include "worldbaseobject.h"
#include "transmat4.h"

namespace curiosity {
    namespace graphics {

    WorldBaseObject::WorldBaseObject(const Vec3 &position, const Vec3 &scaleFactor, Program *program)
        : position(position), scaleFactor(scaleFactor), program(program) {
        setModelMatrix();
    }

    void WorldBaseObject::move(const Vec3 &trans) {
        position += trans;
        setModelMatrix();
    }

    void WorldBaseObject::scale(const Vec3 &scaleFactor) {
        this->scaleFactor = scaleFactor;
        setModelMatrix();
    }

    void WorldBaseObject::setModelMatrix() {
        program->use();
        TransMat4 modelMat = TransMat4::translation(position);
        TransMat4 scaleMat = TransMat4::scale(scaleFactor);
        program->setTransMat4("model", modelMat * scaleMat);
    }

    }
}

