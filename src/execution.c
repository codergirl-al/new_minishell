/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:01:36 by apeposhi          #+#    #+#             */
/*   Updated: 2024/04/05 15:15:38 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>

static char *ft_getpath(char **env, char *f_cmd) {
  char *path;
  char *p1;
  char *tmp;
  char *s_tmp;

  s_tmp = NULL;
  p1 = ft_arrcmp((void **)env, "PATH=");
  if (!p1)
    return (NULL);
  path = ft_strdup(p1);
  path += 5;
  tmp = path;
  while (*path && access(s_tmp, X_OK)) {
    if (s_tmp)
      free(s_tmp);
    path = tmp;
    while (*tmp && *tmp != ':')
      tmp++;
    if (*tmp && *tmp == ':')
      *tmp++ = '\0';
    s_tmp = ft_strjoin(path, ft_strjoin("/", f_cmd, 0), STRFREE_S2);
  }
  if (!s_tmp)
    s_tmp = ft_strjoin("./", f_cmd, 0);
  return (s_tmp);
}

static int execute(t_list *lst, t_data *data, int *stdin, t_exec exe) {
  exe.cmd = lst_to_arr(lst);

  dup2(*stdin, STDIN_FILENO);
  exe.path = ft_getpath(data->envp, exe.cmd[0]);
  close(*stdin);
  if (exe.fd_in > 2) {
    dup2(exe.fd_in, STDIN_FILENO);
    close(exe.fd_in);
  }
  if (exe.fd_out > 2) {
    dup2(exe.fd_out, STDOUT_FILENO);
    close(exe.fd_out);
  }
  //   printf("zebi%d %d path%s\n", exe.fd_in, exe.fd_out, exe.path);
  execve(exe.path, exe.cmd, data->envp);
  return (1);
}

static int execute_pipe(char *cmd, t_data *data, int *stdin) {
  int fd[2];
  t_exec exe;
  t_list *lst;

  exe.fd_in = 0;
  exe.fd_out = 1;
  lst = parse_cmd(cmd, data, &exe, true);
  if (exe.fd_in < 0 || exe.fd_out < 0)
    return 0;
  if (!pipe(fd) && !fork()) {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execute(lst, data, stdin, exe);
    return (1);
  }
  close(fd[1]);
  close(*stdin);
  *stdin = fd[0];
  ft_lstfree(lst);
  return (0);
}

// static int	is_builtin(t_list *lst) {
//	if (!ft_strncmp("cd", (char *)lst->content, 3))
// 		return (1);
// 	else if (!ft_strncmp("echo", (char *)lst->content, 5))
// 		return (1);
// 	else if (!ft_strncmp("env", (char *)lst->content, 4))
// 		return (1);
// 	else if (!ft_strncmp("exit", (char *)lst->content, 5))
// 		return 1;
// 	else if (!ft_strncmp("export", (char *)lst->content, 7))
// 		return (1);
// 	else if (!ft_strncmp("pwd", (char *)lst->content, 4))
// 		return (1);
// 	else if (!ft_strncmp("unset", (char *)lst->content, 6))
// 		return (1);
// 	return (0);
// }

static int execute_last(char *cmd, t_data *data, int *stdin) {
  t_exec exe;
  t_list *lst;

  exe.fd_in = 0;
  exe.fd_out = 1;
  lst = parse_cmd(cmd, data, &exe, true);
  // if (is_builtin(lst)) {
  // 	exe.cmd = lst_to_arr(lst);
  // 	execute_builtin(data, &exe);
  // }
  // else if (!fork())
  if (exe.fd_in < 0 || exe.fd_out < 0)
    return 0;
  if (!fork()) {
    execute(lst, data, stdin, exe);
    return (1);
  }
  close(*stdin);
  while (waitpid(-1, NULL, WUNTRACED) != -1)
    ;
  *stdin = dup(STDIN_FILENO);
  ft_lstfree(lst);
  return (0);
}

int iter_cmd(t_data *data) {
  char *start;
  char *end;
  int stdin;

  start = data->input;
  end = data->input;
  stdin = dup(STDIN_FILENO);
  while (data->input && *end) {
    if (*end == '\'' || *end == '\"')
      end = iter_quotes(end);
    else if (*end == '|') {
      *end = 0;
      execute_pipe(start, data, &stdin);
      start = end + 1;
    }
    end++;
  }
  execute_last(start, data, &stdin);
  close(stdin);
  return (0);
}
