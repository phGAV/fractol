/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:51:38 by diona             #+#    #+#             */
/*   Updated: 2020/08/03 16:51:38 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <errno.h>

void	exit_err(char *err_msg)
{
	if (errno != 0)
		perror(err_msg);
	else
		ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
