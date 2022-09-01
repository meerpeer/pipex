/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:45:47 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/01 15:16:29 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child2_process(int fd_outfile, int pipe_end[2], char *cmd2, char **envp)
{
	char	**split_cmd;

	close(pipe_end[1]);
	if (fd_outfile < 0)
		exit (EXIT_FAILURE);
	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(pipe_end[0]);
	close(fd_outfile);
	split_cmd = ft_split(cmd2, ' ');
	if (!split_cmd)
		exit (1);
	if (execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp) == -1)
	{
		perror("pipex: ");
		exit (1);
	}
	exit (1);
}

void	child1_process(int fd_infile, int pipe_end[2], char *cmd1, char **envp)
{
	char	**split_cmd;

	close(pipe_end[0]);
	if (fd_infile < 0)
		exit (EXIT_FAILURE);
	dup2(fd_infile, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(fd_infile);
	close(pipe_end[1]);
	split_cmd = ft_split(cmd1, ' ');
	if (!split_cmd)
		exit (1);
	if (execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp) == -1)
	{
		perror("pipex :");
		exit (1);
	}
	exit (1);
}

void	start_pipex(int fd_in, int fd_out, char **argv, char **envp)
{
	int		ends[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(ends) == -1)
		exit (1);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("pipex: "));
	else if (pid1 == 0)
		child1_process(fd_in, ends, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
		return (perror("pipex: "));
	else if (pid2 == 0)
		child2_process(fd_out, ends, argv[3], envp);
	close(ends[0]);
	close(ends[1]);
	waitpid(pid2, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	close (fd_in);
	close (fd_out);
	exit (WEXITSTATUS(status));
}
