
#include "../../include/lib.h"

int	istoken(char c)
{
	return ((c == '|') || (c == '>') || (c == '<'));
}