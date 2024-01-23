/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:10:53 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 12:22:30 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, t_info *info, char *s)
{
	pthread_mutex_lock(&info->console);
	pthread_mutex_lock(&info->death);
	if (!info->is_dead && !info->is_full)
	{
		printf("%ld ", actual_time() - info->t_simulation);
		printf(" %d ", philo->id + 1);
		printf("%s\n", s);
	}
	pthread_mutex_unlock(&info->death);
	pthread_mutex_unlock(&info->console);
}

static void	philo_eat(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->meal);
	philo_print(philo, info, EAT);
	philo->t_last_meal = actual_time();
	pthread_mutex_unlock(&info->meal);
	while (1)
	{
		pthread_mutex_lock(&info->death);
		if (info->is_dead || info->is_full)
		{
			pthread_mutex_unlock(&info->death);
			break ;
		}
		pthread_mutex_unlock(&info->death);
		if ((actual_time() - philo->t_last_meal) >= info->time_to_eat)
			break ;
		usleep(500);
	}
	pthread_mutex_lock(&info->meal);
	philo->nb_meal++;
	pthread_mutex_unlock(&info->meal);
}

static void	philo_sleep(t_philo *philo, t_info *info)
{
	size_t	sleep_start;

	philo_print(philo, info, SLEEP);
	sleep_start = actual_time();
	while (1)
	{
		pthread_mutex_lock(&info->death);
		if (info->is_dead || info->is_full)
		{
			pthread_mutex_unlock(&info->death);
			break ;
		}
		pthread_mutex_unlock(&info->death);
		if (actual_time() - sleep_start >= info->time_to_sleep)
			break ;
		usleep(500);
	}
}

static int	philo_has_forks(t_philo *philo, t_info *info)
{
	if (philo->id % 2)
		pthread_mutex_lock(&(info->forks[philo->right_fork_index]));
	else
		pthread_mutex_lock(&(info->forks[philo->left_fork_index]));
	philo_print(philo, info, FORK);
	if (info->nb_phil < 2)
	{
		pthread_mutex_unlock(&(info->forks[philo->right_fork_index]));
		return (1);
	}
	if (philo->id % 2)
		pthread_mutex_lock(&(info->forks[philo->left_fork_index]));
	else
		pthread_mutex_lock(&(info->forks[philo->right_fork_index]));
	philo_print(philo, info, FORK);
	philo_eat(philo, info);
	if (philo->id % 2)
		(pthread_mutex_unlock(&(info->forks[philo->right_fork_index])),
			pthread_mutex_unlock(&(info->forks[philo->left_fork_index])));
	else
		(pthread_mutex_unlock(&(info->forks[philo->left_fork_index])),
			pthread_mutex_unlock(&(info->forks[philo->right_fork_index])));
	return (0);
}

void	*philo_action(void *arg)
{
	t_philo			*philo;
	t_info			*info;

	philo = (t_philo *)arg;
	info = philo->info;
	if (philo->id % 2)
		usleep(10000);
	while (1)
	{
		if (philo_has_forks(philo, info))
			break ;
		philo_sleep(philo, info);
		philo_print(philo, info, THINK);
		pthread_mutex_lock(&info->death);
		if (info->is_dead || info->is_full)
		{
			pthread_mutex_unlock(&info->death);
			break ;
		}
		pthread_mutex_unlock(&info->death);
		usleep(100);
	}
	return (NULL);
}
