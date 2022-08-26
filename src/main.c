/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 13:39:26 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/08/26 11:32:08 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <string.h>
#include <errno.h> 

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n", STDERR_FILENO);
		return (1);
	}
	start_pipex(argv, envp);
	return (0);
}
