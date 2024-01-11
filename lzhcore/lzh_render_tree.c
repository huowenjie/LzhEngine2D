#include "lzh_render_tree.h"

/*===========================================================================*/

static int interger_comp(const void *a, const void *b)
{
    int i1 = *((int *)a);
    int i2 = *((int *)b);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

static void rt_visit_free(const RT_RB_NODE *node, void *args)
{
    if (node) {
        SRT_RB_TREE *sub_tree = node->value;
        srt_rb_destroy(sub_tree, NULL, NULL);
    }
}

/*===========================================================================*/

RT_RB_TREE *create_render_tree()
{
    RT_RB_TREE *tree = rt_rb_create(interger_comp);
    return tree;
}

void destroy_render_tree(RT_RB_TREE *tree)
{
    rt_rb_destroy(tree, rt_visit_free, NULL);
}

void render_tree_push(
    RT_RB_TREE *render_tree, int layer, int order, LZH_OBJECT *object)
{
    SRT_RB_TREE *sub_tree = NULL;

    if (!render_tree) {
        return;
    }

    if (rt_rb_find(render_tree, layer, &sub_tree) != 0) {
        sub_tree = srt_rb_create(interger_comp);
        if (!sub_tree) {
            return;
        }
        rt_rb_insert(render_tree, layer, sub_tree);
    }

    if (object) {
        srt_rb_insert(sub_tree, order, object);
    }
}

/*===========================================================================*/

struct rt_cache {
    int layer;
    void (*visit)(int, int, LZH_OBJECT *object, void *);
    void *args;
};

static void srt_visit(const SRT_RB_NODE *node, void *args)
{
    if (node && args) {
        struct rt_cache *cache = (struct rt_cache *)args;

        if (cache->visit) {
            cache->visit(cache->layer, node->key, node->value, cache->args);
        }
    }
}

static void rt_visit(const RT_RB_NODE *node, void *args)
{
    if (node && args) {
        struct rt_cache *cache = (struct rt_cache *)args;
        SRT_RB_TREE *sub_tree = node->value;

        cache->layer = node->key;
        srt_rb_iterate(sub_tree, srt_visit, (void *)cache);
    }
}

void render_tree_iterate(
    RT_RB_TREE *render_tree,
    void (*visit)(int, int, LZH_OBJECT *, void *),
    void *args
)
{
    struct rt_cache cache;

    if (!render_tree) {
        return;
    }

    cache.visit = visit;
    cache.args = args;
    rt_rb_iterate(render_tree, rt_visit, (void *)&cache);
}

/*===========================================================================*/

RBTREE_IMPLEMENT(SRT, srt, int, LZH_OBJECT *)
RBTREE_IMPLEMENT(RT, rt, int, SRT_RB_TREE *)

/*===========================================================================*/
