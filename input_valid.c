/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:04:37 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/15 09:23:38 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_range(int to_compare, t_input *input)
{
	if (to_compare <= 0 || to_compare >= INT_MAX)
	{
		write(1, "value(s) out of range\n", 20);
		free(input);
		return (0);
	}
	return (1);
}

int	input_valid(int argc, char **argv, t_input *input)
{
	if (argc < 5 || argc > 6)
	{
		write(1, "Wrong amount of arguments\n", 27);
		free(input);
		return (0);
	}
	input->nbr_philos = ft_atoi(argv[1]);
	if (!valid_range(input->nbr_philos, input))
		return (0);
	input->time_die = ft_atoi(argv[2]);
	if (!valid_range(input->time_die, input))
		return (0);
	input->time_eat = ft_atoi(argv[3]);
	if (!valid_range(input->time_eat, input))
		return (0);
	input->time_sleep = ft_atoi(argv[4]);
	if (!valid_range(input->time_sleep, input))
		return (0);
	input->nbr_cycles = -1;
	if (argc == 5)
		return (1);
	input->nbr_cycles = ft_atoi(argv[5]);
	if (!valid_range(input->nbr_cycles, input))
		return (0);
	return (1);
}
