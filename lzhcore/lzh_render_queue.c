#include <string.h>

#include "lzh_render_queue.h"
#include "lzh_mem.h"
#include "lzh_link.h"

/*===========================================================================*/

struct RENDER_LAYER_QUEUE *create_render_layer_queue()
{
    struct RENDER_LAYER_QUEUE *queue = LZH_MALLOC(sizeof(struct RENDER_LAYER_QUEUE));
    memset(queue, 0, sizeof(struct RENDER_LAYER_QUEUE));
    return queue;
}

void destroy_render_layer_queue(struct RENDER_LAYER_QUEUE *queue)
{
    if (!queue) {
        return;
    }

    while (queue->count > 0) {
        struct RENDER_LAYER_QUEUE_NODE *rlq_elem = 
            (struct RENDER_LAYER_QUEUE_NODE *)link_pop((LINK *)queue);
        if (rlq_elem) {
            struct RENDER_QUEUE *rq_link = rlq_elem->render_queue;

            while (rq_link && rq_link->count > 0) {
                struct RENDER_QUEUE_NODE *rq_elem = 
                    (struct RENDER_QUEUE_NODE *)link_pop((LINK *)rq_link);
                if (rq_elem) {
                    LZH_FREE(rq_elem);
                }
            }
            LZH_FREE(rq_link);
            LZH_FREE(rlq_elem);
        }
    }
    LZH_FREE(queue);
}

static void render_queue_push_object(
    struct RENDER_QUEUE *queue, LZH_OBJECT *object)
{
    struct RENDER_QUEUE_NODE *rq_elem = NULL;
    int count = 0;

    if (!queue || !object) {
        return;
    }
    
    rq_elem = queue->head;
    while (count++ < queue->count) {
        if (rq_elem->object == object) {
            return;
        }

        rq_elem = rq_elem->next;
    }

    rq_elem = LZH_MALLOC(sizeof(struct RENDER_QUEUE_NODE));
    if (!rq_elem) {
        return;
    }
    memset(rq_elem, 0, sizeof(struct RENDER_QUEUE_NODE));

    rq_elem->object = object;
    link_push((LINK *)queue, (LINK_NODE *)rq_elem);
}

void render_queue_push(
    struct RENDER_LAYER_QUEUE *queue, int layer, LZH_OBJECT *object)
{
    struct RENDER_LAYER_QUEUE_NODE *rlq_elem = NULL;
    struct RENDER_QUEUE *rq_link = NULL;
    int count = 0;

    if (!queue) {
        return;
    }

    rlq_elem = queue->head;
    while (count++ < queue->count) {
        if (rlq_elem->layer == layer) {
            break;
        }

        rlq_elem = rlq_elem->next;
    }

    if (!rlq_elem) {
        rlq_elem = LZH_MALLOC(sizeof(struct RENDER_LAYER_QUEUE_NODE));
        if (!rlq_elem) {
            return;
        }
        memset(rlq_elem, 0, sizeof(struct RENDER_LAYER_QUEUE_NODE));
        
        rq_link = LZH_MALLOC(sizeof(struct RENDER_QUEUE));
        if (!rq_link) {
            LZH_FREE(rlq_elem);
            return;
        }
        memset(rq_link, 0, sizeof(struct RENDER_QUEUE));

        rlq_elem->layer = layer;
        rlq_elem->render_queue = rq_link;

        link_push((LINK *)queue, (LINK_NODE *)rlq_elem);
    } else {
        rq_link = rlq_elem->render_queue;
    }

    if (object) {
        render_queue_push_object(rq_link, object);
    }
}

/*===========================================================================*/
