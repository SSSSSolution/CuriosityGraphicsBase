#include "scene_managing/scene_v1/scenev1Tree.h"
#include "worldbaseobject.h"
#include "program.h"
#include <assert.h>

namespace curiosity {
    namespace graphics {

    void SceneV1Tree::process(TreeNode *node) {
        if (!node->content)
            return;
        if (!node->content->data)
            return;
        WorldBaseObject *obj = static_cast<WorldBaseObject *>(node->content->data);
        scene->concreatProcess(obj);
    }

    void SceneV1Tree::setScene(SceneV1 *scene) {
        this->scene = scene;
    }

    }
}

