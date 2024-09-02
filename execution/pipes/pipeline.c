/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/27 18:37:55 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data)
// {
//     int i;
//     int in, fd[2];
//     pid_t pid;

//     in = STDIN_FILENO;
//     i = 0;
//     while (i < num_commands)
//     {
//         pipe(fd);
//         pid = fork();

//         if (pid == 0)
//         {
//             // Child process
//             if (in != STDIN_FILENO)
//             {
//                 dup2(in, STDIN_FILENO);
//                 close(in);
//             }
//             if (i < num_commands - 1)
//             {
//                 dup2(fd[1], STDOUT_FILENO);
//             }
//             close(fd[0]);
//             close(fd[1]);

//             ft_execute_command(commands[i], return_value, data);
//             exit(EXIT_FAILURE);  // In case execute_command fails
//         }
//         else if (pid < 0)
//         {
//             perror("fork");
//             return 1;
//         }

//         // Parent process
//         close(fd[1]);
//         if (in != STDIN_FILENO)
//             close(in);
//         in = fd[0];
//         i++;
//     }

//     // Wait for all children
//     while (wait(NULL) > 0);

//     return 0;
// }

#include <sys/wait.h>
#include <errno.h>

int ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data)
{
    int i, in, fd[2];
    pid_t pid;
    int status;
    (void)data;

    in = STDIN_FILENO;
    for (i = 0; i < num_commands; i++)
    {
        if (i < num_commands - 1)
        {
            if (pipe(fd) == -1)
            {
                perror("pipe");
                return 1;
            }
        }

        pid = fork();
        if (pid == 0)
        {
            // Child process
            if (in != STDIN_FILENO)
            {
                dup2(in, STDIN_FILENO);
                close(in);
            }
            if (i < num_commands - 1)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
            }
            close(fd[1]);

            execvp(commands[i][0], commands[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("fork");
            return 1;
        }

        // Parent process
        if (in != STDIN_FILENO)
            close(in);
        if (i < num_commands - 1)
        {
            close(fd[1]);
            in = fd[0];
        }
    }

    // Wait for all children
    while (wait(&status) > 0)
        ;

    if (WIFEXITED(status))
        *return_value = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        *return_value = 128 + WTERMSIG(status);

    return 0;
}