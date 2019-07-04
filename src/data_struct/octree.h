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
//        typedef struct TreeNode TreeNode;
//        typedef struct NodeContent NodeContent;

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

            enum Region {
                A, B, C, D, E, F, G, H
            };
            Region whichRegion(NodeContent *content) {
                if (xMax - content->x <= content->x - xMin) {
                    if (yMax - content->y <= content->y - yMin) {
                        if (zMax - content->z <= content->z - zMin) {
                            return A;
                        } else {
                            return E;
                        }
                    } else {
                        if (zMax - content->z <= content->z - zMin) {
                            return B;
                        } else {
                            return F;
                        }
                    }
                } else {
                    if (yMax - content->y <= content->y - yMin) {
                        if (zMax - content->z <= content->z - zMin) {
                            return D;
                        } else {
                            return H;
                        }
                    } else {
                        if (zMax - content->z <= content->z - zMin) {
                            return C;
                        } else {
                            return G;
                        }
                    }
                }
            }

            std::vector<float> getNewRegion(Region r) {
                std::vector<float> ret;
                switch (r) {
                case A:
                    ret.push_back(xMax);
                    ret.push_back(yMax);
                    ret.push_back(zMax);
                    ret.push_back((xMax + xMin)/2.0f);
                    ret.push_back((yMax + yMin)/2.0f);
                    ret.push_back((zMax + zMin)/2.0f);
                    break;
                case B:
                    break;
                case C:
                    break;
                case D:
                    break;
                case E:
                    break;
                case F:
                    break;
                case G:
                    break;
                case H:
                    break;
                }
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
                   const std::vector<NodeContent *> &nodeContents);
        void insert(TreeNode *root, NodeContent *content);

    private:
        TreeNode *root;
    };


    }
}

#endif
