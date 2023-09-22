/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:32:00 by meacar            #+#    #+#             */
/*   Updated: 2023/07/19 19:00:20 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env(char *str, char *env, int flag, char *input)
{
	if (flag == 2)
		return (ft_strcomp(str));
	if (flag == 1)
		return (err_check(str, input));
	else if (flag == 0)
	{
		if (!str || !env)
			return (0);
		while ((*str || *env) && *env != '=' && *str != '=')
		{
			if (*str != *env)
				return (0);
			env++;
			str++;
		}
		if ((*str == '=' && *env != '=') || (*str != '=' && *env == '='))
		{
			if (*env == '\0' || *str == '\0')
				return (1);
			return (0);
		}
	}
	return (1);
}

void	add_env(char *str)
{
	int		i;
	char	**env;
	char	**new_env;

	i = 0;
	env = g_bm.env;
	new_env = ft_calloc(sizeof(char **), env_len(NULL, 0) + 2);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	free_array(g_bm.env);
	g_bm.env = new_env;
}

int	is_include(char *str)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	env = g_bm.env;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && str[j])
		{
			if (str[j] == '=' && env[i][j] == '=')
				return (i);
			if (str[j] != env[i][j])
				break ;
			j++;
		}
		i++;
	}
	if (env_len(str, 1))
		return (env_len(str, 1));
	return (-1);
}

void	builtin_export(char **input)
{
	input++;
	if (*input == NULL)
		builtin_env2();
	export_while(input);
	set_paths();
	if (!(g_bm.parent_pid == getpid()))
		exit (EXIT_SUCCESS);
}

void	export_while(char **input)
{
	int		pos;
	char	*tmp;

	while (*input)
	{
		if (check_env(*input, NULL, 1, *input))
		{
			pos = is_include(*input);
			if (pos != -1)
			{
				if (!check_env(*input, NULL, 2, NULL))
				{
					tmp = g_bm.env[pos];
					g_bm.env[pos] = ft_strdup(*input);
					free(tmp);
				}
			}
			else
				add_env(*input);
		}
		input++;
	}
}
