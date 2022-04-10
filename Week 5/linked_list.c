#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    // List of size
    node *list = NULL;

    // Add 1st number to the list
    node *n =  malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    // Go there first and then set value of that node number to 1
    n->number = 1;
    n->next = NULL;

    list = n;

    // Add 2nd number to the list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;

     // Add 3rd number to the list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    // Free memory allocated
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    return 0;
}