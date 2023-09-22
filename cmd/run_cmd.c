/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyildir <beyildir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:33:34 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 20:28:02 by beyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contain_heredoc(t_process *process)
{
	int	i;

	i = 0;
	while (process->redirects[i])
	{
		if (!ft_strncmp(process->redirects[i], "<<", 2))
			return (1);
		i++;
	}
	return (0);
}

void	close_fd_all(void)
{
	t_process	*process;

	process = g_bm.process;
	while (process)
	{
		if (contain_heredoc(process) && process->heredoc_fd[0] > 2)
			close(process->heredoc_fd[0]);
		if (process->fd[0] > 2)
			close(process->fd[0]);
		if (process->fd[1] > 2)
			close(process->fd[1]);
		process = process->next;
	}
}

void	route_cmd(t_process *process)
{
	if (g_bm.process_count > 1)
	{
		if (contain_heredoc(process))
		{
			if (process->next != NULL)
				dup2(process->fd[1], 1);
		}
		else
		{
			if (process->prev == NULL)
				dup2(process->fd[1], 1);
			else if (process->next == NULL)
				dup2(process->prev->fd[0], 0);
			else
			{
				dup2(process->prev->fd[0], 0);
				dup2(process->fd[1], 1);
			}
		}
	}
	get_all_inputs(process);
	set_all_outputs(process);
	close_fd_all();
}

void	run_cmd(t_process *process)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		route_cmd(process);
		run_builtin(process->execute);
		path = get_path(*process->execute);
		execve(path, process->execute, g_bm.env);
		cmd_error(*process->execute);
		exit(g_bm.errno);
	}
	else
		process->pid = pid;
}
