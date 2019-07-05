#include "scene_managing/scene_v1/scenev1Tree.h"
#include "worldbaseobject.h"
#include "program.h"
#include <assert.h>

namespace curiosity {
    namespace graphics {

    void SceneV1Tree::process(TreeNode *node) {
        cubeProgram.use();
        cube->setPosition(Vec3((node->range[0]+node->range[1])/2.0f,
                        (node->range[2]+node->range[3])/2.0f,
                        (node->range[4]+node->range[5])/2.0f));
        cube->scale(Vec3(node->range[1]-node->range[0],
                         node->range[3]-node->range[2],
                         node->range[5]-node->range[4]));
        scene->concreatProcess(cube);
        if (!node->content)
            return;
        // 画出这个节点的范围立方体
        NodeContent *p = node->content;
        while (p) {
            if (p->data) {
                WorldBaseObject *obj = static_cast<WorldBaseObject *>(p->data);
                scene->concreatProcess(obj);
            }
            p = p->next;
        }
    }

    void SceneV1Tree::setScene(SceneV1 *scene) {
        this->scene = scene;
    }

    }
}

