/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:42:47 by ialgac            #+#    #+#             */
/*   Updated: 2022/07/08 03:55:33 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	reaper(t_person *self)
{
	unsigned int	now;

	now = the_counter(self->start_time);
	if (now - self->eated_at > self->time_for_die)
	{
		if (any_dead_body(self))
			return (1);
		pthread_mutex_lock(self->died);
		*(self->died_bool) = 1;
		pthread_mutex_unlock(self->died);
		printf("%u %d is died\n", the_counter(self->start_time), self->id);
		return (1);
	}
	return (0);
}

int	take_left_fork(t_person *self)
{
	pthread_mutex_lock(self->mutex_list[self->left_fork_index]);
	if (self->fork_list[self->left_fork_index] == 1)
	{
		self->fork_list[self->left_fork_index] = 0;
		printf("%u %d has taken a fork\n", \
		the_counter(self->start_time), self->id);
		pthread_mutex_unlock(self->mutex_list[self->left_fork_index]);
		return (1);
	}
	pthread_mutex_unlock(self->mutex_list[self->left_fork_index]);
	return (0);
}

int	take_right_fork(t_person *self)
{
	pthread_mutex_lock(self->mutex_list[self->right_fork_index]);
	if (self->fork_list[self->right_fork_index] == 1)
	{
		self->fork_list[self->right_fork_index] = 0;
		printf("%u %d has taken a fork\n", \
		the_counter(self->start_time), self->id);
		pthread_mutex_unlock(self->mutex_list[self->right_fork_index]);
		return (1);
	}
	pthread_mutex_unlock(self->mutex_list[self->right_fork_index]);
	return (0);
}

int	take_forks(t_person *self)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	usleep(100);
	while (!(left == 1 && right == 1))
	{
		if (reaper(self))
			return (1);
		if (!left)
			left = take_left_fork(self);
		if (!right)
			right = take_right_fork(self);
		usleep(100);
	}
	return ((right == 1 && left == 1) == 0);
}

int	time_sleep(t_person *self, unsigned int time, int sit)
{
	unsigned int	start_time;

	if (sit == 1)
		printf("%u %d is eating\n", the_counter(self->start_time), self->id);
	start_time = the_counter(self->start_time);
	while (the_counter(self->start_time) - start_time < time)
	{
		if (reaper(self))
			return (1);
		usleep(100);
	}
	return (0);
}
