/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:39:26 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/18 15:27:54 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	char	*PATH_str = NULL;
	char	*tmp;
	int		i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			PATH_str = ft_substr(envp[i], 5 , ft_strlen(envp[i]) - 5);
			if (!PATH_str)
				return (NULL);
			break;
		}
		i++;
	}
	paths = ft_split(PATH_str, ':');
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free (tmp);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0) // look up f_OK and X_OK and acces
			return (cmd_path);
		free (cmd_path);
		i++;
	}
	exit (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_path;
	char	*cmd = "ls";
	char	*options[3] = {"ls", "-la", NULL};

	(void) argc;
	(void) argv;
	cmd_path = get_cmd_path(cmd, envp);
	if (!cmd_path)
	{
		perror(cmd_path);
		return (-1);
	}
	ft_printf("cmd path = %s\n", cmd_path);
	execve(cmd_path, options, envp);
	return (0);
}
