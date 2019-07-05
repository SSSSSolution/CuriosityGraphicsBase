#ifndef GRAPHCIS_SCENEV1_TREE_H
#define GRAPHCIS_SCENEV1_TREE_H

#include "data_struct/octree.h"

namespace curiosity {
    namespace graphics {

    class SceneV1Tree : public OcTree {
    protected:
        virtual void process(TreeNode *node);
    };

    }
}

#endif
