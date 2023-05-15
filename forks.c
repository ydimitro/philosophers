/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:44:22 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/15 09:45:01 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_fork(t_mutex *fork, bool *check, t_philo *philosopher)
{
	pthread_mutex_lock(&(fork->mutex));
	if (fork->value == false)
	{
		check = true;
		fork->value = true;
		print_activity(philosopher, timestamp_in_ms(), " has taken a fork");
	}
	pthread_mutex_unlock(&(fork->mutex));
}

void	pick_up_forks(t_philo *philosopher)
{
	bool	lcheck;
	bool	rcheck;

	lcheck = false;
	rcheck = false;
	while ((lcheck == false || rcheck == false))
	{
		check_fork(philosopher->fork_left, &lcheck, philosopher);
		check_fork(philosopher->fork_right, &rcheck, philosopher);
		if (dead_or_alive(philosopher) == false)
			break ;
	}
}

void	put_down_forks(t_philo *philosopher)
{
	pthread_mutex_lock(&(philosopher->fork_left->mutex));
	philosopher->fork_left->value = false;
	pthread_mutex_unlock(&(philosopher->fork_left->mutex));
	pthread_mutex_lock(&(philosopher->fork_right->mutex));
	philosopher->fork_right->value = false;
	pthread_mutex_unlock(&(philosopher->fork_right->mutex));
}
