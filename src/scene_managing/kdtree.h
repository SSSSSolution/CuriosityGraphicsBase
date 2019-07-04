#ifndef GRAPHICS_KDTREE_H
#define GRAPHICS_KDTREE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct KdTree KdTree;
typedef struct KdRes KdRes;
typedef struct KdNode KdNode;
typedef struct KdHyperRect KdHyperRect;

struct KdTree {
    int dim;
    KdNode *root;
    KdHyperRect *rect;
    void (*destr)(void*);
};

struct KdNode {
    float *pos;
    int dir;
    void *data;

    KdNode *right, *left;
};

typedef struct KdResNode KdResNode;

struct KdResNode {
    KdNode *item;
    float dist_sq;
    KdResNode *next;
};


struct KdHyperRect {
    int dim;
    float *min, *max;
};



struct KdRes {
    struct KdTree *tree;
    KdResNode *rlist, *riter;
    int size;
};

KdTree *kd_create(int k);
void kd_free(KdTree *tree);

void kd_clear(KdTree *tree);

int kd_insert(KdTree *tree, float *pos, void *data);

// 找距离在范围内的点
KdRes *kd_nearest_range(KdTree *tree, float *pos, float range);

#ifdef __cplusplus
}
#endif

#endif
