/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gl_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:31:07 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 11:41:17 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	av_is_num(char *s)
{
	long	num;
	long	i;
	int		sign;

	num = 0;
	sign = 1;
	i = 0;
	if (!(s[i] >= '0' && s[i] <= '9'))
		return (0);
	while (s[i])
	{
		num = 10 * num + (s[i] - 48);
		if ((!(s[i] >= '0' && s[i] <= '9')) || num * sign > 2147483647
			|| num * sign < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoi(const char *s)
{
	long	num;
	long	i;
	int		sign;

	num = 0;
	sign = 1;
	i = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		num = 10 * num + (s[i++] - 48);
	num *= sign;
	return (num);
}

static void	verif_values(t_info *info)
{
	if (info->nb_phil > 200)
		exit_error(ERR_MANY_PHI, NULL, ERROR);
	if (info->nb_phil <= 0)
		exit_error(ERR_NO_PHI, NULL, ERROR);
	if (info->time_to_die < 60)
		exit_error(ERR_DIE, NULL, ERROR);
	if (info->time_to_eat < 60)
		exit_error(ERR_EAT, NULL, ERROR);
	if (info->time_to_sleep < 60)
		exit_error(ERR_SLEEP, NULL, ERROR);
	if (info->min_nb_meal == 0)
		exit_error(ERR_MEAL, NULL, ERROR);
}

void	init_gl_info(t_info *info, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!av_is_num(argv[i]))
			exit_error(ERR_AV, argv[i], ERROR);
	info->nb_phil = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->min_nb_meal = ft_atoi(argv[5]);
	else
		info->min_nb_meal = -1;
	verif_values(info);
}
