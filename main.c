/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:12 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/04 13:54:30 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lib.h"
#include "include/minishell.h"

int	g_sig;

static void	prompt(t_data *data)
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
			data->exit_status = checker(&data->input);
			add_history(data->input);
			if (!data->exit_status)
				(void) iter_cmd(data);
		}
		else if (!data->input || data->exit || g_sig < 256)
			break ;
		if (data->prev_input)
			free(data->prev_input);
		data->prev_input = data->input;
		data->input = NULL;
	}
}

static void set_data(t_data *data, char **env)
{
	g_sig = 256;
	data->envp = ft_arrdup(env);
	data->exit_status = 0;
	data->exit = false;
	data->input = NULL;
	data->prev_input = NULL;
}

static void unset_data(t_data *data)
{
	ft_arrfree(data->envp);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	set_data(&data, env);
	if (argc != 1)
		printf("All arguments will be ignored\n");
	prompt(&data);
	unset_data(&data);
	return (data.exit_status);
}
