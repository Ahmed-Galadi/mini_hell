#include "../../minishell.h"
#include <stdio.h>

int	count_docs(t_opp *op)
{
	int	count;

	count = 0;
	while (op)
	{
		if (op->operator == HERE_DOC
			|| op->operator == HERE_DOC_EXP)
			count++;
		op = op->next;
	}
	return (count);
}

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
		count += count_docs(curr->operator);
		curr = curr->next;
	}
	return (count);
}

char	**fill_heredoc_files(int count)
{
	int		i;
	char	**new;

	new = gc_malloc(sizeof(char *) * (count + 1), LOCAL);
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new[i] = ft_strjoin("/tmp/.tmpheredocfile", ft_itoa(i), LOCAL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ftputstr_fd(int fd, char *s)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
			s++;
	}
}

void	open_heredoc(char **files, t_opp *op, int *count, t_shell *data)
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
		if (!str || ft_strcmp(str, op->arg) == 0)
			return ;
		if (op->operator == HERE_DOC_EXP)
			expand(&str, data->env, data->exit_status);
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
	data->heredoc_count = count;
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
			if (op->operator == HERE_DOC
				|| op->operator == HERE_DOC_EXP)
				open_heredoc(data->heredoc_files, op, &count, data);
			op = op->next;
		}
		curr = curr->next;
	}
}

int	ft_read_from_heredoc(t_shell *data)
{
	int	new;
	int	count;

	if (data->heredoc_index >= data->heredoc_count)
		return (0);
	new = open(data->heredoc_files[data->heredoc_index], O_RDONLY);
	if (new < 0)
		return (perror("open heredeoc failed!"), 1);
	unlink(data->heredoc_files[data->heredoc_index]);
	data->heredoc_index++;
	if (dup2(new, STDIN_FILENO) < 0)
		return (perror("dup failed!"), 1);
	close(new);
	return (0);
}
