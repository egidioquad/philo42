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

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit(write(2, "signora mi scusi che ore sono?\n", 32));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(char *mess, t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	if (!stato_freddato(philo))
		printf("\t%zu %d %s", get_time() - philo->start_time, philo->philo_id, mess);
	pthread_mutex_unlock(philo->write_lock);
}


int	stato_freddato(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return(1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return(0);
}

int	ft_sleep(size_t milli)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milli)
		usleep(1); //aggiusta in base ad esigenza
	return (0);
}