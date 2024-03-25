/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/25 18:31:42 by apeposhi         ###   ########.fr       */
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

void    execute_builtin(t_data *data, t_exec *exe)
{
    if (!strcmp("cd", exe->cmd[0]))
        b_cd(exe->cmd[1], data);
    else if (!strcmp("echo", exe->cmd[0]))
        b_echo(exe->cmd);
    else if (!strcmp("env", exe->cmd[0]))
        b_env(data->envp);
    else if (!strcmp("exit", exe->cmd[0]))
        b_exit(data);
    else if (!strcmp("export", exe->cmd[0]))
        b_export(data->envp, exe->cmd[1]);
    else if (!strcmp("pwd", exe->cmd[0]))
        b_pwd();
    else if (!strcmp("unset", exe->cmd[0]))
        b_unset(data->envp, exe->cmd);
}

// work on this later

int	update_env_var(char **env, const char *key, const char *value)
{
	if (!env || !*env || !key || !value) {
		fprintf(stderr, "Invalid argument(s) provided to update_env_var.\n");
		return (1);
	}

	char *key_equals = malloc(strlen(key) + 2);
	if (!key_equals)
		return(handle_error(EXIT_FAILURE, "Memory allocation failed for key search string"));
    sprintf(key_equals, "%s=", key);

    char *found = ft_arrcmp((void **)*env, (void *)key_equals);
    if (found) {
        int index = (found - (char *)*env) / sizeof(char *);

        free((*env)[index]);
        
        size_t new_entry_len = strlen(key) + strlen(value) + 2;
        char *new_entry = malloc(new_entry_len);
        if (!new_entry) {
            perror("Unable to allocate memory for new environment value");
            free(key_equals);
            exit(EXIT_FAILURE);
        }
        snprintf(new_entry, new_entry_len, "%s=%s", key, value);
        (*env)[index] = new_entry;
    }
    free(key_equals);
    return (0);
}
