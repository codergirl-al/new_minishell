
#include "../../include/lib.h"

void ft_arrfree(char **arr)
{
	int size;

	size = ft_arrlen(arr);
    if (arr == NULL)
        return;
    int i = 0;
    while (i < size)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
