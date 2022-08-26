/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:45:47 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/26 12:50:29 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child2_process(char *outfile, int pipe_end[2], char *cmd2, char **envp)
{
	char	**split_cmd;
	int		fd_outfile;

	close(pipe_end[1]);
	fd_outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_outfile < 0 || access(outfile, F_OK | W_OK) != 0)
	{
		perror(outfile);
		exit (1);
	}
	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(pipe_end[0]);
	close(fd_outfile);
	split_cmd = ft_split(cmd2, ' ');
	if (!split_cmd)
		exit (1);
	if (execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp) == -1)
	{
		perror(NULL);
		exit (1);
	}
	exit (1);
}

void	child1_process(char *infile, int pipe_end[2], char *cmd1, char **envp)
{
	char	**split_cmd;
	int		fd_infile;

	close(pipe_end[0]);
	fd_infile = open(infile, O_RDONLY);
	if (fd_infile < 0)
	{
		perror(infile);
		exit (1);
	}
	dup2(fd_infile, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[1]);
	close(fd_infile);
	split_cmd = ft_split(cmd1, ' ');
	if (!split_cmd)
		exit (1);
	if (execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp) == -1)
	{
		perror(NULL);
		exit (1);
	}
	exit (1);
}

void	start_pipex(char **argv, char **envp)
{
	int		ends[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(ends) == -1)
		exit (1);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("fork"));
	else if (pid1 == 0)
		child1_process(argv[1], ends, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
		return (perror("fork"));
	else if (pid2 == 0)
		child2_process(argv[4], ends, argv[3], envp);
	close(ends[0]);
	close(ends[1]);
	waitpid(pid2, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	exit (WEXITSTATUS(status));
}
