/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:43:00 by ialgac            #+#    #+#             */
/*   Updated: 2022/07/08 03:52:55 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

unsigned int	time_in_ml(void)
{
	struct timeval	tv;
	unsigned int	ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

unsigned int	the_counter(unsigned int old)
{
	return (time_in_ml() - old);
}

t_person	**crt_bodies(char **argv, pthread_mutex_t **mute, int *died_bool)
{
	t_person	**rtn;

	rtn = (t_person **)malloc(sizeof(t_person *) * ft_atoi(argv[1]));
	put_bodies(rtn, argv, mute, died_bool);
	return (rtn);
}

int	check_argument(int ac, char **av)
{
	int	i;
	int	k;

	i = 1;
	while (i < ac)
	{
		k = 0;
		while (av[i][k])
		{
			if (av[i][k] < '0' || av[i][k] > '9')
				return (0);
			k++;
		}
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
