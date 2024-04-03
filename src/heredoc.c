/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:32:23 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/03 15:09:21 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char *handle_heredoc_expansion(char *line, char **envp)
// {
// 	char	*buffer;
// 	char	*env_var;
// 	size_t	*env_var_index;
// 	size_t	index;
// 	size_t	i;

// 	buffer[0] ='\0';
// 	index = 0;
// 	i = 0;
// 	while (line[i] != '\0' && index < ft_strlen(buffer) - 1)
// 	{
// 		if (line[i] == '$')
// 		{
// 			env_var_index = 0;
// 			i++;
// 			while (ft_isalnum(line[i]) || line[i] == '_')
// 			{
// 				if (env_var_index < 
// 			}
			
// 		}
// 		i++;
// 	}
// }

int	handle_heredoc(const char *delimiter)
{
	char	*read;
	int		found;
	char	*tmp_filename;
	int		fd;

	tmp_filename = "heredoc";
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
