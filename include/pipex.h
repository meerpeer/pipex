/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:53:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/19 12:52:25 by mevan-de      ########   odam.nl         */
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

char	*get_cmd_path(char *cmd, char **envp);

#endif