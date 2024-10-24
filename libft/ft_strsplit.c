/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:12:29 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/24 14:42:55 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strwords(const char *s, const char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static int	ft_strlenword(const char *s, const char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			len++;
		if (s[i] == c && i != 0 && s[i - 1] != c)
			break ;
		i++;
	}
	return (len);
}

static int	ft_filltab(const char *s, char **tab, char c)
{
	int	i;
	int	word;

	word = ft_strwords(s, c);
	i = 0;
	while (word--)
	{
		while (*s == c && *s != '\0')
			s++;
		tab[i] = ft_strsub(
				(const char *)s,
				0,
				ft_strlenword((const char *)s, c)
				);
		if (tab[i] == NULL)
			return (0);
		s = s + ft_strlenword(s, c);
		i++;
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (s && c)
	{
		tab = (char **)malloc(
				sizeof(char *) * ((ft_strwords((const char *)s, c)) + 1)
				);
		if (!tab)
			return (NULL);
		if (ft_filltab(s, tab, c) == 0)
			return (NULL);
		return (tab);
	}
	return (NULL);
}
