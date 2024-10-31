/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:56:47 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/31 21:01:11 by yuyu             ###   ########.fr       */
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

typedef struct	s_env
{
	int				philo_num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	int 			check_is_end; // 0 -> live, 1 -> die
	bool			*fork_arr;  // 아직 이거 설정 안함.
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	env_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*philo_mutex; // 아직 미완 (먹은 시간 접근 시....)
} t_env;
// &env->fork_mutex == &(env->fork_mutex) != (&env)->fork_mutex

typedef struct	s_philo
{
	int			philo_id; // 1부터 ~
	int			eat_count;
	long long	eat_time; // ms
	// long long	cur_time; // ms
	t_env		*env; // env 접근 가능
	pthread_t	thread_id;
} t_philo;

// int usleep(useconds_t usec);
// int gettimeofday(struct timeval *tv, struct timezone *tz);
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                //    void *(*start_routine)(void *), void *arg);
// int pthread_detach(pthread_t thread);
// int pthread_join(pthread_t thread, void **retval);
// int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
// int pthread_mutex_destroy(pthread_mutex_t *mutex);
// int pthread_mutex_lock(pthread_mutex_t *mutex);
// int pthread_mutex_unlock(pthread_mutex_t *mutex);


int		ft_atoi(const char *str);
void	println(t_env *env, long long cur_time, int id, char *str);

#endif
