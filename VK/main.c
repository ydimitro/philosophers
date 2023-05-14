/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitro <ydimitro@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:11:09 by ydimitro          #+#    #+#             */
/*   Updated: 2023/05/14 23:22:30 by ydimitro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char** argv)
{
	t_input *input;
	t_all	*all;
	
	input = malloc(sizeof(t_input));
	if (input == NULL)
		return (1);
	if(input_valid(argc, argv, input) == 0)
		return (1);
	all = create_all(input);
	free(input);
	if(!all)
		return 0;
	set_the_table(all);
	start_threads(all);
	
	// printf("%p\n%p\n", all->philosophers->fork_right, all->philosophers->next->fork_left);
	destroy_all(all);
}
