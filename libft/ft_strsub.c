/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:12:29 by lcluzan           #+#    #+#             */
/*   Updated: 2024/05/28 00:13:08 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s)
	{
		i = 0;
		str = malloc(sizeof(char) * len + 1);
		if (str == NULL)
			return (NULL);
		while (i < len)
		{
			str[i] = s[i + start];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
