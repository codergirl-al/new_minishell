/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:14:56 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/16 17:19:51 by apeposhi         ###   ########.fr       */
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

void	setup_signal_handling(void)
{
	struct	termios term_settings;

    // Disable the control characters for terminal like Ctrl-C (handled within the program)
	tcgetattr(STDIN_FILENO, &term_settings);
	term_settings.c_lflag &= ~ECHOCTL; // Disable echo control characters like ^C for Ctrl-C
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_settings);
    // Setup signal handlers
	signal(SIGQUIT, SIG_IGN); // Ignore Ctrl-\"
	signal(SIGINT, handle_signal); // Handle Ctrl-C as specified
}
