
#include "../../include/lib.h"

int ft_setflag(int flag, ...)
{
    va_list args;
    int arg;

    va_start(args, flag);
    while ((arg = va_arg(args, int)) != 0)
        if (!(flag & arg))
            flag |= arg;
    va_end(args);
    return (flag);
}