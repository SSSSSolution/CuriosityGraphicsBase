#include "scenev1organizer.h"

namespace curiosity {
    namespace graphics {

    SceneV1Organizer::SceneV1Organizer() {
        ocTree = new SceneV1Tree(1);
        float r[6] = { -1000.0f, 1000.0f, -1000.0f, 1000.0f, -1000.0f, 1000.0f};
        ocTree->build(r);
    }

    void SceneV1Organizer::addObject(WorldBaseObject *obj) {
        OcTree::NodeContent *content = new OcTree::NodeContent();
        content->data = obj;
        content->x = obj->getPosition().x_;
        content->y = obj->getPosition().y_;
        content->z = obj->getPosition().z_;
        ocTree->insert(content);
    }

    void SceneV1Organizer::removeObject(WorldBaseObject *obj) {
        // todo...
    }

    void SceneV1Organizer::exec() {
        ocTree->traversal();
    }

    void SceneV1Organizer::setScene(SceneV1 *scene) {
        ocTree->setScene(scene);
    }

    }
}
