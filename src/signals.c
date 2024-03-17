/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:14:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/17 13:20:26 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_sig;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGTERM)
		g_sig = SIGTERM;
}

void	s_child_case(int sig)
{
	if (sig == SIGINT)
		printf("^C\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	s_heredoc_case(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(sig);
	}
}

void	handle_signals_extended(void (*func)(int))
{
	signal(SIGINT, func);
	signal(SIGTERM, func);
	signal(SIGQUIT, func);
}

void	setup_signal_handling(void)
{
	struct termios	t_settings;

	tcgetattr(1, &t_settings);
	t_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &t_settings);
	handle_signals_extended(handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
