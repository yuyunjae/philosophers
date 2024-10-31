/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:07:19 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/28 19:13:39 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	total;

	total = count * size;
	if (size != 0 && ((size_t)(total / size) != count))
		return (0);
	if (total == 0)
		str = (char *)malloc(total + 1);
	else
		str = (char *)malloc(total);
	if (!str)
		return (0);
	if (!total)
		memset(str, 0, 1);
	else
		memset(str, 0, total);
	return (str);
}
