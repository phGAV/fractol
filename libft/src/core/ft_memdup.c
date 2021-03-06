/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourgot <ourgot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 02:52:42 by ourgot            #+#    #+#             */
/*   Updated: 2019/11/27 09:42:18 by ourgot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

void	*ft_memdup(const void *s, size_t n)
{
	void *dst;

	if ((dst = ft_malloc(n)))
		ft_memcpy(dst, s, n);
	return (dst);
}
