/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:31:52 by meacar            #+#    #+#             */
/*   Updated: 2023/07/19 15:30:40 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char **input)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	if (g_bm.fail == 1)
		return ;
	if (input[i])
		i = echo_control(input, i);
	if (i > 1)
		flag = 0;
	g_bm.errno = 0;
	while (input[i])
	{
		ft_putstr_fd(input[i], 1);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	if (!(g_bm.parent_pid == getpid()))
		exit(EXIT_SUCCESS);
}

int	echo_control(char **input, int i)
{
	int	j;

	j = 0;
	while (input[i])
	{
		if (input[i][j] == '-')
		{
			j++;
			while (input[i][j] == 'n')
				j++;
			if (input[i][j] != '\0')
				break ;
			if (j == 1)
				break ;
			else
				i++;
			j = 0;
		}
		else
			break ;
	}
	return (i);
}
