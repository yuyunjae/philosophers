/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:56:47 by yuyu              #+#    #+#             */
/*   Updated: 2024/11/09 18:02:50 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <memory.h>
# include <stdbool.h>

typedef struct s_env
{
	int				philo_num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	int				must_eat_remain;
	int				must_eat_count;
	int				check_is_end;
	bool			*fork_arr;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	env_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	eat_cnt_mutex;
	pthread_mutex_t	*fork_mutex;
}	t_env;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	long long	eat_time;
	t_env		*env;
	pthread_t	thread_id;
}	t_philo;

//--------------------------- philo.c ---------------------------//
void		*thread_do(void *arg);
int			philo(t_env *env);

//--------------------------- philo_do.c ---------------------------//
int			ft_eat(t_philo *philo);

//--------------------------- philo_end.c ---------------------------//
void		change_check_end(t_env *env);
int			check_end(t_env *env);
int			check_die(t_philo *philo);

//--------------------------- philo_env.c ---------------------------//
void		free_mutex(t_env *env, int mutex_index);
int			env_setting(int argc, char **argv, t_env *env);

//--------------------------- philo_utils.c ---------------------------//
void		swap_fork(int *left_fork, int *right_fork);
int			ft_sleep(t_philo *philo, long long sleep_time);
void		println(t_philo *philo, int id, char *str);
long long	return_time(t_env *env);

//--------------------------- ft_atoi.c ---------------------------//
int			ft_atoi(const char *str);

//--------------------------- ft_strncmp.c ---------------------------//
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
