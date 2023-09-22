/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:31:54 by meacar            #+#    #+#             */
/*   Updated: 2023/07/19 21:21:11 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(void)
{
	char	**env;

	env = g_bm.env;
	while (*env)
	{
		if (!ft_strcomp(*env))
			printf("%s\n", *env);
		env++;
	}
	if (!(g_bm.parent_pid == getpid()))
		exit (EXIT_SUCCESS);
}

void	builtin_env2(void)
{
	env_extra(NULL, -1, -1, 0);
	if (!(g_bm.parent_pid == getpid()))
		exit (EXIT_SUCCESS);
}

void	env_extra(char **env, int i, int j, int flag)
{
	env = g_bm.env;
	while (env[++i])
	{
		printf("declare -x ");
		while (env[i][++j])
		{
			if (env[i][j - 1] == '=')
			{
				flag = 1;
				printf("\"");
			}
			printf("%c", env[i][j]);
		}
		j = -1;
		if (flag == 1)
		{
			flag = 0;
			printf("\"");
		}
		printf("\n");
	}
}

int	ft_strcomp(char *s1)
{
	while (*s1)
	{
		if (*s1 == '=')
			return (0);
		s1++;
	}
	return (1);
}
