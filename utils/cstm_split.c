
#include "../minishell.h"
#include <sys/unistd.h>

static bool	is_delimiter(char c, const char *delims)
{
	while (*delims)
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}

static int	count_words(const char *str, const char *delims)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*str)
	{
		if (!is_delimiter(*str, delims) && !in_word)
		{
			in_word = true;
			count++;
		}
		else if (is_delimiter(*str, delims))
			in_word = false;
		str++;
	}
	return (count);
}

static char	*copy_word(const char *start, const char *end)
{
	int		len;
	int		i;
	char	*word;

	len = end - start;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**cstm_split(const char *str, const char *delims)
{
	int		word_count;
	char	**result;
	int		i;
	const char	*start;

	if (!str || !delims)
		return (NULL);
	word_count = count_words(str, delims);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!is_delimiter(*str, delims))
		{
			start = str;
			while (*str && !is_delimiter(*str, delims))
				str++;
			result[i] = copy_word(start, str);
			if (!result[i])
				return (NULL);
			i++;
		}
		else
			str++;
	}
	result[i] = NULL;
	return (result);
}
