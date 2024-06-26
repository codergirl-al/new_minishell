/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:12 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/08 00:24:50 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lib.h"
#include "include/minishell.h"

int	g_sig;

static void	prompt(t_data *data, int status)
{
	while (g_sig >= 256)
	{
		setup_signal_handling();
		if (data->exit_status)
			data->input = readline(RED"➜ "DEFAULT);
		else if (isatty(fileno(stdin)))
			data->input = readline(GREEN"➜ "DEFAULT);
		if (data->input && *data->input)
		{
			status = checker(&data->input);
			add_history(data->input);
			if (!status)
				(void) iter_cmd(data);
			else
				data->exit_status = status;
		}
		else if (!data->input || data->exit || g_sig < 256)
		{
			free(data->input);
			break ;
		}
		free(data->input);
		data->input = NULL;
	}
}

static void	set_data(t_data *data, char **env)
{
	g_sig = 256;
	data->envp = ft_arrdup(env);
	data->exit_status = 0;
	data->exit = false;
	data->input = NULL;
}

static void	unset_data(t_data *data)
{
	ft_arrfree(data->envp);
}

int	main(int argc, char **argv, char **env)
{
	int		status;
	t_data	data;

	(void)argv;
	status = 0;
	set_data(&data, env);
	if (argc != 1)
		printf("All arguments will be ignored\n");
	prompt(&data, status);
	unset_data(&data);
	return (data.exit_status);
}
