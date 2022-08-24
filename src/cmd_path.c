/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 12:51:28 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/24 16:44:45 by mevan-de      ########   odam.nl         */
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

char	*get_path_str(char **envp)
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
	return (path_str);
}

void	append_str(char **path, char *str)
{
	char	*tmp;

	tmp = *path;
	*path = ft_strjoin(*path, str);
	if (!*path)
		exit (1);
	free (tmp);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_str;
	int		i;

	path_str = get_path_str(envp);
	paths = ft_split(path_str, ':');
	i = 0;
	while (paths[i])
	{
		append_str(&paths[i], "/");
		append_str(&paths[i], cmd);
		if (access(paths[i], F_OK | X_OK) == 0)
			return (paths[i]);
		i++;
	}
	exit (1);
}
