#include "octree.h"
#include <iostream>

namespace curiosity {
    namespace graphics {

    OcTree::OcTree() {
        root = NULL;
    }
    OcTree::~OcTree() {}

    void OcTree::build(float xMin, float xMax, float yMin,
                       float yMax, float zMin, float zMax,
                       const std::vector<NodeContent *> &nodeContents) {
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


    // 插入新的节点
    void OcTree::insert(TreeNode *node, NodeContent *content) {
        TreeNode::Region region = node->whichRegion(content);
        TreeNode **insertPos;
        switch(region) {
        case TreeNode::A:
            insertPos = &(node->a);
            break;
        case TreeNode::B:
            insertPos = &(node->b);
            break;
        case TreeNode::C:
            insertPos = &(node->c);
            break;
        case TreeNode::D:
            insertPos = &(node->d);
            break;
        case TreeNode::E:
            insertPos = &(node->e);
            break;
        case TreeNode::F:
            insertPos = &(node->f);
            break;
        case TreeNode::G:
            insertPos = &(node->g);
            break;
        case TreeNode::H:
            insertPos = &(node->h);
            break;
        default:
            std::cout << __func__ << "Should't run to here" << std::endl;
        }
        if (*insertPos) {
            insert(*insertPos, content);
        } else {
            TreeNode *newNode = new TreeNode();
            newNode->nodeContent = content;
            *insertPos = newNode;
        }
    }

    }
}
