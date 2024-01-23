/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:28:01 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 09:50:14 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static int	putstr_error(char *error)
{
	write(2, error, ft_strlen(error));
	return (ERROR);
}

void	exit_error(char *error, char *file, int ret)
{
	putstr_error(error);
	if (file)
	{
		putstr_error(": ");
		putstr_error(file);
	}
	putstr_error("\n");
	if (!ret)
		return ;
	exit (ret);
}
