/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:35:13 by plandolf          #+#    #+#             */
/*   Updated: 2023/05/23 10:05:25 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_resume(char *s)
{
	int		i;
	int		l;
	char	*resume;

	i = 0;
	l = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), NULL);
	resume = malloc((ft_strlen(s) - i + 1) * sizeof(char));
	if (!resume)
		return (NULL);
	i++;
	while (s[i])
		resume[l++] = s[i++];
	resume[l] = '\0';
	free(s);
	return (resume);
}

char	*ft_line(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		tmp = malloc((i + 2) * sizeof(char));
	else
		tmp = malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		tmp[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_read(int fd, char *s)
{
	char	*buff;
	int		b_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	b_read = 1;
	while (!ft_strchr_get_next(s, '\n') && b_read != 0)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(s);
			free(buff);
			return (NULL);
		}
		buff[b_read] = '\0';
		s = ft_strjoin_get_next(s, buff);
	}
	free(buff);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*s;
	static char	*index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	index = ft_read(fd, index);
	if (!index)
		return (free(index), NULL);
	s = ft_line(index);
	index = ft_resume(index);
	return (s);
}
