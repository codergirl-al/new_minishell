/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeposhi <apeposhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:46:23 by khnishou          #+#    #+#             */
/*   Updated: 2024/04/07 22:18:32 by apeposhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*parse_arg(char **cont, t_data *data)
{
	int		it[2];
	int		len;

	it[0] = 0;
	it[1] = 0;
	while ((*cont)[it[0]])
	{
		if ((*cont)[it[0]] == '$')
		{
			dollar_handler(cont, data, &len, it);
			it[0]++;
		}
		else if ((*cont)[it[0]] == '\'')
			squote_handler(cont, it);
		else if ((*cont)[it[0]] == '\"')
			dquote_handler(cont, data, &len, it);
		else
			it[0]++;
	}
	return ((*cont));
}

static int	ft_open(char *start, int len, int flag, t_data *data)
{
	int		fd;
	char	*file_name;

	fd = 0;
	file_name = ft_substr(start, 0, len, 0);
	if (!(!(flag & IS_INOOUT) && (flag & IS_DOUBLE)))
		parse_arg(&file_name, data);
	if (!(flag & IS_INOOUT) && !(flag & IS_DOUBLE))
		fd = open(file_name, O_RDONLY);
	else if ((flag & IS_INOOUT) && !(flag & IS_DOUBLE))
		fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0000644);
	else if (!(flag & IS_INOOUT) && (flag & IS_DOUBLE))
		fd = handle_heredoc(file_name, data);
	else if ((flag & IS_INOOUT) && (flag & IS_DOUBLE))
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0000644);
	if (fd == -1)
	{
		file_name = ft_strjoin("Minishell: ", file_name, STRFREE_S2);
		perror(file_name);
	}
	free(file_name);
	return (fd);
}

static void	redirect(char **str, t_exec *exe, t_data *data)
{
	char	*start;
	int		flag;
	int		*tmp_fd;

	if (!(str && *str))
		return ;
	flag = (!ft_strncmp(">", *str, 1) << 0)
		| ((!ft_strncmp("<<", *str, 2) || !ft_strncmp(">>", *str, 2)) << 1);
	while (**str && (ft_issep(**str) || **str == '>' || **str == '<'))
		*(*str)++ = 0;
	start = *str;
	while (**str && !(ft_issep(**str) || **str == '>' || **str == '<'))
	{
		if (**str == '\"' || **str == '\'')
			*str = iter_quotes(*str);
		(*str)++;
	}
	if (flag & IS_INOOUT)
		tmp_fd = &(exe->fd_out);
	else
		tmp_fd = &(exe->fd_in);
	if (*tmp_fd > 2)
		close(*tmp_fd);
	else if (!(*tmp_fd < 0))
		*tmp_fd = ft_open(start, *str - start, flag, data);
}

static t_list	*set_arg(t_data *data, char *str, t_list *old, bool exp_flag)
{
	t_list	*new;
	char	*cont;

	cont = ft_strdup(str);
	if (!cont)
		return (NULL);
	if (exp_flag)
		parse_arg(&cont, data);
	new = ft_lstnew((void *)cont);
	if (!new)
		return (NULL);
	new->next = old;
	return (new);
}

t_list	*parse_cmd(char *str, t_data *data, t_exec *exe, bool exp_flag)
{
	char	*start;
	t_list	*tmp;

	if (!str)
		return (NULL);
	while (*str && (ft_issep(*str) || *str == '>' || *str == '<'))
		if ((*str == '<') || (*str == '>'))
			redirect(&str, exe, data);
	else
		*(str++) = 0;
	if (*str && !(ft_issep(*str) || *str == '>' || *str == '<'))
		start = str;
	else
		return (NULL);
	while (*str && !(ft_issep(*str) || *str == '>' || *str == '<'))
	{
		if (*str == '\'' || *str == '\"')
			str = iter_quotes(str);
		str++;
	}
	tmp = parse_cmd(str, data, exe, exp_flag);
	tmp = set_arg(data, start, tmp, exp_flag);
	if (!tmp)
		return (NULL);
	return (tmp);
}
