/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:31:34 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:28:02 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output(char *file, int mode)
{
	int		fd;

	fd = 0;
	if (mode == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == 0)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
		if (g_bm.parent_pid == getpid())
			return ;
		else
			exit(g_bm.errno);
	}
	dup2(fd, 1);
	close(fd);
}
