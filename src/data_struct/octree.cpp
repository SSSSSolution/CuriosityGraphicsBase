#include "data_struct/octree.h"
#include <iostream>
#include <assert.h>

using namespace std;

namespace curiosity {
    namespace graphics {

    OcTree::OcTree(int maxContenSize)
        : root(nullptr), maxContentSize(maxContenSize) {
    }

    OcTree::~OcTree() {

    }

    void OcTree::build(float *r) {
        if (root)
            clearTree();
        root = new TreeNode(r);
    }

    void OcTree::build(float *r, vector<NodeContent *> &contents) {
        if (root)
            clearTree();
        root = new TreeNode(r);

        for (auto content : contents)
            insert(root, content);
    }

    void OcTree::clearTree() {

    }

    void OcTree::insert(NodeContent *content) {
        insert(root, content);
    }

    // 插入新的节点
    void OcTree::insert(TreeNode *root, NodeContent *content) {
        assert(root);
        assert(content);

        int quad = root->whichQuadrant(content);
        if (root->dir[quad]) {
            insert(root->dir[quad], content);
            return;
        }
        // 插入位置为空，则开始处理
        if (root->isLeaf) { // 如果是叶子结点, 将内容加到该结点内容链表上
            root->addContentList(content);
            if (root->contentSize > maxContentSize) // 如果链表大小大于最大内容数，则切分这个结点
                root->split();
        } else { // 不是叶子结点，就在子节点上新建结点并加入内容
            float r[6];
            root->quadrantRange(quad, r);
            root->dir[quad] = new TreeNode(r);
            root->dir[quad]->addContentList(content);
        }
    }

    void OcTree::traversal() {
        traversal(root);
    }

    void OcTree::traversal(TreeNode *root) {
        if (!root)
            return;
        process(root);
        for (int i = 0; i <8; ++i) {
            traversal(root->dir[i]);
        }
    }


    OcTree::TreeNode::TreeNode(float *r) {
        for (int i = 0; i < 8; i++)
            dir[i] = nullptr;
        content = nullptr;
        contentSize = 0;
        isLeaf = true;
        memcpy(range, r, sizeof(float) * 6);
    }


    OcTree::TreeNode::~TreeNode() {
        clearContent();
        for (int i = 0; i < 8; i++) {
            if (dir[i])
                delete dir[i];
        }
    }

    void OcTree::TreeNode::clearContent() {
        NodeContent *p = content;
        while (p) {
            NodeContent *tmp = p->next;
            delete p;
            p = tmp;
        }
    }

    int OcTree::TreeNode::whichQuadrant(NodeContent *content) {
        assert(content);
        float ox = (range[0]+range[1])/2.0f;
        float oy = (range[2]+range[3])/2.0f;
        float oz = (range[4]+range[5])/2.0f;
        if (content->x - ox  >= 0) { // 点在x轴正半边
            if (content->y - oy >= 0) { // 点在y轴正半边
                if (content->z - oz >= 0) { // 点在z轴正半边
                    return 0;
                } else {
                    return 4;
                }
            } else {
                if (content->z - oz >= 0) {
                    return 3;
                } else {
                    return 7;
                }
            }
        } else {
            if (content->y - oy >= 0) {
                if (content->z - oz >= 0) {
                    return 1;
                } else {
                    return 5;
                }
            } else {
                if (content->z - oz >= 0) {
                    return 2;
                } else {
                    return 6;
                }
            }
        }
    }

    void OcTree::TreeNode::quadrantRange(int dir, float *out) {
        float ox = (range[0]+range[1])/2.0f;
        float oy = (range[2]+range[3])/2.0f;
        float oz = (range[4]+range[5])/2.0f;

        switch (dir) {
        case 0:
            out[0] = ox;        out[2] = oy;        out[4] = oz;
            out[1] = range[1];  out[3] = range[3];  out[5] = range[5];
            return;
        case 1:
            out[0] = range[0];  out[2] = oy;        out[4] = oz;
            out[1] = ox;        out[3] = range[3];  out[5] = range[5];
            return;
        case 2:
            out[0] = range[0]; out[2] = range[2];   out[4] = oz;
            out[1] = ox;       out[3] = oy;         out[5] = range[5];
            return;
        case 3:
            out[0] = ox;        out[2] = range[2];  out[4] = oz;
            out[1] = range[1];  out[3] = oy;        out[5] = range[5];
            return;
        case 4:
            out[0] = ox;        out[2] = oy;        out[4] = range[4];
            out[1] = range[1];  out[3] = range[3];  out[5] = oz;
            return;
        case 5:
            out[0] = range[0];  out[2] = oy;        out[4] = range[4];
            out[1] = ox;        out[3] = range[3];  out[5] = oz;
            return;
        case 6:
            out[0] = range[0]; out[2] = range[2];   out[4] = range[4];
            out[1] = ox;       out[3] = oy;         out[5] = oz;
            return;
        case 7:
            out[0] = ox;        out[2] = range[2];  out[4] = range[4];
            out[1] = range[1];  out[3] = oy;        out[5] = oz;
            return;
        }
    }

    void OcTree::TreeNode::addContentList(NodeContent *c) {
        assert(c != nullptr);
        c->next = content;
        content = c;
        contentSize++;
    }

    void OcTree::TreeNode::split() {
        NodeContent *pContent = content;
        float r[6];

        while(pContent != nullptr) {
            // 计算出这个内容应该分配到哪一象限
            int quad = whichQuadrant(pContent);
            // 该象限子树不存在，则创建
            if (!dir[quad]) {
                quadrantRange(quad, r);
                dir[quad] = new TreeNode(r);
            }
            //将内容加入该子树内容链表, 加入后的内容个数有可能会大于最大数，这是被允许的
            NodeContent *tmp = pContent->next;
            dir[quad]->addContentList(pContent);
            pContent = tmp;
        }
        content = nullptr;
        contentSize = 0;
        isLeaf = false;
    }

    }
}

































