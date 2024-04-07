/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:32:23 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/07 14:58:49 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void setup_heredoc_signals(void) {
    signal(SIGINT, s_heredoc_case); // Use heredoc-specific signal handling
    signal(SIGQUIT, SIG_IGN); // Ignore SIGQUIT in heredoc
}

// This function is called after finishing the heredoc input loop
void restore_signals_after_heredoc(void) {
    setup_signal_handling(); // Restore the original signal handling setup
}

static char	*handle_heredoc_expansion(char *line, t_data *data)
{
	char	*env_var;
	int		ints[2];
	size_t	i;

	env_var = NULL;
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
		{
			ints[0] = i;
			ints[1] = get_env(data->envp, line + i, &env_var, data);
			line = ft_swapstr(line, env_var, ints, STRFREE_ARG | STRFREE_SRC);
			i = ints[0];
		}
	}
	return (line);
}

char	*format_delimiter(const char *delimiter)
{
	char	*formatted;
	size_t	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' || delimiter[0] == '"')
		&& delimiter[len - 1] == delimiter[0])
	{
		formatted = strndup(delimiter + 1, len - 2);
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
	char	*f_delimiter;

	f_delimiter = format_delimiter(delimiter);
	fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (fd == -1)
	{
		perror("open error");
		exit(EXIT_FAILURE);
	}
	setup_heredoc_signals(); // Set heredoc-specific signal handling
	found = 0;
	while (!found)
	{
		read = readline("heredoc> ");
		if (read == NULL)
			break ;
		if (ft_strchr(read, '$') != NULL)
			read = handle_heredoc_expansion(read, data);
		if (ft_strncmp(read, f_delimiter, ft_strlen(f_delimiter)) == 0
			&& ft_strlen(read) == ft_strlen(f_delimiter))
		{
			found = 1;
			free (read);
			break ;
		}
		write(fd, read, strlen(read));
		write(fd, "\n", 1);
		free (read);
	}
	restore_signals_after_heredoc(); // Restore the original signal handling setup
	return (fd);
}
