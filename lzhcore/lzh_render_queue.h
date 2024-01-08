#ifndef __LZH_RENDER_QUEUE_H__
#define __LZH_RENDER_QUEUE_H__

#include <lzh_type.h>

/*===========================================================================*/
/* ��Ⱦ���� */
/*===========================================================================*/

/* ���нڵ� */
struct RENDER_QUEUE_NODE {
    struct RENDER_QUEUE_NODE *prev;
    struct RENDER_QUEUE_NODE *next;

    /* ��Ⱦ���� */
    LZH_OBJECT *object;
};

/* ��Ⱦ���� */
struct RENDER_QUEUE {
    struct RENDER_QUEUE_NODE *head;
    struct RENDER_QUEUE_NODE *tail;

    int count;
};

/* ��Ⱦ��ڵ� */
struct RENDER_LAYER_QUEUE_NODE {
    struct RENDER_LAYER_QUEUE_NODE *prev;
    struct RENDER_LAYER_QUEUE_NODE *next;

    struct RENDER_QUEUE *render_queue;
    int layer;
};

/* ��Ⱦ����� */
struct RENDER_LAYER_QUEUE {
    struct RENDER_LAYER_QUEUE_NODE *head;
    struct RENDER_LAYER_QUEUE_NODE *tail;

    int count;
};

struct RENDER_LAYER_QUEUE *create_render_layer_queue();
void destroy_render_layer_queue(struct RENDER_LAYER_QUEUE *queue);

void render_queue_push(
    struct RENDER_LAYER_QUEUE *queue, int layer, LZH_OBJECT *object);

/*===========================================================================*/

#endif /* __LZH_RENDER_QUEUE_H__ */
