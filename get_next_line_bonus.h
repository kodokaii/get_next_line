/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/24 18:54:38 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	128
# endif

# define FD_MAX			128

# include <stdlib.h>
# include <unistd.h>

typedef enum e_bool
{
	FT_FALSE	= 0,
	FT_TRUE		= 1
}	t_bool;

typedef unsigned char	t_byte;

typedef struct s_char_save
{
	char	buf[BUFFER_SIZE];
	ssize_t	len;
}	t_char_save;

typedef struct s_char_buf
{
	char	*buf;
	ssize_t	len;
	t_bool	full;
}	t_char_buf;

char	*get_next_line(int fd);

void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memdup(const void *src, size_t n);

#endif
