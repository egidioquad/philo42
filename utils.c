#include "philo.h"

void	kill_all(char *str, t_prog *prog, pthread_mutex_t *forks)
{
	int	i;

	if(str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}

	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->write_lock);

	i = -1;
	while(++i < prog->philos[0].number_of_philosophers)
		pthread_mutex_destroy(&forks[i]);
}