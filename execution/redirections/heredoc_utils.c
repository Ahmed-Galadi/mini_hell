#include "../../minishell.h"

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
