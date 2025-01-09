/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:07:51 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/07 04:28:45 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static char	*gnl_read(int fd, char *stack)
{
	ssize_t	bread;
	char	*buffer;

	bread = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bread != 0 && !sl_strchr(stack, '\n'))
	{
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread == -1)
			return (free(buffer), NULL);
		buffer[bread] = '\0';
		stack = sl_strjoin(stack, buffer);
	}
	return (free(buffer), stack);
}

static char	*before_nl(char *stack)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!stack[0])
		return (NULL);
	while (stack[i] && stack[i] != '\n')
		i++;
	str = malloc((sizeof(char) * i) + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (stack[i] && stack[i] != '\n')
	{
		str[i] = stack[i];
		i++;
	}
	if (stack[i] == '\n')
	{
		str[i] = stack[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*after_nl(char *stack)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stack[i] && stack[i] != '\n')
		i++;
	if (!stack[i])
		return (free(stack), NULL);
	str = (char *)malloc(sizeof(char) * ((sl_strlen(stack) - i) + 1));
	if (!str)
		return (NULL);
	i++;
	while (stack[i])
		str[j++] = stack[i++];
	str[j] = '\0';
	return (free(stack), str);
}

char	*gnl(int fd)
{
	static char	*stack;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stack), stack = NULL, NULL);
	stack = gnl_read(fd, stack);
	if (!stack)
		return (NULL);
	line = before_nl(stack);
	stack = after_nl(stack);
	if (stack)
	{
		free(stack);
		stack = NULL;
	}
	return (line);
}
