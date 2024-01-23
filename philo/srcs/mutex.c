/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:30:09 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 11:41:38 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_info *info)
{
	int	fork_indx;

	if (pthread_mutex_init(&info->meal, NULL))
		return (ERROR);
	if (pthread_mutex_init(&info->console, NULL))
		return (ERROR);
	if (pthread_mutex_init(&info->death, NULL))
		return (ERROR);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_phil);
	if (!info->forks)
		return (ERROR);
	fork_indx = 0;
	while (fork_indx < info->nb_phil)
	{
		if (pthread_mutex_init(&info->forks[fork_indx], NULL))
			return (ERROR);
		fork_indx++;
	}
	return (SUCCESS);
}

int	destroy_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_phil)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->death);
	pthread_mutex_destroy(&info->console);
	pthread_mutex_destroy(&info->meal);
	if (info->forks)
		free(info->forks);
	return (0);
}
