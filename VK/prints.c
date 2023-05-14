/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:04:47 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/14 23:48:15 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	print_death(t_philo* philosopher, long long current_time)
{
	pthread_mutex_lock(&(philosopher->is_printing->mutex));
	print_time(philosopher->start_time, current_time);
	write(1, " ", 1);
	print_nbr(philosopher->pid);
	write(1, " died", 5);
	write(1, "\n", 1);
	pthread_mutex_unlock(&(philosopher->is_printing->mutex));
	//tell the others that you are done printing
}

void print_activity(t_philo* philosopher, long long current_time, char* message)
{	
	bool check_death;

	pthread_mutex_lock(&(philosopher->is_printing->mutex));
	pthread_mutex_lock(&(philosopher->a_death->mutex));
	check_death = philosopher->a_death->value;
	pthread_mutex_unlock(&(philosopher->a_death->mutex));
	if (!check_death)
	{
		print_time(philosopher->start_time, current_time);
		write(1, " ", 1);
		print_nbr(philosopher->pid);
		write(1, message, ft_strlen(message));
		write(1, "\n", 1);
	}
	//tell the others that you are done printing
	pthread_mutex_unlock(&(philosopher->is_printing->mutex));
}

void print_nbr(int value)
{
	char* to_print;
	
	to_print = ft_llitoa((long long)value);
	write(1, to_print, ft_strlen(to_print));
	free(to_print);
}

void print_time(long long start_time, long long current_time)
{
	current_time = current_time - start_time;
	char* time = ft_llitoa(current_time);
	write(1, time, ft_strlen(time));
	free(time);
}
