/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:32:23 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/02 17:53:17 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_heredoc(const char *delimiter)
{
	char	*read;
	int		found;
	char	*tmp_filename;
	int		fd;

	tmp_filename = "heredoc.tmp";
	fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open error");
		exit(EXIT_FAILURE);
	}
	found = 0;
 	while (!found)
	{
		read = readline("heredoc> ");
		if (read == NULL)
			break ;
		if (ft_strncmp(read, delimiter, ft_strlen(delimiter)) == 0 && ft_strlen(read) == ft_strlen(delimiter))
		{
			found = 1;
			free (read);
			break ;
		}
		write(fd, read, strlen(read));
		write(fd, "\n", 1);
		free (read); 
	}
	// close(fd);
	// unlink(tmp_filename);
	return (fd);
}
