
#include "include/minibash.h"

static void	prompt(t_data *data)
{
	while (1)
	{
		printf(GREEN);
		if (data->exit_status)
			printf(RED);
		if (isatty(fileno(stdin)))
			data->input = readline("➜ "DEFAULT);
		if (data->input && *data->input)
		{
			data->exit_status = checker(&data->input);
			add_history(data->input);
			ft_parse_input(data->input);
			// executer
		}
		else if (!data->input || data->exit)
			break ;
		if (data->prev_input)
			free(data->prev_input);
		data->prev_input = data->input;
		data->input = NULL;
	}
}

void	set_data(t_data *data, char** env)
{
	data->envp = arrdup(env);
	data->exit_status = 0;
	data->exit = false;
	data->input = NULL;
	data->prev_input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_data data;
	set_data(&data, env);
	if (argc != 1)
		printf("All arguments will be ignored\n");
	prompt(&data);
	exit(data.exit_status);
}