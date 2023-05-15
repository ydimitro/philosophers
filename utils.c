/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:26:09 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/14 22:23:04 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_len(long long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_llitoa(long long n)
{
	int		len;
	char	*str;

	len = ft_len(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (n)
	{
		str[len] = n % 10 + '0';
		len--;
		n = n / 10;
	}
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	if (!str)
		return (0);
	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * neg);
}
