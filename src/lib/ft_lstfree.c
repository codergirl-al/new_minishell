
#include "../../include/lib.h"

void ft_lstfree(t_list *lst)
{
    t_list *current = lst;
    t_list *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
}
