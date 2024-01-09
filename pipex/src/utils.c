/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:28:45 by hunpark           #+#    #+#             */
/*   Updated: 2023/01/30 15:04:17 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error_handle(int a, char *str)
{
	if (a == 0)
	{
		perror(str);
		exit(1);
	}
	if (a == 2 || a == 3)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		if (a == 3)
			exit(127);
		exit(1);
	}
}

void	ft_free(char **path, char *tmp, char *cmd_path, int mode)
{
	int	i;

	if (mode == 1)
	{
		i = -1;
		while (path[++i])
			free(path[i]);
		free(path);
		free(tmp);
	}
	if (mode == 2)
	{
		i = -1;
		while (path[++i])
			free(path[i]);
		free(path);
		if (!tmp || !cmd_path)
			error_handle(0, NULL);
	}
	if (mode == 3)
	{
		free(tmp);
		free(cmd_path);
	}
}

char	**ft_env_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
			path = ft_split(env[i] + 5, ':');
	}
	return (path);
}

char	*ft_find_path(char *cmd, char **env)
{
	char	**path;
	char	*tmp;
	char	*cmd_path;
	int		i;

	path = ft_env_path(env);
	if (!path)
		error_handle(0, NULL);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		if (!tmp || !cmd_path)
			ft_free(path, tmp, cmd_path, 2);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free(path, tmp, cmd_path, 1);
			return (cmd_path);
		}
		ft_free(path, tmp, cmd_path, 3);
	}
	ft_free(path, tmp, cmd_path, 2);
	return (NULL);
}
