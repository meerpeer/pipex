/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:39:26 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/24 14:37:56 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(int pipe_ends[2], char *cmd_str, char **envp)
{
	char	**split_cmd;
	char	*options;

	close(pipe_ends[0]);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(pipe_ends[1]);
	split_cmd = ft_split(cmd_str, ' ');
	if (!split_cmd)
			exit (1);
	options = get_options(split_cmd);
	execve(get_cmd_path(split_cmd[0], envp), &options, envp);
	if (options)
		free (options);
	free_2d_array(split_cmd);
}

void	start_child_proccess(int pipe_ends[2], char *cmd_str, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
		child_process(pipe_ends, cmd_str, envp);
	else
	{
		close(pipe_ends[0]);
		close(pipe_ends[1]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	pipe_fds[2];
	int	fd_out;

	(void) envp;

	fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
		return (1);
	if (pipe(pipe_fds) == -1)
		return (1);
	if (argc < 5)
		exit (1);
	i = 1;
	while (i < argc - 2)
	{
		start_child_proccess(pipe_fds, argv[i], envp);
		i++;
	}
	dup2(fd_out, STDOUT_FILENO);
	child_process(pipe_fds, argv[i], envp);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	while (wait(NULL) > 0)
		continue;
}

//open trunc creat rdwr
//while (wait(NULL) > 0) for making sure all child processes are done