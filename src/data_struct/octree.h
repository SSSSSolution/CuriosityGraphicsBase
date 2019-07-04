#ifndef GRAPHICS_OCTREE_H
#define GRAPHICS_OCTREE_H
#include <vector>
/*
 * 先实现空间点的搜索树
 * 有体积的先不实现
 */

namespace curiosity {
    namespace graphics {

    class OcTree {
    public:
        typedef struct TreeNode TreeNode;
        typedef struct NodeContent NodeContent;

        struct NodeContent {
            void *data;
            float x, y, z;
            NodeContent *next;
        };
        struct TreeNode {
            TreeNode() {
                a = b = c = d = e = f = g = h = NULL;
                nodeContent = NULL;
            }
            TreeNode *a, *b, *c, *d,
                     *e, *f, *g, *h;
            NodeContent *nodeContent;
            float xMin, xMax, yMin, yMax, zMin, zMax;
        };

        OcTree();
        ~OcTree();

        void build(float xMin, float xMax,
                   float yMin, float yMax,
                   float zMin, float zMax,
                   const std::vector<NodeContent> &nodeContents);
        void insert(TreeNode *root, NodeContent *content);

    private:
        TreeNode *root;
    };


    }
}

#endif
