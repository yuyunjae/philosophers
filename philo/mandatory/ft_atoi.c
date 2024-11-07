/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:56:39 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/07 17:20:53 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static unsigned long	ft_strtol(char *str, int sign)
{
	unsigned long	i;
	unsigned long	ans;
	unsigned long	before;

	i = 0;
	ans = 0;
	before = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		ans = ans * 10 + str[i] - '0';
		if (before > ans && sign == -1)
			return (0);
		else if (before > ans && sign == 1)
			return (-1);
		else if (ans >= (long)9223372036854775807 && sign == 1)
			return (-1);
		else if (ans > (long)9223372036854775807 && sign == -1)
			return (0);
		before = ans;
		i++;
	}
	return (sign * ans);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ans;

	sign = 1;
	i = 0;
	ans = 0;
	while (str[i] && ft_isspace(str[i]))
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return ((int)ft_strtol((char *)(str + i), sign));
}
