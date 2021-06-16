/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:51:40 by youjeon           #+#    #+#             */
/*   Updated: 2021/06/15 18:46:12 by youjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "get_next_line_bonus.h"

int		get_newline(char *backup)
{
	int	i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		static_split_newline(int newline_pos, char **line, char **backup)
{
	char	*tmp;
	int		length;

	length = ft_strlen(*backup);
	(*backup)[newline_pos] = 0;
	*line = ft_strdup(*backup);
	tmp = ft_substr(*backup, newline_pos + 1, length - newline_pos - 1);
	free(*backup);
	*backup = tmp;
	return (1);
}

int		value_return(char **backup, char **line, int read_num)
{
	int	newline_idx;

	if (read_num < 0)
		return (-1);
	if (*backup && (newline_idx = get_newline(*backup)) >= 0)
	{
		 get_newline(*backup);
		return (static_split_newline(newline_idx, line, backup));
	}
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*backup[OPEN_MAX];
	int				read_num;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	if (backup[fd] && get_newline(backup[fd]) >= 0)
		return (value_return(&backup[fd], line, 1));
	while ((read_num = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_num] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		if (get_newline(backup[fd]) >= 0)
			break ;
	}
	return (value_return(&backup[fd], line, read_num));
}
