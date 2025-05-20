/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luevange <luevange@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:10:50 by luevange          #+#    #+#             */
/*   Updated: 2025/05/20 22:02:57 by luevange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_child1(int *fd, int infile, char *cmd, char **envp)
{
    if (dup2(infile, STDIN_FILENO) == -1)
    {
        close(infile);
        close(fd[0]);
        close(fd[1]);
        exit(1);
    }
    close(infile);
    close(fd[0]);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
    {
        close(fd[1]);
        exit(1);
    }
    close(fd[1]);
    execute_cmd(cmd, envp);
}

void handle_child2(int *fd, int outfile, char *cmd, char **envp)
{
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
    {
        close(fd[0]);
        close(outfile);
        exit(1);
    }
    close(fd[0]);
    if (dup2(outfile, STDOUT_FILENO) == -1)
    {
        close(outfile);
        exit(1);
    }
    close(outfile);
    execute_cmd(cmd, envp);
}

void execute_cmd(char *cmd, char **envp)
{
    char **cmd_args;
    char *path;
    char *original_path;

    cmd_args = ft_split(cmd, ' ');
    if (!cmd_args)
        exit(1);
    original_path = find_path(cmd_args[0], envp);
    path = original_path;
    if (execve(path, cmd_args, envp) == -1)
    {
        write(2, "Command not found: ", 18);
        write(2, cmd_args[0], ft_strlen(cmd_args[0]));
        write(2, "\n", 1);
        free(path);
        ft_free_matrix(cmd_args);
        exit(127);
    }
}

void create_processes(t_pipex *data)
{
    pid_t pid1;
    pid_t pid2;

    pid1 = fork();
    if (pid1 == -1)
        error_handler("Fork");
    if (pid1 == 0)
        handle_child1(data->fd, data->infile, data->argv[2], data->envp);
    pid2 = fork();
    if (pid2 == -1)
        error_handler("Fork");
    if (pid2 == 0)
        handle_child2(data->fd, data->outfile, data->argv[3], data->envp);
    close(data->fd[0]);
    close(data->fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex data;

    check_args(argc);
    data.argv = argv;
    data.envp = envp;
    create_pipe(data.fd);
    setup_files(&data.infile, &data.outfile, argv);
    create_processes(&data);
    close(data.infile);
    close(data.outfile);
    return (0);
}