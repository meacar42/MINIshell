/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolarSign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:34:54 by meacar            #+#    #+#             */
/*   Updated: 2023/07/19 21:35:56 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar(char *str)
{
	int	k;

	k = check_dollar2(0, 0, str);
	if (!valid_op(*(ft_strchr(str, '$') + 1)) || (k % 2 == 1))
		return (0);
	return (1);
}

int	check_dollar2(int i, int k, char *str)
{
	while (str[i] && str[i] != '$')
	{
		if (str[i] == DOUBLE_QUOTE)
		{
			i++;
			while (str[i++] != DOUBLE_QUOTE && str[i] && str[i] != '$')
				i++;
			if (str[i] == DOUBLE_QUOTE && str[i] != '$')
				i++;
		}
		else if (str[i] == SINGLE_QUOTE)
		{
			i++;
			k++;
			while (str[i] != SINGLE_QUOTE && str[i] && str[i] != '$')
				i++;
		}
		else
			i++;
	}
	return (k);
}

static char	*get_str2(char *str, int *pos, int type)
{
	int		first;
	char	*data;

	first = *pos;
	while (str[*pos] != type && str[*pos])
		(*pos)++;
	data = ft_substr(str, first, *pos - first);
	(*pos)++;
	return (data);
}

char	*parse_dollar_op(char *str)
{
	int		i;
	int		first;
	char	*env;
	char	*result;
	char	*data;

	i = 0;
	result = NULL;
	data = get_str2(str, &i, '$');
	push_new_str(&result, data);
	first = i;
	if (str[i] == '?' && ++i)
		push_new_str(&result, ft_itoa(g_bm.errno));
	else
	{
		while (valid_op(str[i]))
			(i)++;
		data = ft_substr(str, first, i - first);
		env = get_env(data);
		push_new_str(&result, env);
		free(data);
	}
	data = get_str2(str, &i, 0);
	push_new_str(&result, data);
	return (result);
}

char	*dollar(char *str)
{
	char	*tmp;
	char	*new_str;

	new_str = ft_strdup(str);
	while (ft_strchr(new_str, '$') && check_dollar(new_str))
	{
		tmp = new_str;
		new_str = parse_dollar_op(new_str);
		free(tmp);
	}
	return (new_str);
}
