/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:32:18 by meacar            #+#    #+#             */
/*   Updated: 2023/07/19 14:49:59 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), env_len(NULL, 0) + 1);
	while (g_bm.env[i])
	{
		if (ft_strncmp(g_bm.env[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_bm.env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_bm.env);
	g_bm.env = new_env;
}

void	builtin_unset(char **input)
{
	char	*data;

	input++;
	while (*input)
	{
		check_env(*input, NULL, 1, *input);
		data = ft_strjoin(*input, "=");
		remove_env(data);
		free(data);
		input++;
	}
	set_paths();
	if (!(g_bm.parent_pid == getpid()))
		exit (0);
}

int	env_len(char *str, int flag)
{
	char	**env;
	int		i;

	env = g_bm.env;
	if (flag == 0)
	{
		while (*env)
			env++;
		return (env - g_bm.env);
	}
	else
	{
		i = 0;
		while (env[i])
		{
			if (check_env(str, env[i], 0, NULL))
				return (i);
			i++;
		}
	}
	return (0);
}

int	exp_error(char *str)
{
	g_bm.errno = 1;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
	if (!(g_bm.parent_pid == getpid()))
		exit(g_bm.errno);
	return (0);
}

int	err_check(char *str, char *input)
{
	if (*str)
	{
		if (*str == '=')
			return (exp_error(input));
		if (*str >= '0' && *str <= '9')
			return (exp_error(input));
		while (*str)
		{
			if (*str == ' ' || *str == '\t')
				return (exp_error(input));
			str++;
		}
	}
	return (1);
}
