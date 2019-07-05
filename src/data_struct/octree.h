#ifndef GRAPHICS_OCTREE_H
#define GRAPHICS_OCTREE_H
#include <vector>
#include <string.h>
/*
 * 先实现空间点的搜索树
 * 有体积的先不实现
 */

namespace curiosity {
    namespace graphics {

    class OcTree {
    public:
        OcTree(int maxContentSize);
        virtual ~OcTree();

        struct NodeContent {
            NodeContent() {}
            ~NodeContent() {}
            void *data;
            float x, y, z;
            NodeContent *next;
        };

        struct TreeNode {
            TreeNode(float *r);
            ~TreeNode();

            void clearContent();
            // 内容位置在这个结点的哪个象限上
            int whichQuadrant(NodeContent *content);
            // 计算出某个象限的子节点的区域范围
            void quadrantRange(int dir, float *out);
            // 向结点加入内容
            void addContentList(NodeContent *content);
            // 拆分成子空间
            void split();
            // ８个象限的子树
            TreeNode *dir[8];
            //　结点代表的区域范围，xMin, xMax, yMin, yMax, zMin, zMax
            float range[6];
            // 这个结点包含的内容链表
            NodeContent *content;
            int contentSize;
            bool isLeaf;
        };

        void build(float *r, std::vector<NodeContent *> &contents);
        void clearTree();
        void insert(TreeNode *root, NodeContent *content);
        void traversal(TreeNode *root);

    protected:
        virtual void process(TreeNode *node) {}

    public:
        TreeNode *root;
        int maxContentSize;
    };

    }
}

#endif
