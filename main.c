/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:42:24 by ialgac            #+#    #+#             */
/*   Updated: 2022/07/08 04:17:02 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	*threads(void *arg)
{
	t_person	*self;

	self = (t_person *)arg;
	self->eated_at = 0;
	while (self->count_of_pasta != 0)
	{
		if (take_forks(self))
			return (NULL);
		if (any_dead_body(self))
			return (NULL);
		self->eated_at = the_counter(self->start_time);
		if (time_sleep(self, self->time_for_eat, 1))
			return (NULL);
		leave_forks(self);
		if (any_dead_body(self))
			return (NULL);
		printf("%u %d is sleeping\n", the_counter(self->start_time), self->id);
		if (time_sleep(self, self->time_for_slp, 2))
			return (NULL);
		if (any_dead_body(self))
			return (NULL);
		printf("%u %d is thinking\n", the_counter(self->start_time), self->id);
		self->count_of_pasta -= (self->count_of_pasta != -1);
	}
	return (NULL);
}

void	start_playing(t_person **master, int fc)
{
	int				i;
	unsigned int	the_time;

	the_time = time_in_ml();
	i = 0;
	while (i < fc)
	{
		master[i]->start_time = the_time;
		pthread_create(&(master[i]->tid), NULL, &threads, (void *)(master[i]));
		i = i + 2;
	}
	usleep(300);
	i = 1;
	while (i < fc)
	{
		master[i]->start_time = the_time;
		pthread_create(&(master[i]->tid), NULL, &threads, (void *)(master[i]));
		i = i + 2;
	}
	i = 0;
	while (i < fc)
	{
		pthread_join((master[i])->tid, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_person		**bodies;
	pthread_mutex_t	*died;
	int				dead_bool;

	dead_bool = 0;
	if (argc == 5 || argc == 6)
	{
		if (check_argument(argc, argv))
		{
			died = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
			pthread_mutex_init(died, NULL);
			bodies = crt_bodies(argv, &died, &dead_bool);
			start_playing(bodies, ft_atoi(argv[1]));
			pthread_mutex_destroy(died);
			free(died);
			free_leaks(bodies, ft_atoi(argv[1]));
			free(bodies);
		}
	}
	return (0);
}
