/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:23:31 by apeposhi          #+#    #+#             */
/*   Updated: 2024/03/27 12:16:32 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *find_env_var(char **env, const char *name) {
  size_t name_len = strlen(name);
  for (size_t i = 0; env[i] != NULL; i++) {
    if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=') {
      return env[i] + name_len + 1;
    }
  }
  return NULL;
}

void b_cd(char *path, t_data *data)
{
  if (!data) {
    fprintf(stderr, "cd: invalid data structure\n");
    return;
  }

  char oldPath[1024];
  if (getcwd(oldPath, sizeof(oldPath)) == NULL) {
    perror("cd: error getting current directory");
    data->exit_status = 1;
    return;
  }
  if (path == NULL || *path == '\0') {
    path = find_env_var(data->envp, "HOME");
    if (path == NULL) {
      fprintf(stderr, "cd: HOME not set\n");
      data->exit_status = 1;
      return;
    }
  }
  if (chdir(path) != 0) {
    perror("cd");
    data->exit_status = 1;
    return;
  }

  update_env_var(&(data->envp), "OLDPWD", oldPath);
  char newPath[1024];
  if (getcwd(newPath, sizeof(newPath)) == NULL) {
    perror("cd: error getting new directory");
    data->exit_status = 1;
    return;
  }
  update_env_var(&(data->envp), "PWD", newPath);

  data->exit_status = 0;
}
