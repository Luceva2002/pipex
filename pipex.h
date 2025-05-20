/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luevange <luevange@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:11:02 by luevange          #+#    #+#             */
/*   Updated: 2025/05/20 17:50:20 by luevange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	**argv;
	char	**envp;
}			t_pipex;

char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlen(const char *s1);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_free_matrix(char **matrix);
void		error_handler(char *str);
char		*find_path(char *cmd, char **envp);
void		execute_cmd(char *cmd, char **envp);
void		check_args(int argc);
void		setup_files(int *infile, int *outfile, char **argv);
void		handle_child1(int *fd, int infile, char *cmd, char **envp);
void		handle_child2(int *fd, int outfile, char *cmd, char **envp);
void		create_pipe(int *fd);
void		create_processes(t_pipex *data);

#endif