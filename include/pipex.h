/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:53:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/01 14:59:54 by mevan-de      ########   odam.nl         */
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
# include <fcntl.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}			t_bool;

char	*get_cmd_path(char *cmd, char **envp);
void	free_2d_array(char **array);
void	start_pipex(int fd_in, int fd_out, char **argv, char **envp);
void	print_error(char *str1, char *str2, t_bool should_perror);

#endif