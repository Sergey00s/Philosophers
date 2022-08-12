/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:43:18 by ialgac            #+#    #+#             */
/*   Updated: 2022/07/08 04:08:10 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
# define PH_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_person
{
	struct s_person	**master;
	int				id;
	int				*died_bool;
	unsigned int	start_time;
	int				philo_count;
	int				time_for_die;
	int				time_for_eat;
	int				time_for_slp;
	int				count_of_pasta;
	int				eated_at;
	int				left_fork_index;
	int				right_fork_index;
	int				*fork_list;
	pthread_mutex_t	**mutex_list;
	pthread_mutex_t	*died;
	pthread_t		tid;
}					t_person;

void			free_leaks(t_person **master, int fc);
int				take_forks(t_person *self);
int				any_dead_body(t_person *self);
int				time_sleep(t_person *self, unsigned int sc, int sit);
int				leave_forks(t_person *self);
int				check_argument(int ac, char **av);
t_person		**crt_bodies(char **argv, \
pthread_mutex_t **mute, int *died_bool);
void			put_bodies(t_person **bodies, \
char **argv, pthread_mutex_t **mute, int *died_bool);
pthread_mutex_t	**put_mutexs(int pc);
int				*put_forks(int pc);
int				ft_atoi(const char *s);
unsigned int	the_counter(unsigned int old);
unsigned int	time_in_ml(void);

#endif
