/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:32:23 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/04 14:29:20 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
 
static char *handle_heredoc_expansion(char *line, t_data *data)
{
	char	*env_var = NULL;
	int ints[2];
	size_t	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
		{
			ints[0] = i;
			ints[1] = get_env(data->envp, line + i, &env_var, data);
			line = ft_swapstr(line, env_var, ints, 0);
			i = ints[0];
		}
	}
	return (line);
}

char	*format_delimiter(const char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' || delimiter[0] == '"') && delimiter[len - 1] == delimiter[0])
	{
		char *formatted = strndup(delimiter + 1, len - 2);
		if (!formatted)
		{
			perror("Failed to allocate memory for formatted delimiter");
			exit(EXIT_FAILURE);
		}
		return (formatted);
	}
	else
		return (strdup(delimiter));
}

int	handle_heredoc(const char *delimiter, t_data *data)
{
	int		fd;
	int		found;
	char	*read;
	char	*tmp_filename;
	char	*delimiter_formatted;

	delimiter_formatted = format_delimiter(delimiter);
	tmp_filename = "heredoc";
	fd = open(tmp_filename, O_CREAT | O_RDWR | O_TRUNC, 0000644);
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
		if (ft_strchr(read, '$') != NULL)
			read = handle_heredoc_expansion(read, data);
		if (ft_strncmp(read, delimiter_formatted, ft_strlen(delimiter_formatted)) == 0 && ft_strlen(read) == ft_strlen(delimiter_formatted))
		{
			found = 1;
			free (read);
			break ;
		}
		write(fd, read, strlen(read));
		write(fd, "\n", 1);
		free (read); 
	}
	return (fd);
}
