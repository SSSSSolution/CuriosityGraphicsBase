#include "kdtree.h"
#include <stdlib.h>
#include <string.h>
#include "math.h"

#define SQ(x)   ((x) * (x))

static int insert_rec(KdNode **nptr, float *pos, void *data, int dir, int dim);
static KdHyperRect* hyperrect_create(int dim, float *min, float *max);
static void hyperrect_free(KdHyperRect *rect);
static float hyperrect_dist_sq(KdHyperRect *rect, float *pos);
static KdResNode *alloc_resnode(void);

static int rlist_insert(KdResNode *list, KdNode *iter, float dist_sq);

static int find_nearest(KdNode *node, float *pos, float range,
                        KdResNode *list, int ordered, int dim);

static void clear_rec(struct KdNode *node, void(*destr)(void*));
static void hyperrect_extend(KdHyperRect *rect, float *pos);

KdTree *kd_create(int k) {
    KdTree *tree;

    if (!(tree = (KdTree *)malloc(sizeof(KdTree))))
        return NULL;

    tree->dim = k;
    tree->root = NULL;
    tree->destr = NULL;
    tree->rect = NULL;
}

void kd_free(KdTree *tree) {
    if (tree) {
        kd_clear(tree);
        free(tree);
    }
}

// 向结点插入超矩形的一个切面(矩形)
// 一个点加一个维度形成一个矩形切面
int insert_rec(KdNode **nptr, float *pos, void *data, int dir, int dim) {
    int new_dir;
    KdNode *node;

    if (!*nptr) {
        if (!(node = (KdNode *)malloc(sizeof(KdNode)))) {
            return -1;
        }
        if (!(node->pos = (float *)malloc(dim * sizeof(float)))) {
            free(node);
            return -1;
        }
        memcpy(node->pos, pos, dim * sizeof(float));
        node->data = data;
        node->dir = dir;
        node->left = node->right = NULL;
        *nptr = node;
        return 0;
    }
    node = *nptr;
    // ***新的超平面的划分策略：仅仅是顺序轮换,是父结点的维度后面的一个维度
    new_dir = (node->dir + 1) % dim;
    if (pos[node->dir] < node->pos[node->dir]) {
        return insert_rec(&((*nptr)->left), pos, data, new_dir, dim);
    }
    return insert_rec(&((*nptr)->right), pos, data, new_dir, dim);
}

// 向树中插入节点
int kd_insert(KdTree *tree, float *pos, void *data) {
    // 1.先插入结点，就是插入矩形切面
    if (insert_rec(&tree->root, pos, data, 0, tree->dim)) {
        return -1;
    }
    // 2.再更新树结点上的超平面信息
    if (tree->rect == NULL) {
        tree->rect = hyperrect_create(tree->dim, pos, pos);
    } else {
        hyperrect_extend(tree->rect, pos);
    }

    return 0;
}

KdHyperRect *hyperrect_create(int dim, float *min, float *max) {
    size_t size = dim * sizeof(float);
    KdHyperRect *rect = NULL;

    if (!(rect = (KdHyperRect *)malloc(sizeof(KdHyperRect))))
        return NULL;

    rect->dim = dim;
    if (!(rect->min = (float *)malloc(size))) {
        free(rect);
        return NULL;
    }
    if (!(rect->max = (float *)malloc(size))) {
        free(rect->min);
        free(rect);
        return NULL;
    }
    memcpy(rect->min, min, size);
    memcpy(rect->max, max, size);

    return rect;
}

void hyperrect_free(KdHyperRect *rect) {
    free(rect->min);
    free(rect->max);
    free(rect);
}

// 扩展超矩形(扩展各个维度取值范围)
void hyperrect_extend(KdHyperRect *rect, float *pos) {
    int i;
    for (i = 0; i < rect->dim; i++) {
        if (pos[i] < rect->min[i]) {
            rect->min[i] = pos[i];
        }
        if (pos[i] > rect->max[i]) {
            rect->max[i] = pos[i];
        }
    }
}

// 计算固定坐标点与超矩形之间的距离
// 例如 把立方体看作一个超矩形，立方体外的点和这个立方体就有距离，
//      距离的度量为:各个坐标到立方体表面距离的平方和
float hyperrect_dist_sq(KdHyperRect *rect, float *pos) {
    int i;
    float result = 0;

    for (i = 0; i < rect->dim; i++) {
        if (pos[i] < rect->min[i]  - pos[i]) {
            result += SQ(rect->min[i] - pos[i]);
        } else if (pos[i] > rect->max[i]) {
            result += SQ(rect->max[i] - pos[i]);
        }
    }

    return result;
}


void kd_clear(KdTree *tree) {
    if (!tree)
        return;

    clear_rec(tree->root, tree->destr);
    tree->root = NULL;

    if (tree->rect) {
        hyperrect_free(tree->rect);
        tree->rect = NULL;
    }
}

void clear_rec(KdNode *node, void (*destr)(void *)) {
    if (!node)
        return;

    clear_rec(node->left, destr);
    clear_rec(node->right, destr);

    if (destr) {
        destr(node->data);
    }

    free(node->pos);
    free(node);
}

KdRes *kd_nearest_range(KdTree *tree, float *pos, float range) {
    int ret;
    KdRes *rset;

    if (!(rset = (KdRes *)malloc(sizeof(KdRes))))
        return NULL;

    if (!(rset->rlist = (KdResNode*)malloc(sizeof(KdResNode)))) {
        free(rset);
        return NULL;
    }
    rset->rlist->next = NULL;
    rset->tree = tree;

//    if ((ret = find_nearest()))
}

// 找到最邻近的点
// 参数: 树节点，位置，范围, 返回结果，bool型排序, 维度
int find_nearest(KdNode *node, float *pos, float range,
                 KdResNode *list, int ordered, int dim) {
    float dist_sq, dx;
    int i, ret, added_res = 0;

    if (!node)
        return 0;

    dist_sq = 0;
    for (i = 0; i < dim; i++) {
        dist_sq += SQ(node->pos[i] - pos[i]);
    }

    if (dist_sq <= SQ(range)) {
        if (rlist_insert(list, node, ordered ? dist_sq : -1.0) == -1) {
            return -1;
        }
        added_res = 1;
    }

    dx = pos[node->dir] - node->pos[node->dir];

    ret = find_nearest(dx <= 0.0f ? node->left : node->right, pos,
                       range, list, ordered, dim);

    if (ret >= 0 && fabsf(dx) < range) {
        added_res += ret;
        ret = find_nearest(dx < 0.0f ? node->right : node->left, pos,
                           range, list, ordered, dim);
    }
    if (ret == -1) {
        return -1;
    }
    added_res += ret;

    return added_res;
}

static int rlist_insert(KdResNode *list, KdNode *item, float dist_sq) {
    KdResNode *rnode;

    if (!(rnode = (KdResNode *)malloc(sizeof(KdResNode))))
        return -1;
    rnode->item = item;
    rnode->dist_sq = dist_sq;

    if (dist_sq >= 0.0f) {
        while(list->next && list->next->dist_sq < dist_sq) {
            list = list->next;
        }
    }
    rnode ->next = list->next;
    list->next = rnode;
    return 0;
}




































