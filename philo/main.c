/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:56:54 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/31 21:10:57 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutex_arr(pthread_mutex_t *fork_mutex, int last_index)
{
	int	i;

	i = -1;
	while (++i <= last_index)
	{
		pthread_mutex_destroy(&fork_mutex[i]);
	}
	free(fork_mutex);
	return (1);
}

int	make_mutex(t_env *env) // 미완 - mutex 더 추가해야함... 정리 함 해야할듯.
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&env->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&env->env_mutex, NULL))
	{
		pthread_mutex_destroy(&env->print_mutex);
		return (1);
	}
	env->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* env->philo_num);
	if (!env->fork_mutex)
		return (1);
	while (++i < env->philo_num)
	{
		if (pthread_mutex_init(&env->fork_mutex[i], NULL))
		{
			pthread_mutex_destroy(&env->print_mutex);
			pthread_mutex_destroy(&env->env_mutex);
			return (destroy_mutex_arr(env->fork_mutex, i - 1));
		}
	}
	return(0);
}

int env_setting(int argc, char **argv, char **envp, t_env *env)
{
	memset(env, 0, sizeof(t_env));
	env->philo_num = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->must_eat_count = -1;
	if (argc == 6)
		env->must_eat_count = ft_atoi(argv[5]);
	if (make_mutex(&env))
		return (1);
	return (0);
}

// int	eat_time(t_philo *philo)
// {
// 		philo->eat_time = return_time
// }

void	ft_usleep(t_philo *philo, long long sleep_time)
{
	long long s_time;

	s_time = return_time();
	if (check_end(philo->env))
			return ;
	while (s_time + sleep_time > return_time())
	{
		if (check_end(philo->env))
			return ;
		usleep(100);
	}
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->fork_mutex[philo->philo_id]); // 왼쪽
	if (check_end(philo->env))
	{
		pthread_mutex_unlock(&philo->env->fork_mutex[philo->philo_id]);
		return (1);
	}
	pthread_mutex_lock(&philo->env->fork_mutex[(philo->philo_id + 1) % philo->env->philo_num]); // 오른쪽
	philo->eat_time = return_time();
	println(philo->env, philo->eat_time, philo->philo_id, "is eating");
	ft_usleep(philo, philo->env->time_to_eat);
	pthread_mutex_unlock(&philo->env->fork_mutex[(philo->philo_id + 1) % philo->env->philo_num]);
	pthread_mutex_unlock(&philo->env->fork_mutex[philo->philo_id]);
	return (check_end(philo->env));
}

int thread_do(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->env_mutex);
	pthread_mutex_unlock(&philo->env->env_mutex);
	philo->eat_time = return_time();
	if (check_end(philo->env))
		return (3);
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo, philo->env->time_to_eat);
	else if (philo->env->philo_num % 2 && philo->philo_id == philo->env->philo_num)
		ft_usleep(philo, philo->env->time_to_eat * 2);
	while (!check_die(philo)) // if not die // 이거 생각 더해보기 모니터 있으면 굳이 싶긴하잖아~
	{
		if (ft_eat(philo)) // eating
			return (1);
		println(philo->env, return_time(), philo->philo_id, "is sleeping");
		ft_usleep(philo, philo->env->time_to_sleep); // sleeping
		if (check_end(philo->env))
			return (2);
		println(philo->env, return_time(), philo->philo_id, "is thinking");
	}
	return (0); // end at thinking
}

void	free_thread(t_env *env, t_philo	*philo)
{
	int	index;

	index = -1;
	while (++index < env->philo_num)
		pthread_join(philo[index].thread_id, NULL);
}

void	monitoring(t_env *env, t_philo *philo)
{
	//
}

int	philo(t_env *env)
{
	t_philo *philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * (env->philo_num));
	if (!philo)
		return (1);
	memset(philo, 0, sizeof(t_philo) * env->philo_num);
	pthread_mutex_lock(&env->env_mutex);
	while(++i < env->philo_num)
	{
		philo[i].env = env;
		philo[i].philo_id = i + 1;
		pthread_create(philo[i].thread_id, NULL, thread_do, &philo[i]);
	}
	pthread_mutex_unlock(&env->env_mutex);
	// monitoring(env, philo);
	// thread join으로 기다려야 할듯?
	free_thread(env, philo);
	// free_all(env, philo); // + free해줄거 해주기.
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc == 5 || argc == 6)
	{
		if (env_setting(argc, argv, envp, &env))
			return (1);
	}
	else
		return (1);
	philo(&env);
	// free_env(env);
}
