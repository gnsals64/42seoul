/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:16:35 by hunpark           #+#    #+#             */
/*   Updated: 2023/01/30 15:09:11 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_run(char *cmd, char **env, int mode)
{
	char	*cmd_path;
	char	**cmd_data;
	int		i;

	i = -1;
	cmd_data = ft_split(cmd, ' ');
	if (!cmd_data)
		error_handle(0, NULL);
	if (ft_strncmp(cmd, "/", 1) == 0)
		cmd_path = ft_strdup(cmd);
	else
		cmd_path = ft_find_path(cmd_data[0], env);
	if (!cmd_path && mode == 1)
		error_handle(2, cmd_data[0]);
	if (!cmd_path && mode == 2)
		error_handle(3, cmd_data[0]);
	if (execve(cmd_path, cmd_data, env) == -1)
	{
		while (cmd_data[++i] != NULL)
			free(cmd_data[i]);
		free(cmd_path);
		free(cmd_data);
	}
}

void	child_process(char **av, char **env, int *fd)
{
	int	input_fd;

	input_fd = open(av[1], O_RDONLY);
	if (input_fd == -1)
		return (error_handle(0, av[1]));
	close(fd[0]);
	dup2(input_fd, 0);
	dup2(fd[1], 1);
	ft_run(av[2], env, 1);
}

void	parents_process(char **av, char **env, int *fd)
{
	int	output_fd;

	output_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (output_fd == -1)
		return (error_handle(0, NULL));
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(output_fd, 1);
	ft_run(av[3], env, 2);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			error_handle(0, NULL);
		pid = fork();
		if (pid == -1)
			error_handle(0, NULL);
		else if (pid == 0)
			child_process(av, env, fd);
		waitpid(pid, NULL, WNOHANG);
		parents_process(av, env, fd);
	}
	else
	{
		write(1, "invalid argument\n", 17);
		write(1, "ex)./pipex <infile> <cmd1> <cmd2> <outfile>\n", 44);
		exit(1);
	}
}
