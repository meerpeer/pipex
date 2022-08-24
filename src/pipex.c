/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:45:47 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/24 15:33:37 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child1_process(int fd_infile, int pipe_end[2], char *cmd1, char **envp)
{
	char **split_cmd;
	char *options;

	dup2(fd_infile, STDOUT_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	split_cmd = ft_split(cmd1, ' ');
	if (!split_cmd)
			exit (1);
	options = get_options(split_cmd);
	execve(get_cmd_path(split_cmd[0], envp), &options, envp);
	if (options)
		free (options);
	free_2d_array(split_cmd);
	exit (1);
}

void	child2_process(int fd_outfile, int pipe_end[2], char *cmd2, char **envp)
{
	char **split_cmd;
	char *options;

	dup2(pipe_end[0], STDIN_FILENO);
	close(pipe_end[1]);
	dup2(fd_outfile, STDOUT_FILENO);
	split_cmd = ft_split(cmd2, ' ');
	if (!split_cmd)
			exit (1);
	options = get_options(split_cmd);
	execve(get_cmd_path(split_cmd[0], envp), &options, envp);
	if (options)
		free (options);
	free_2d_array(split_cmd);
	exit (1);
}

void	start_pipex(int infile_fd, int outfile_fd, char **argv, char **envp)
{
	int		ends[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(ends) == -1)
		exit (1);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("fork"));
	else if (pid1 == 0)
		child1_process(infile_fd, ends, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
		return (perror("fork"));
	else if (pid2 == 0)
		child2_process(outfile_fd, ends, argv[3], envp);
	close(ends[0]);
	close(ends[1]);
	close(infile_fd);
	close(outfile_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return ;
}