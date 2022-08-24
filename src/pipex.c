/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:45:47 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/24 17:44:42 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child2_process(int fd_outfile, int pipe_end[2], char *cmd2, char **envp)
{
	char	**split_cmd;

	dup2(pipe_end[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(pipe_end[1]);
	split_cmd = ft_split(cmd2, ' ');
	if (!split_cmd)
		exit (1);
	execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp);
	//free_2d_array(split_cmd);
	exit (1);
}

void	child1_process(int fd_infile, int pipe_end[2], char *cmd1, char **envp)
{
	char	**split_cmd;

	dup2(fd_infile, STDIN_FILENO);
	dup2(pipe_end[1], STDOUT_FILENO);
	close(pipe_end[0]);
	split_cmd = ft_split(cmd1, ' ');
	if (!split_cmd)
		exit (1);
	execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp);
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
	while (wait(NULL) > 0)
		continue ;
	return ;
}
