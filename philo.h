/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:11:47 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/15 10:28:49 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_input
{
	int	nbr_philos;
	int	time_eat;
	int	time_sleep;
	int	time_die;
	int	nbr_cycles;
}	t_input;

typedef struct s_bool_mutex
{
	pthread_mutex_t	mutex;
	int				value;
}	t_mutex;

struct s_philo
{
	t_mutex			*fork_left;
	t_mutex			*fork_right;
	t_mutex			*a_death;
	t_mutex			*is_printing;
	t_mutex			*cycles_fullfilled;
	bool			is_alive;
	int				cycles_left;
	int				pid;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				nbr_philos;
	long long		last_meal;
	long long		start_time;
	t_philo			*next;
}	;

typedef struct s_all
{
	t_mutex		*mutex_death;
	t_mutex		*mutex_print;
	t_mutex		**forks;
	t_mutex		*mutex_cycles;
	t_philo		*philosophers;
	int			nbr_philosophers;
	int			nbr_cycles;
}	t_all;

char		*ft_llitoa(long long n);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);

long long	timestamp_in_ms(void);

void		print_time(long long start_time, long long current_time);
void		print_nbr(int value);
void		print_activity(t_philo *philosopher,
				long long current_time, char *message);
void		print_death(t_philo *philosopher, long long current_time);

int			input_valid(int argc, char **argv, t_input *input);

void		*routine(void *philo);
bool		dead_or_alive(t_philo *philosopher);
void		set_the_table(t_all *all);
void		pick_up_forks(t_philo *philosopher);
void		put_down_forks(t_philo *philosopher);

t_philo		*create_philo(t_input *input, t_mutex *death, t_mutex *print);
t_philo		*create_all_philos(t_input *input,
				t_mutex *death, t_mutex *print, t_mutex *cycles);
void		destroy_all_philos(t_philo *to_destroy);
void		destroy_philo(t_philo *to_destroy);

t_mutex		*create_mutex(void);
void		destroy_mutex(t_mutex *mutex);
t_mutex		**create_forks(int nbr_forks);
void		destroy_forks(t_mutex **forks);
t_all		*create_all(t_input *input);
void		destroy_all(t_all *to_destroy);

void		start_threads(t_all *all, int i, long long time,
				t_philo *philosopher);
bool		wait_for_mutex(t_mutex *mutex, t_mutex *death);

#endif
