/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:24:05 by rmohamma          #+#    #+#             */
/*   Updated: 2023/09/27 11:40:26 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		exit_error(ERR_ARG, NULL, ERROR);
	memset(&info, 0, sizeof(info));
	init_gl_info(&info, argc, argv);
	if (init_mutex(&info))
	{
		destroy_mutex(&info);
		exit_error(ERR_MUT, NULL, ERROR);
	}
	if (init_philo(&info))
	{
		destroy_mutex(&info);
		exit_error(ERR_PHI, NULL, ERROR);
	}
	create_philo(&info, info.philo);
	destroy_mutex(&info);
	free(info.philo);
	return (0);
}
