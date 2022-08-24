/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:53:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/24 15:12:44 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

// to include execve, access, pipe, dup, dup2
# include <unistd.h>
// to include wait
# include <sys/wait.h>
//# include <stdlib.h>
# include <fcntl.h>

char	*get_cmd_path(char *cmd, char **envp);
char	*get_options(char **cmd_and_options);
void	free_2d_array(char	**array);
void	start_pipex(int infile_fd, int outfile_fd, char **argv, char **envp);

#endif