#ifndef GRAPHCIS_SCENEV1_TREE_H
#define GRAPHCIS_SCENEV1_TREE_H

#include "data_struct/octree.h"
#include "transmat4.h"
#include "scene_managing/scene_v1/scenev1.h"

namespace curiosity {
    namespace graphics {

    class SceneV1Tree : public OcTree {
    public:
        SceneV1Tree(int maxContentSize)
            : OcTree(maxContentSize) {
        }

        void setScene(SceneV1 *scene);
    protected:
        virtual void process(TreeNode *node);
    private:
        SceneV1 *scene;

    };

    }
}

#endif
