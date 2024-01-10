#include "philo.h"

void	*monitor(void *pointer)
{
	t_philo	*philo;
	int			i;

	philo = (t_philo *)pointer; //typecasting  //This allows the function to interpret pointer as a pointer to a t_philo structure.
	while (1)
	{
		if (check_freddo(philo) == 1 || check_overeat(philo) == 1)
			break ;
	}
	print_message("broke\n", philo);
	pthread_mutex_lock(&philo->prog->dead_lock);
  philo->prog->death = 1;
	i = 0;
	if (philo->prog->number_of_times_each_philosopher_must_eat == -1)
 	{
		while (i < philo->prog->number_of_philosophers)
  	{
  		if (!philo->prog->philos[i].is_dead)
  		{
  		  philo->prog->philos[i].is_dead = 1;
  		}
  		i++;
  	}
	}
  pthread_mutex_unlock(&philo->prog->dead_lock);
	return (pointer);
}
//check se il filosofo è freddo
int	check_freddo(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time() - philo->last_meal >= philo->prog->time_to_die &&
		!philo->is_eating )
	{
		pthread_mutex_unlock(&philo->meal_lock);

		print_message("is dead\n", philo); 	
		return(1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return(0);
}

int	check_overeat(t_philo *philo)
{
	if (philo->prog->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->n_meals >= philo->prog->number_of_times_each_philosopher_must_eat)
	{
		print_message("ate too much and died\n", philo);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);

	return (0);
}