/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:35:03 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 11:35:33 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	actual_time(void)
{
	struct timeval	current_time;
	size_t			milli_s;

	if (gettimeofday(&current_time, NULL) < 0)
		return (0);
	milli_s = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (milli_s);
}

void	check_full(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->meal);
	while (i < info->nb_phil)
	{
		if (philo[i].nb_meal < info->min_nb_meal)
		{
			pthread_mutex_unlock(&info->meal);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&info->meal);
	pthread_mutex_lock(&info->death);
	info->is_full = 1;
	pthread_mutex_unlock(&info->death);
}

void	check_full_death(t_info *info, t_philo *philo)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&info->death);
		if (info->is_dead || info->is_full)
		{
			pthread_mutex_unlock(&info->death);
			break ;
		}
		pthread_mutex_unlock(&info->death);
		if (info->min_nb_meal >= 0)
			check_full(info, philo);
		i = -1;
		while (++i < info->nb_phil)
		{
			pthread_mutex_lock(&info->meal);
			if ((actual_time() - philo[i].t_last_meal) > info->time_to_die)
				(philo_print(philo, info, DEAD),
					pthread_mutex_lock(&info->death), info->is_dead = 1,
					pthread_mutex_unlock(&info->death));
			pthread_mutex_unlock(&info->meal);
		}
		usleep(100);
	}
}
