/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/24 19:06:10 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_error(int r_value, char *r_message)
{
	perror(r_message);
	return (r_value);
}

void    handle_void_perror(char *message)
{
    perror(message);
    return ;
}

void    handle_void_error(char  *message)
{
    fprintf(stderr, message);
    return ;
}

//work in progress as to how the args will look like
// let's have a chat about it tomorrow
void    execute_builtin(char *cmd, char *path, char ***env, char *assign, const char *key, char **args)
{
    size_t  i;

    i = -1;
    while (cmd[++i] != NULL)
    {
        if (cmd == "cd")
            b_cd(path, args);
        else if (cmd == "echo")
            b_echo(args);
        else if (cmd == "env")
            b_env(env);
        else if (cmd == "exit")
            b_exit(args);
        else if (cmd == "export")
            b_export(env, assign);
        else if (cmd == "pwd")
            b_pwd();
        else if (cmd == "unset")
            b_unset(env, key);
    }
}


int	update_env_var(char **env, const char *key, const char *value)
{
	if (!env || !*env || !key || !value) {
		fprintf(stderr, "Invalid argument(s) provided to update_env_var.\n");
		return (1);
	}

	// char *key_equals = malloc(strlen(key) + 2);
	// if (!key_equals)
	// 	return(handle_error(EXIT_FAILURE, "Memory allocation failed for key search string"));
    // sprintf(key_equals, "%s=", key);

    // char *found = ft_arrcmp((void **)*env, (void *)key_equals);
    // if (found) {
    //     int index = (found - (char *)*env) / sizeof(char *);

    //     free((*env)[index]);
        
    //     size_t new_entry_len = strlen(key) + strlen(value) + 2;
    //     char *new_entry = malloc(new_entry_len);
    //     if (!new_entry) {
    //         perror("Unable to allocate memory for new environment value");
    //         free(key_equals);
    //         exit(EXIT_FAILURE);
    //     }
    //     snprintf(new_entry, new_entry_len, "%s=%s", key, value);
    //     (*env)[index] = new_entry;
    // }
    // free(key_equals);
    return (0);
}
