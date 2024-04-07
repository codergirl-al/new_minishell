
#include "../include/minishell.h"

void	print_error(int flag)
{
	char	c;

	c = 0;
	printf("minibash: syntax error near unexpected token `");
	if ((flag & FLAG_1) && !(flag & FLAG_2))
		c = '|';
	else if (!(flag & FLAG_1) && (flag & FLAG_2))
		c = '<';
	else if ((flag & FLAG_1) && (flag & FLAG_2))
		c = '>';
	printf("%c", c);
	if (flag & FLAG_3)
		printf("%c", c);
	printf("\'\n");
}