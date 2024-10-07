/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:49:01 by lcluzan           #+#    #+#             */
/*   Updated: 2024/06/03 19:43:39 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	dstlen;
	size_t	scrlen;
	size_t	i;

	dstlen = ft_strlen(s1);
	scrlen = 0;
	while (s1[scrlen])
		scrlen++;
	i = 0;
	while (s2[i] && (i + scrlen + 1) < n)
	{
		s1[scrlen + i] = s2[i];
		i++;
	}
	if (i < n)
		s1[scrlen + i] = '\0';
	if (n <= dstlen)
		return (ft_strlen(s2) + n);
	else
		return (ft_strlen(s2) + dstlen);
}
