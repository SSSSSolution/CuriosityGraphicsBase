#include "scene.h"

namespace curiosity {
    namespace graphics {

    Scene::Scene(SceneFactory *factory)
        : factory(factory) {
        sceneOrganizer = factory->createSceneOrganizer();
    }

    void Scene::addObject(WorldBaseObject *obj) {
        sceneOrganizer->addObject(obj);
    }

    void Scene::removeObject(WorldBaseObject *obj) {
        sceneOrganizer->removeObject(obj);
    }

    void Scene::exec() {
        sceneOrganizer->exec();
    }

    }
}
