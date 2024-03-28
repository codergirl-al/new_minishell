/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:19:32 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/28 15:17:09 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// int	validate_export_var(const char *name)
// {
// 	const char	*ptr;

// 	if (!name || !*name || !(ft_isalpha(*name)) || *name == '_')
// 		return (0);
// 	ptr = name + 1;
// 	while (*ptr)
// 	{
// 		if (!ft_isalnum(*ptr) && *ptr != '_')
// 			return (0);
// 		ptr++;
// 	}
// 	return (1);
// }

// static void	handle_reallocation(char ***env, char ***new_env, char *new_var)
// {
// 	size_t	size;
// 	size_t	i;

// 	size = 0;
// 	while (*(env)[size])
// 		++size;
// 	*(new_env) = malloc(sizeof(char *) * (size + 2));
// 	if (!*(new_env))
// 	{
// 		free(*(new_env));
// 		return (handle_void_perror("Failed to reallocate environment array"));
// 	}
// 	i = -1;
// 	while (++i < size)
// 		*(new_env)[i] = *(env)[i];
// 	*(env)[size] = new_var;
// 	*(env)[size + 1] = NULL;
// }

// void	handle_env(char ***env, const char *name, const char *value)
// {
// 	char	*new_var;
// 	char	**new_env;
// 	size_t	len;
// 	size_t	i;

// 	len = ft_strlen(name) + ft_strlen(value) + 2;
// 	new_var = malloc(len);
// 	new_env = NULL;
// 	if (!new_var)
// 		return (handle_void_perror("Failed to allocate memory."));
// 	snprintf(new_var, len, "%s=%s", name, value);
// 	i = 0;
// 	while (*(env)[++i])
// 	{
// 		if (ft_strncmp(env[i], name, strlen(name)))
// 		{
// 			dprintf(2, "found\n");
// 			free(*(env)[i]);
// 			*(env)[i] = new_var;
// 			return ;
// 		}
// 		dprintf(2, "=|=|==|=|=\n");
// 	}
// 	handle_reallocation(env, &new_env, new_var);
// 	free(*(env));
// 	*(env) = new_env;
// }

// void	b_export(t_data *data, char *assignment)
// {
// 	char	*pos;
// 	char	*name;
// 	char	*value;

// 	if (!assignment)
// 		return (handle_void_error("export: Missing argument\n"));
// 	pos = ft_strchr(assignment, '=');
// 	if (!pos || pos == assignment)
// 		return (handle_void_error("export: Invalid assignment\n"));
// 	*pos = '\0';
// 	if (!validate_export_var(assignment))
// 	{
// 		fprintf(stderr, "export: '%s' is not a valid identifier\n", assignment);
// 		*pos = '=';
// 		return ;
// 	}
// 	*pos = '=';
// 	name = assignment;
// 	value = pos + 1;
// 	handle_env(*data->envp, name, value);
// }

// #include "../../include/minishell.h"

// // Corrected validation function
// int validate_export_var(const char *name) {
//     if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
//         return (0);
//     for (const char *ptr = name + 1; *ptr; ptr++) {
//         if (!ft_isalnum(*ptr) && *ptr != '_')
//             return (0);
//     }
//     return (1);
// }

// // Assuming these functions are correctly defined elsewhere

// void update_or_add_env_var(char ***env, char *name, char *value) {
//     size_t len = ft_strlen(name) + ft_strlen(value) + 2;
//     char *new_var = malloc(len);
//     if (!new_var) {
//         handle_void_error("Failed to allocate memory for new environment variable.");
//         return;
//     }
//     snprintf(new_var, len, "%s=%s", name, value);

//     for (size_t i = 0; (*env)[i]; i++) {
//         if (strncmp((*env)[i], name, ft_strlen(name)) == 0 && (*env)[i][ft_strlen(name)] == '=') {
//             free((*env)[i]);
//             (*env)[i] = new_var;
//             return; // Existing variable updated; no further action required.
//         }
//     }

//     // Variable not found; add as a new variable.
//     // Calculate the current size of the environment array.
//     size_t size;
//     for (size = 0; (*env)[size]; size++);

//     // Allocate space for the new environment array.
//     char **new_env = malloc(sizeof(char *) * (size + 2)); // +1 for new entry, +1 for NULL
//     if (!new_env) {
//         free(new_var); // Cleanup new_var on allocation failure.
//         handle_void_error("Failed to allocate memory for expanded environment array.");
//         return;
//     }

//     // Copy existing variables to the new environment array.
//     for (size_t i = 0; i < size; i++) {
//         new_env[i] = (*env)[i];
//     }
//     new_env[size] = new_var; // Append the new variable.
//     new_env[size + 1] = NULL; // Null-terminate the new environment array.

//     free(*env); // Free the old environment array.
//     *env = new_env; // Update the pointer to point to the new array.
// }

// void b_export(t_data *data, char *assignment) {
//     if (!assignment || validate_export_var(assignment)) {
//         handle_void_error("export: Invalid or missing argument.");
//         return;
//     }
//     char *pos = strchr(assignment, '=');
//     if (!pos) {
//         handle_void_error("export: Invalid format. Use NAME=VALUE.");
//         return;
//     }
//     *pos = '\0'; // Temporarily terminate the string to isolate the name.
//     update_or_add_env_var(&(data->envp), assignment, pos + 1);
//     *pos = '='; // Restore the original assignment string.
// }
