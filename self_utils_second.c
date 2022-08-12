/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_utils_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:43:28 by ialgac            #+#    #+#             */
/*   Updated: 2022/07/08 03:02:58 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	leave_forks(t_person *self)
{
	pthread_mutex_lock(self->mutex_list[self->left_fork_index]);
	self->fork_list[self->left_fork_index] = 1;
	pthread_mutex_unlock(self->mutex_list[self->left_fork_index]);
	pthread_mutex_lock(self->mutex_list[self->right_fork_index]);
	self->fork_list[self->right_fork_index] = 1;
	pthread_mutex_unlock(self->mutex_list[self->right_fork_index]);
	return (0);
}

int	any_dead_body(t_person *self)
{
	usleep(100);
	pthread_mutex_lock(self->died);
	if (*(self->died_bool) == 1)
	{
		pthread_mutex_unlock(self->died);
		return (1);
	}
	pthread_mutex_unlock(self->died);
	return (0);
}

void	free_leaks(t_person **master, int fc)
{
	int	i;

	i = 0;
	free(master[0]->fork_list);
	while (i < fc)
	{
		pthread_mutex_destroy(master[0]->mutex_list[i]);
		free(master[0]->mutex_list[i]);
		i++;
	}
	free(master[0]->mutex_list);
	i = 0;
	while (i < fc)
	{
		free(master[i]);
		i++;
	}
}
