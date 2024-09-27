/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/27 12:14:53 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <readline/readline.h>
#include <sys/fcntl.h>
#include <unistd.h>

void update_prev_pipe(int *prev_pipe, int *curr_pipe, int is_last)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (is_last)
	{
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
}

int set_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}



// int ft_execute_pipeline(char ***commands, int num_commands, t_shell *data)
// {
// 	int prev_pipe[2] = {-1, -1};
// 	int curr_pipe[2] = {-1, -1};
// 	int heredoc_pipe[2] = {-1, -1};
// 	pid_t pid;
// 	int status;
// 	int i;
// 	t_com	*com;
// 	t_opp	*curr_op;


// 	i = 0;
// 	while (i < num_commands)
// 	{
// 		com = &data->command[i];
// 		curr_op = com->operator;

// 		if (i < num_commands - 1)
// 			if (pipe(curr_pipe) == -1)
// 				return (perror("pipe"), 1);
// 		ft_open_heredoc(curr_op, heredoc_pipe);
// 		pid = fork();
// 		if (pid < 0)
// 			return (perror("fork"), 1);
// 		else if (pid == 0)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			signal(SIGQUIT, SIG_DFL);
// 			redirect_to_pipe_fds(data, (i > 0) ? prev_pipe : NULL, (i < num_commands - 1) ? curr_pipe : NULL, i, num_commands, is_builtin(data->command->command[0]));
// 			if (is_builtin(data->command->command[0]))
// 				ft_execute_builtin(data);
// 			else
// 				execute_command(data, commands[i]);
// 			exit(0);
// 		}
// 		update_prev_pipe(prev_pipe, curr_pipe, i < num_commands - 1);
// 		data->command = data->command->next;
// 		i++;
// 	}
// 	update_prev_pipe(prev_pipe, curr_pipe, 0); /* Close prev_pipe fds */
// 	while (wait(&status) > 0)
// 		;
// 	return (set_exit_status(status));
// }

int	heredoc_count(t_com *command)
{
	int		count;
	t_com	*curr;
	t_opp	*op;

	curr = command;
	count = 0;
	while (curr)
	{
		op = curr->operator;
		while (op)
		{
			if (op->operator == HERE_DOC)
				count++;
			op = op->next;
		}
		curr = curr->next;
	}
	return (count);
}

char	**fill_heredoc_files(int count)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * count);
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new[i] = ft_strjoin("/tmp/.tmpheredocfile", ft_itoa(i));
		i++;
	}
	new[i] = NULL;
	return (new);
}

static void	ftputstr_fd(int fd, char *s)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
			s++;
	}
}

void	open_heredoc(char **files, t_opp *op, int *count)
{
	char	*str;
	int		fd;

	fd = open(files[*count], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("open"));
	(*count)++;
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, op->arg))
			return ;
		ftputstr_fd(fd, str);
		write(fd, "\n", 1);
	}
	close(fd);
}

void	ft_open_heredoc(t_shell *data)
{
	int		count;
	t_com	*curr;
	t_opp	*op;
	char	*line;

	count = heredoc_count(data->command);
	if (count > 16)
	{
		printf("Error: maximum here-document count exceeded\n");
		exit(2);
	}
	data->heredoc_files = fill_heredoc_files(count);
	curr = data->command;
	count = 0;
	while (curr)
	{
		op = curr->operator;
		while (op)
		{
			if (op->operator == HERE_DOC)
				open_heredoc(data->heredoc_files, op, &count);
			op = op->next;
		}
		curr = curr->next;
	}
}

int ft_execute_pipeline(char ***commands, int num_commands, t_shell *data)
{
    int prev_pipe[2] = {-1, -1};
    int curr_pipe[2] = {-1, -1};
    pid_t pid;
    int status;
    int i;
    t_com *com;
    t_opp *curr_op;

    i = 0;
    ft_open_heredoc(data);
    while (i < num_commands)
    {
        com = &data->command[i];
        curr_op = com->operator;

        if (i < num_commands - 1)
            if (pipe(curr_pipe) == -1)
                return (perror("pipe"), 1);


        pid = fork();
        if (pid < 0)
            return (perror("fork"), 1);
        else if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            redirect_to_pipe_fds(data, (i > 0) ? prev_pipe : NULL, (i < num_commands - 1) ? curr_pipe : NULL, i, num_commands, is_builtin(data->command->command[0]));
            if (is_builtin(data->command->command[0]))
                ft_execute_builtin(data);
            else
                execute_command(data, commands[i]);
            exit(0);
        }
        update_prev_pipe(prev_pipe, curr_pipe, i < num_commands - 1);
        data->command = data->command->next;
        i++;
    }

    update_prev_pipe(prev_pipe, curr_pipe, 0);
    while (wait(&status) > 0)
        ;
    return (set_exit_status(status));
}
