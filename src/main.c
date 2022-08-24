/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:39:26 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/24 15:31:55 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;

	if (argc != 5)
		exit (1); // add correct error
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_in < 0 || fd_out < 0)
		return (EXIT_FAILURE);
	start_pipex(fd_in, fd_out, argv, envp);
	return (0);
}

//open trunc creat rdwr
//while (wait(NULL) > 0) for making sure all child processes are done