/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/24 03:19:04 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	update_len(t_char_buf *oldbuf, t_char_buf *line)
{
	ssize_t	len;

	len = 0;
	while (len < oldbuf->len && oldbuf->buf[len] != '\n')
		len++;
	line->len += len;
	if (len != oldbuf->len)
	{
		line->len += 1;
		oldbuf->len = len + 1;
		oldbuf->full = FT_FALSE;
	}
}

static void	line_allocation(t_char_buf *line,
		t_char_buf *buf, t_char_buf *oldbuf)
{
	ssize_t	buf_rest;

	buf_rest = buf->len - oldbuf->len;
	if (line->len)
		line->buf = malloc(line->len + 1);
	if (line->buf)
	{
		line->buf[line->len] = '\0';
		ft_memcpy(buf->buf, oldbuf->buf + oldbuf->len, buf_rest);
		buf->len = buf_rest;
	}
}

static void	read_line(int fd, t_char_buf *line, t_char_buf *buf)
{
	t_char_buf	oldbuf;

	oldbuf.len = buf->len;
	oldbuf.buf = ft_memdup(buf->buf, buf->len);
	oldbuf.full = buf->full;
	update_len(&oldbuf, line);
	if (oldbuf.full == FT_TRUE)
	{
		buf->len = read(fd, buf->buf, BUFFER_SIZE);
		if (buf->len != BUFFER_SIZE)
			buf->full = FT_FALSE;
		if (0 <= buf->len)
			read_line(fd, line, buf);
	}
	else if (oldbuf.buf)
		line_allocation(line, buf, &oldbuf);
	if (oldbuf.buf && line->buf)
	{
		line->len -= oldbuf.len;
		ft_memcpy(line->buf + line->len, oldbuf.buf, oldbuf.len);
	}
	free(oldbuf.buf);
}

char	*get_next_line(int fd)
{
	static t_char_save	saves[FD_MAX] = {};
	t_char_buf			buf;
	t_char_buf			line;

	if (fd < 0 || FD_MAX <= fd)
		return (NULL);
	line.len = 0;
	line.buf = NULL;
	buf.len = saves[fd].len;
	buf.buf = saves[fd].buf;
	buf.full = FT_TRUE;
	read_line(fd, &line, &buf);
	saves[fd].len = buf.len * (0 <= buf.len);
	return (line.buf);
}
