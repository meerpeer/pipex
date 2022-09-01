/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 14:47:29 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/01 15:16:53 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_error(char *str, char *error_str, t_bool should_perror)
{
	if (ft_putstr_fd("pipex: ", STDERR_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (ft_putstr_fd(str, STDERR_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (should_perror)
		perror(error_str);
	else if (ft_putstr_fd(error_str, STDERR_FILENO) == -1)
		exit(EXIT_FAILURE);
}
