#ifndef GRAPHCIS_SCENEV1_TREE_H
#define GRAPHCIS_SCENEV1_TREE_H

#include "data_struct/octree.h"
#include "transmat4.h"
#include "scene_managing/scene_v1/scenev1.h"
#include "drawable_object/cubeline.h"
#include "resourcemanager.h"

namespace curiosity {
    namespace graphics {

    class SceneV1Tree : public OcTree {
    public:
        SceneV1Tree(int maxContentSize)
            : OcTree(maxContentSize) {
            cubeProgram = ResourceManager::loadProgram("/drawobject/cubeobject.vs", "/drawobject/cubeobject.fs", nullptr, "cubeline");
            cube = new CubeLine(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), &cubeProgram);
        }

        void setScene(SceneV1 *scene);
    protected:
        virtual void process(TreeNode *node);
    private:
        SceneV1 *scene;
        CubeLine *cube;
        Program cubeProgram;

    };

    }
}

#endif
