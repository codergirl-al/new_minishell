/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:55:12 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/16 23:04:06 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	prompt(t_data *data)
{
	t_list	shell_commands;

	while (g_sig >= 256)
	{
		setup_signal_handling();
		printf(GREEN);
		if (data->exit_status)
			printf(RED);
		if (isatty(fileno(stdin)))
			data->input = readline("➜ "DEFAULT);
		if (data->input && *data->input)
		{
			data->exit_status = checker(&data->input);
			add_history(data->input);
			ft_parse_input(data->input, &shell_commands);
			// executer
		}
		else if (!data->input || data->exit || g_sig < 256)
			break ;
		if (data->prev_input)
			free(data->prev_input);
		data->prev_input = data->input;
		data->input = NULL;
	}
}

void	set_data(t_data *data, char **env)
{
	g_sig = 256;
	data->envp = ft_arrdup(env);
	data->exit_status = 0;
	data->exit = false;
	data->input = NULL;
	data->prev_input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	setup_signal_handling();
	set_data(&data, env);
	if (argc != 1)
		printf("All arguments will be ignored\n");
	prompt(&data);
	exit(data.exit_status);
}
