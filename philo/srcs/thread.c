/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:36:25 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 11:35:33 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_phil)
	{
		if (pthread_join(info->philo[i].t_id, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	create_philo(t_info *info, t_philo *philo)
{
	int		i;
	void	*copy_phi;

	i = 0;
	info->t_simulation = actual_time();
	while (i < info->nb_phil)
	{
		philo[i].t_last_meal = info->t_simulation;
		copy_phi = (void *)&(philo[i]);
		if (pthread_create(&philo[i].t_id, NULL, philo_action, copy_phi))
			return (1);
		i++;
	}
	check_full_death(info, info->philo);
	destroy_philo(info);
	return (0);
}
