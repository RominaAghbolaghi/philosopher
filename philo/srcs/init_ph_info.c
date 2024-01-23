/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ph_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:15:20 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 09:48:47 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->nb_phil);
	if (!info->philo)
		return (ERROR);
	while (i < info->nb_phil)
	{
		info->philo[i].id = i;
		info->philo[i].right_fork_index = i;
		info->philo[i].left_fork_index = (i + 1) % info->nb_phil;
		info->philo[i].info = info;
		info->philo[i].nb_meal = 0;
		info->philo[i].t_last_meal = 0;
		i++;
	}
	return (SUCCESS);
}
