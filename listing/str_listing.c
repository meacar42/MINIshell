/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_listing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:34:51 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:16:17 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	operator_check(char **str)
{
	if (!**str)
		return (0);
	if (*str[0] == '<' && *str[1] == '<')
		return (HERE_DOC);
	if (*str[0] == '>' && *str[1] == '>')
		return (RED_APPEND);
	if (*str[0] == '<')
		return (RED_INPUT);
	if (*str[0] == '>')
		return (RED_OUTPUT);
	if (*str[0] == '|')
		return (PIPE);
	if ((*str[0] == ' ') || (*str[0] == '\t'))
		return (1);
	return (0);
}

void	string_found(char **str)
{
	char	type;

	if (**str == '"')
		type = '"';
	if (**str == '\'')
		type = '\'';
	(*str)++;
	while (**str)
	{
		if (**str == type)
		{
			(*str)++;
			if (operator_check(&(*str)))
				break ;
			else
				while (**str && !(operator_check(&(*str))))
					(*str)++;
			return ;
		}
		(*str)++;
	}
}

void	str_listing(char **str)
{
	int		len;
	char	*head;
	char	*chain_str;

	while (**str && ((**str == ' ') || (**str == '\t')))
		(*str)++;
	head = *str;
	if (**str && ((**str == DOUBLE_QUOTE) || (**str == SINGLE_QUOTE)))
		string_found(&(*str));
	else
		str = str_short(str);
	len = *str - head;
	if (len > 0)
	{
		chain_str = ft_substr(head, 0, len);
		add_list(&g_bm.chain, new_list(chain_str, STRING));
	}
}

char	**str_short(char **str)
{
	while (**str)
	{
		if (**str && ((**str == DOUBLE_QUOTE) || (**str == SINGLE_QUOTE)))
		{
			(*str)++;
			while (!((**str == DOUBLE_QUOTE) || (**str == SINGLE_QUOTE)) \
			&& **str)
				(*str)++;
		}
		if (!(operator_check(&(*str))))
			(*str)++;
		else
			break ;
	}
	return (str);
}
