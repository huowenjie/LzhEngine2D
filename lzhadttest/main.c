#include <stdio.h>
#include <lzh_link.h>

LINK_DECLARE(STR, str, char *)

int comp(const void *str1, const void *str2);
void visit(const STR_LINK_NODE *node, void *args);

char *genstr(const char *str);
void show_link(STR_LINK *link);

int main(int argc, char *argv[])
{
    STR_LINK *link = str_link_create(comp);
    char *str = NULL;

    str_link_push(link, genstr("ac"));
    str_link_push(link, genstr("bb"));
    str_link_push(link, genstr("adfds"));
    str_link_push(link, genstr("1"));
    str_link_push(link, genstr("张三"));

    show_link(link);

    str_link_insert(link, 0, genstr("李四"));
    str_link_insert(link, 6, genstr("王五"));

    show_link(link);

    str_link_remove(link, 1, &str);
    printf("delete %s\n", str);
    LZH_FREE(str);

    str_link_remove(link, 5, &str);
    printf("delete %s\n", str);
    LZH_FREE(str);

    show_link(link);

    str_link_pop(link, &str);
    printf("pop %s\n", str);
    LZH_FREE(str);

    show_link(link);

    str = "张三";
    if (str_link_exist(link, str)) {
        printf("%s exist\n", str);
    } else {
        printf("%s not exist\n", str);
    }

    str = "李四";
    if (str_link_exist(link, str)) {
        printf("%s exist\n", str);
    } else {
        printf("%s not exist\n", str);
    }

    str_link_remove_value(link, str);
    show_link(link);

    str_link_destroy(link);
    return 0;
}

LINK_IMPLEMENT(STR, str, char *)

int comp(const void *str1, const void *str2)
{
    const char **s1 = (const char **)str1;
    const char **s2 = (const char **)str2;
    return strcmp(*s1, *s2);
}

void visit(const STR_LINK_NODE *node, void *args)
{
    if (node->value) {
        LZH_FREE(node->value);
    }
}

char *genstr(const char *str)
{
    size_t size = strlen(str) + 1;
    char *ret = LZH_MALLOC(size);
    strcpy(ret, str);
    return ret;
}

void show_link(STR_LINK *link)
{
    int i = 0;
    for (; i < str_link_count(link); i++) {
        const char *p = NULL;
        int index = 0;

        str_link_value(link, i, (char **)&p);
        index = str_link_index(link, p);
        printf("%d -- val: %s, index = %d\n", i, p, index);
    }

    printf("-------------------------------------------\n");
}