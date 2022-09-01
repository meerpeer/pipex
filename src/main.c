/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:39:26 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/01 15:04:15 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <string.h>
#include <errno.h> 

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;

	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n", STDERR_FILENO);
		return (1);
	}
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		print_error(NULL, argv[1], TRUE);
	fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0 || access(argv[4], F_OK | W_OK) != 0)
		print_error(NULL, argv[4], TRUE);
	start_pipex(fd_in, fd_out, argv, envp);
	return (0);
}
