/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/24 15:19:56 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	update_env(char ***env, char *name, char *old)
{
	// check for old
	// replace old with new
	return (0);
}

int	handle_error(int r_value, char *r_message)
{
	perror(r_message);
	return (r_value);
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
