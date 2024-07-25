#ifndef __LZH_STACK_H__
#define __LZH_STACK_H__

#include <stddef.h>

/*===========================================================================*/
/* ջģ�� */
/*===========================================================================*/

/* ����ջ����һ�������������ռ䣬�ڶ�������������ǰ׺��������������Ԫ������ */
#define STACK_DEFINE(ns, nscp, type) \
    typedef struct ns##_stack_st{ \
        type *elems; \
        int size; \
        int num; \
    } nscp##_STACK; \
    \
    extern int ns##_stack_push(nscp##_STACK *stack, type val); \
    extern int ns##_stack_pop(nscp##_STACK *stack, type *ret); \

/* ջʵ�� */
#define STACK_IMPLEMENT(ns, nscp, type) \
    int ns##_stack_push(nscp##_STACK *stack, type val) { \
        type *val_list = NULL; \
        int num = 0; \
        int size = 0; \
        \
        if (!stack) { \
            return -1; \
        } \
        \
        val_list = stack->elems; \
        \
        if (!val_list) { \
            return -1; \
        } \
        \
        num = stack->num; \
        size = stack->size; \
        \
        if (num >= size) { \
            return -1; \
        } \
        \
        val_list[num++] = val; \
        stack->num = num; \
        return 0; \
    } \
    \
    int ns##_stack_pop(nscp##_STACK *stack, type *ret) { \
        type *val_list = NULL; \
        int num = 0; \
        \
        if (!stack) { \
            return -1; \
        } \
        \
        val_list = stack->elems; \
        \
        if (!val_list) { \
            return -1; \
        } \
        \
        num = stack->num; \
        \
        if (num <= 0) { \
            return -1; \
        } \
        \
        num--; \
        if (ret) { \
            *ret = val_list[num]; \
        } \
        stack->num = num; \
        return 0; \
    }

/*===========================================================================*/

#endif /* __LZH_STACK_H__ */
