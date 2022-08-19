/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:39:26 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/19 16:56:20 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_path;
	char	*cmd = "ls";
	char	*options[3] = {"ls", "-la", NULL};

	(void) argc;
	(void) argv;
//	(void) envp;
	cmd_path = get_cmd_path(cmd, envp);
	if (!cmd_path)
	{
		perror(cmd_path);
		return (-1);
	}
	
	execve(cmd_path, options, envp);
	return (0);

	pid_t	pid1;
	pid_t	pid2;
	pid_t	res;
	int		status;
	int		ends[2];
	
	if (pipe(ends) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
	{
		usleep(50000);
		ft_printf("Child 1: I'm the first child\n");
		return (0);
	}
	else if (pid1 > 0)
	{
		pid2 = fork();
		if (pid2 == -1)
			return (1);
		else if (pid2 == 0)
		{
			usleep(60000);
			printf("child 2: second child ...\n");
			return (2);
		}
		else if (pid2 > 0)
		{
			ft_printf("Parent: I have 2 children\n");
			res = waitpid(pid1, &status, 0);
			ft_printf("parent: received child1 %d\n", res);
			if(WIFEXITED(status))
				ft_printf("Parent: it exited succesfully with code: %i\n", WEXITSTATUS(status));
			else
				ft_printf("Parent : it was interupted\n");
			res = waitpid(pid2, &status, 0);
			ft_printf("parent: received child2 %d\n", res);
			if(WIFEXITED(status))
				ft_printf("Parent: it exited succesfully with code: %i\n", WEXITSTATUS(status));
			else
				ft_printf("Parent : it was interupted\n");
		}
	}
	return 0;
}

//open trunc creat rdwr
//while (wait(NULL) > 0) for making sure all child processes are done