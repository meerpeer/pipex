/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 12:51:28 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/01 13:05:12 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_2d_array(char	**array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
	return ;
}

char	*get_path_str(char **envp, char *cmd)
{
	char	*path_str;
	int		i;

	i = 0;
	path_str = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			if (!path_str)
				exit (1);
			break ;
		}
		i++;
	}
	if (!path_str)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit (1);
	}
	return (path_str);
}

void	append_strs(char **path, char *str, char *str2)
{
	char	*tmp;

	tmp = *path;
	*path = ft_strjoin(*path, str);
	if (!*path)
		exit (1);
	free (tmp);
	if (str2)
		append_strs(path, str2, NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_str;
	char	**paths;
	char	*path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	path_str = get_path_str(envp, cmd);
	paths = ft_split(path_str, ':');
	path = NULL;
	i = 0;
	while (paths[i])
	{
		append_strs(&paths[i], "/", cmd);
		if (access(paths[i], F_OK | X_OK) == 0)
			path = ft_strdup(paths[i]);
		i++;
	}		
	free (path_str);
	free_2d_array (paths);
	if (path)
		return (path);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("pipex: command not found\n", 2);
	exit (127);
}
