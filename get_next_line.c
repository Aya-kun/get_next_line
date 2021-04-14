#include "get_next_line.h"

void	eof(char **text, char **line)
{
	int	i;

	i = 0;
	*line = ft_strdup(text[i]);
	free(text[i]);
	text[i] = 0;
}

int	sline(char **text, char **line)
{
	char	*tmp;
	int	i;

	i = 0;
	while ((*text)[i] != '\0' && (*text)[i] != '\n')
		i++;
	if (ft_strchr(*text, '\n'))
	{
		*line = ft_substr(*text, 0, i);
		tmp = ft_strdup(ft_strchr(*text, '\n') + 1);
		free(*text);
		*text = tmp;
		return (1);
	}
	else
		return (0);
}

void	stext(char **text, char *buf)
{
	char	*tmp;

	tmp = 0;
	if (!(*text))
		*text = ft_strdup(buf);
	else
	{
		tmp = *text;
		*text = ft_strjoin(tmp, buf);
		free(tmp);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*text[100];
	ssize_t		ret;
	char		buf[BUFFER_SIZE + 1];

	if (read(fd, 0, 0) == -1 || fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (text[fd] && sline(&text[fd], line))
		return (1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		stext(&text[fd], buf);
		if (sline(&text[fd], line))
			return (1);
		ret = read(fd, buf, BUFFER_SIZE);
	}
	if (text[fd] && !ft_strchr(text[fd], '\n'))
	{
		eof(&text[fd], line);
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

/*int		main(int ac, char **av)
{
	int		fd;
	int		ret_value;
	char	*line;

	line = NULL;
	fd = open(av[1], O_RDONLY);
	if (ac > 1)
	if (fd == -1)
		return (-1);
	ret_value = 1;
	while (ret_value == 1)
	{
		ret_value = get_next_line(fd, &line);
		printf("%d |>>| %s\n", ret_value, line);
	}
	close(fd);
	return (0);
}*/
