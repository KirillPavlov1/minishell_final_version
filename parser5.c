/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchalmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:42:18 by rchalmer          #+#    #+#             */
/*   Updated: 2021/07/28 22:42:21 by rchalmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line5_1(char *line, int *i, int *m, t_all **all)
{
	if (line[*i] == '|')
	{
		*m = 0;
		(*all)->cmd->way = find_binary((*all)->cmd->argv[0], (*all)->path);
		ft_listadd_back(&(*all)->cmd, ft_listnew());
		(*all)->cmd = ft_listlast((*all)->cmd);
		(*i)++;
		(*all)->f = 0;
		(*all)->cmd->count = count_argv(line, *i);
		(*all)->cmd->argv = (char **)malloc(sizeof(char *)
				* ((*all)->cmd->count + 1));
		make_null(&(*all)->cmd->argv, (*all)->cmd->count);
		(*all)->to_red = NULL;
		(*all)->old = NULL;
		(*all)->cmd->way = NULL;
	}
}

static void	parse_line50(char *line, int *i, t_all **all)
{
	if (line[*i] == '>')
	{
		(*all)->cmd->dir->redirect = 1;
		(*i)++;
		if (line[*i - 1] == '>' && line[*i] == '>')
		{
			(*all)->cmd->dir->redirect = 2;
			(*i)++;
		}
	}
	if (line[*i] == '<')
	{
		(*all)->cmd->dir->redirect = 3;
		(*i)++;
		if (line[*i - 1] == '<' && line[*i] == '<')
		{
			(*all)->cmd->dir->redirect = 4;
			(*i)++;
		}
	}
}

void	parse_line5(char *line, int *i, int *m, t_all **all)
{
	t_redirect	*p;

	if (line[*i] == '>' || line[*i] == '<')
	{
		redirect_back(&(*all)->cmd->dir, new_redirect());
		p = (*all)->cmd->dir;
		(*all)->cmd->dir = redirect_last((*all)->cmd->dir);
		parse_line50(line, i, all);
		redirect2(line, i, all);
		redirect3(line, i, all);
		redirect4(line, i, all);
		if (!(*all)->to_red)
			(*all)->to_red = ft_strdup("");
		(*all)->cmd->dir->argv = ft_strdup((*all)->to_red);
		free((*all)->to_red);
		(*all)->cmd->dir = p;
		(*all)->to_red = NULL;
	}
	parse_line5_1(line, i, m, all);
}
