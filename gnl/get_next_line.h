/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:54:44 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/19 15:19:35 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "../minirt.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4

# endif

char	*get_next_line(int fd);
int		gnl_strlen(char *s);
char	*check_buffer(char *buffer);
char	*gnl_strchr(char *s, char c);
char	*gnl_substr(char *s, int start, int len);
char	*gnl_strjoin(char *r, char *buffer);
char	*fill_s(char *str);
int		back_slash_len(char *buffer);

#endif
