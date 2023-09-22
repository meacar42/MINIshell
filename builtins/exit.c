/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:31:58 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:28:02 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnumber_with_sign(char *arg)
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (0);
	}
	return (1);
}

void	builtin_exit(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i == 1)
	{
		printf("exit\n");
		exit(g_bm.errno);
	}
	else
	{
		if (ft_isnumber_with_sign(input[1]))
		{
			if (i > 2)
			{
				write(2, "exit\nminishell: exit: too many arguments\n", 41);
				g_bm.errno = 1;
				return ;
			}
			exit(ft_atoi(input[1]) % 256);
		}
		write(2, "exit\nminishell: exit: numeric argument required\n", 48);
		exit(-1 % 256);
	}
}
