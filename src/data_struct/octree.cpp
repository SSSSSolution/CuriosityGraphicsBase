#include "octree.h"

namespace curiosity {
    namespace graphics {

    OcTree::OcTree() {
        root = NULL;
    }
    OcTree::~OcTree() {}

    void OcTree::build(float xMin, float xMax, float yMin,
                       float yMax, float zMin, float zMax,
                       const std::vector<NodeContent> &nodeContents) {
        // 创建根结点
        root = new TreeNode;
        root->xMin = xMin;
        root->xMax = xMax;
        root->yMin = yMin;
        root->yMax = yMax;
        root->zMin = zMin;
        root->zMax = zMax;
        // 将剩下来的结点插入
        for (auto content : nodeContents)
            insert(root, content);
    }

    }
}
