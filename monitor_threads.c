#include "philo.h"

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer; //typecasting 
	//This allows the function to interpret pointer as a pointer to a t_philo structure.
	while (1)
		if (check_filosofi_morti(philos) == 1 || check_overeat(philos) == 1)
			break ;
	return (pointer);
}

//check se il filosofo è freddo
int	check_freddo(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die &&
		!philo->is_eating)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return(1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return(0);
}

int	check_filosofi_morti(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].number_of_philosophers)
	{
		if (check_freddo(&philos[i]))
		{
			print_message("is dead", &philos[i], philos->philo_id);
			pthread_mutex_lock(philos->dead_lock);
			philos[i].is_dead = 1;
			pthread_mutex_unlock(philos->dead_lock);
			return(1);
		}
		i++;
	}
	return(0);
}

int	check_overeat(t_philo *philos)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (philos[0].number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (i < philos[0].number_of_philosophers)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].n_meals >= philos[i].number_of_times_each_philosopher_must_eat)
			ate++;
		pthread_mutex_unlock(philos[i].meal_lock);
	}
	if (ate == philos[0].number_of_philosophers)
		return (1);
}