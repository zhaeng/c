#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} node;

node *insertNode(struct Node *list, int val)
{
    //printf("---%d\r\n", list->value);
    node *tmp = malloc(sizeof(node));
    tmp->value = val;
    tmp->next = list;
    return tmp;
}

node *initNode(int val)
{
    node *tmp;
    tmp = malloc(sizeof(node));
    tmp->value = val;
    tmp->next = NULL;
    return tmp;
}

void printNode(struct Node *list)
{
    for (; list->next != NULL; list = list->next)
    {
        printf("%d\r\n", list->value);
        //free(list);
    }
}

int main(int argc, char const *argv[])
{
    node *node = initNode(10);
    printf("init value %d\r\n", node->value);
    node = insertNode(node, 11);
    node = insertNode(node, 12);
    node = insertNode(node, 13);
    node = insertNode(node, 14);
    printNode(node);
    return 0;
}
