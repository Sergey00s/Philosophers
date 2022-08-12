/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:42:38 by ialgac            #+#    #+#             */
/*   Updated: 2022/07/08 02:42:40 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

int	*put_forks(int pc)
{
	int	*rtn;
	int	i;

	rtn = (int *)malloc(sizeof(int) * pc);
	i = 0;
	while (i < pc)
	{
		rtn[i] = 1;
		i++;
	}
	return (rtn);
}

pthread_mutex_t	**put_mutexs(int pc)
{
	int				i;
	pthread_mutex_t	**rtn;

	rtn = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * pc);
	i = 0;
	while (i < pc)
	{
		rtn[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(rtn[i], NULL);
		i++;
	}
	return (rtn);
}

void	give_my_forks(t_person *body, int i, int fc)
{
	fc--;
	body->right_fork_index = i;
	if (i == 0)
		body->left_fork_index = fc;
	else
		body->left_fork_index = i - 1;
}

void	put_others(t_person *per, char **argv)
{
	per->time_for_die = ft_atoi(argv[2]);
	per->time_for_eat = ft_atoi(argv[3]);
	per->time_for_slp = ft_atoi(argv[4]);
}

void	put_bodies(t_person **bodies, char **argv, \
pthread_mutex_t **mute, int *died_bool)
{
	pthread_mutex_t	**rn;
	int				i;
	int				*rr;

	rr = put_forks(ft_atoi(argv[1]));
	rn = put_mutexs(ft_atoi(argv[1]));
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		(bodies[i]) = (t_person *)malloc(sizeof(t_person));
		if (argv[5])
			(bodies[i])->count_of_pasta = ft_atoi(argv[5]);
		else
			(bodies[i])->count_of_pasta = -1;
		bodies[i]->master = bodies;
		give_my_forks(bodies[i], i, ft_atoi(argv[1]));
		bodies[i]->fork_list = rr;
		bodies[i]->mutex_list = rn;
		bodies[i]->eated_at = 0;
		bodies[i]->died = *mute;
		bodies[i]->died_bool = died_bool;
		bodies[i]->id = 1 + i;
		put_others(bodies[i], argv);
		i++;
	}
}
