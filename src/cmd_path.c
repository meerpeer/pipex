/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 12:51:28 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/19 13:22:08 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path_str(char **envp)
{
	char	*PATH_str;
	int		i;

	i = 0;
	PATH_str = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			PATH_str = ft_substr(envp[i], 5 , ft_strlen(envp[i]) - 5);
			if (!PATH_str)
				exit (1);
			break;
		}
		i++;
	}
	return (PATH_str);
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
	char	*PATH_str;
	int		i;
	
	PATH_str = get_path_str(envp);
	paths = ft_split(PATH_str, ':');
	i = 0;
	while (paths[i])
	{
		append_str(&paths[i], "/");
		append_str(&paths[i], cmd);
		if (access(paths[i], F_OK | X_OK) == 0) // look up f_OK and X_OK and acces
			return (paths[i]);
		i++;
	}
	exit (1);
}