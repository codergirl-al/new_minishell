/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:14:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/16 23:13:13 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_sig;

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
		g_sig = 0;
}

void setup_signal_handling(void) {
    struct sigaction sa;

    sa.sa_handler = &handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

void s_child_case(int sig) {
  if (sig == SIGINT)
    printf("^C\n");
  else if (sig == SIGQUIT)
    printf("Quit: 3\n");
}

void s_heredoc_case(int sig) {
  if (sig == SIGINT) {
    printf("\n");
    exit(sig);
  }
}

void child_signals(void) {
  signal(SIGINT, s_child_case);
  signal(SIGTERM, s_child_case);
  signal(SIGQUIT, s_child_case);
}

void s_heredoc_handler(void) {
  signal(SIGINT, s_heredoc_case);
  signal(SIGTERM, s_heredoc_case);
  signal(SIGQUIT, s_heredoc_case);
}
