/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:02:53 by danz              #+#    #+#             */
/*   Updated: 2026/01/27 20:40:09 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src [i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	size_t	dlen;

	i = 0;
	j = 0;
	slen = ft_strlen(src);
	dlen = ft_strlen(dest);
	if (size == 0)
		return (slen + size);
	while (dest[i] != '\0')
		i++;
	while (i < size - 1 && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if (dlen < size)
		return (dlen + slen);
	return (size + slen);
}

static void	ft_rev_str(char *str, int size)
{
	int	i;
	int	hold;

	i = 0;
	while (i < size / 2)
	{
		hold = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = hold;
		hold = 0;
		i++;
	}
}

static void	ft_itoa_mod(char *ret, long nb, int size)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (nb < 0)
	{
		ret[size] = '-';
		nb *= -1;
		sign = 1;
	}
	while (i < size)
	{
		ret[i] = nb % 10 + 48;
		if (nb > 0)
			nb = nb / 10;
		i++;
	}
	ft_rev_str(ret, i + sign);
	ret[i + sign] = 0;
}

char	*ft_itoa(int n)
{
	int		i;
	char	*ret;
	long	nb;
	int		sign;

	i = 1;
	sign = 0;
	nb = n;
	if (n < 0)
	{
		nb *= -1;
		sign++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		i++;
	}
	nb = n;
	ret = malloc((i + 1 + sign) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_itoa_mod(ret, nb, i);
	return (ret);
}
