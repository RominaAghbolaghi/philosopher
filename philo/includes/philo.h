/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:33:31 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 11:41:56 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

# define ERROR 1
# define SUCCESS 0
# define ERR_ENV "Environnement error"
# define ERR_ARG "Invalid number of arguments"
# define ERR_AV "Argument is not valid"
# define ERR_MANY_PHI "More than 200 philos"
# define ERR_NO_PHI "At least we have to have 1 philosopher"
# define ERR_DIE "Time_to_die is too short"
# define ERR_EAT "Time_to_eat is too short"
# define ERR_SLEEP "Time_to_sleep is too short"
# define ERR_MEAL "There is no meal to eat"
# define ERR_MUT "Mutex's phase error"
# define ERR_PHI "Philo's phase error"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

typedef struct s_philo
{
	int				id;
	int				right_fork_index;
	int				left_fork_index;
	int				nb_meal;
	size_t			t_last_meal;
	pthread_t		t_id;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int				nb_phil;
	int				is_dead;
	int				is_full;
	int				min_nb_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			t_simulation;
	pthread_mutex_t	meal;
	pthread_mutex_t	console;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}				t_info;

extern char	**environ;

//		GET_INFO
void	init_gl_info(t_info *info, int argc, char **argv);

//		INIT
int		init_philo(t_info *info);

//		PHILO
void	*philo_action(void *arg);
void	philo_print(t_philo *philo, t_info *info, char *s);

// 		MUTEX
int		init_mutex(t_info *info);
int		destroy_mutex(t_info *info);

//		THREADS
int		create_philo(t_info *info, t_philo *philo);
int		destroy_philo(t_info *info);

//		ERROR
void	exit_error(char *error, char *file, int ret);

//		TIME
size_t	actual_time(void);

//		CHECK
void	check_full_death(t_info *info, t_philo *philo);

#endif
