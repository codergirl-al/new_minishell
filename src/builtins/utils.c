/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:00:03 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/22 15:38:21 by apeposhi         ###   ########.fr       */
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

void update_env_var(char ***env, const char *key, const char *value) {
    if (!env || !*env || !key || !value) {
        fprintf(stderr, "Invalid argument(s) provided to update_env_var.\n");
        return;
    }

    char *key_equals = malloc(strlen(key) + 2); // +2 for '=' and '\0'
    if (!key_equals) {
        perror("Memory allocation failed for key search string");
        exit(EXIT_FAILURE);
    }
    sprintf(key_equals, "%s=", key); // Prepare key search pattern

    // Use ft_arrcmp to find the matching environment variable
    char *found = ft_arrcmp((void **)*env, (void *)key_equals);
    if (found) {
        // Calculate the index where the found string is located
        int index = (found - (char *)*env) / sizeof(char *);

        // Free the old value
        free((*env)[index]);
        
        // Create the new entry with updated value
        size_t new_entry_len = strlen(key) + strlen(value) + 2; // +2 for '=' and '\0'
        char *new_entry = malloc(new_entry_len);
        if (!new_entry) {
            perror("Unable to allocate memory for new environment value");
            free(key_equals); // Clean up allocated memory for key search
            exit(EXIT_FAILURE);
        }
        snprintf(new_entry, new_entry_len, "%s=%s", key, value);
        (*env)[index] = new_entry; // Update the environment array
    }

    free(key_equals); // Clean up the allocated memory for key search pattern
    // If the variable is not found, do nothing
}

// char	*get_env_value(char **env, char *val)
// {
// 	char	*wanted_value;
	
// 	wanted_value = ft_arrcmp((void **)env, val);
// 	return (wanted_value);
// }
