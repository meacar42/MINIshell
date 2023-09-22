/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meacar <meacar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:34:18 by meacar            #+#    #+#             */
/*   Updated: 2023/07/18 15:34:19 by meacar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordslength(char const *s, char c)
{
	size_t	letter;

	letter = 0;
	while (s[letter] && s[letter] != c)
		letter++;
	return (letter);
}

static size_t	words(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		if (*s != c && (s[1] == '\0' || s[1] == c))
			len++;
		s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s)
		return (NULL);
	len = words(s, c);
	new = malloc(sizeof(char *) * len + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (*s == c && *s != 0)
			s++;
		new[i] = malloc(sizeof(char) * wordslength(s, c) + 1);
		j = 0;
		while (*s != c && *s != 0)
			new[i][j++] = *s++;
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
	return (new);
}
