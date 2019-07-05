#include "scenev1.h"
#include "scenev1organizer.h"

namespace curiosity {
    namespace graphics {

    SceneV1::SceneV1(SceneFactory *factory)
        : Scene(factory) {
        dynamic_cast<SceneV1Organizer *>(sceneOrganizer)->setScene(this);
    }

    SceneV1::~SceneV1() {}


    void SceneV1::setMat(const TransMat4 projectMat, const TransMat4 viewMat) {
        this->projectMat = projectMat;
        this->viewMat = viewMat;
    }

    void SceneV1::concreatProcess(WorldBaseObject *obj) {
        //　画物体
        Program *program = obj->getProgram();
        program->use();
        program->setTransMat4("project", projectMat);
        program->setTransMat4("view", viewMat);
        obj->draw();
    }
    }
}
