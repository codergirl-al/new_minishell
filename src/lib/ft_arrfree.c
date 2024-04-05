
#include "../../include/lib.h"

void ft_arrfree(char **arr)
{
    int i;
    if (arr == NULL)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
