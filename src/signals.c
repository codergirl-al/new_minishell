/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:14:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/16 18:17:57 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_sig;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
        // For Ctrl-C, display a new prompt on a new line without exiting the shell
		printf("\n");
		rl_replace_line("", 0); // Clear the current line
		rl_on_new_line(); // Move to a new line
		rl_redisplay(); // Redisplay the prompt on this new line
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