/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:21:04 by hunpark           #+#    #+#             */
/*   Updated: 2023/01/17 15:21:04 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"

void	error_handle(int a, char *str);
void	ft_free(char **path, char *tmp, char *cmd_path, int mode);
char	*ft_find_path(char *cmd, char **env);
char	**ft_env_path(char **env);
void	ft_run(char *cmd, char **env, int mode);
void	child_process(char **av, char **env, int *fd);
void	parents_process(char **av, char **env, int *fd);

#endif
