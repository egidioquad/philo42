#include "philo.h"

void	*routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
/* 	if (philo->philo_id % 2)
		ft_sleep(1); */
	//this checks if !philo.is_dead
	while(!stato_freddato(philo))
	{
		if (!eat(philo))
		{
			dream(philo);
			think(philo);
		}
		else
			return(pointer);
	}
	return(pointer);
}


int eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a r fork\n", philo);

	if (philo->number_of_philosophers == 1)
	{
		ft_sleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a l fork\n", philo);

	philo->is_eating = 1;
	print_message("is eating\n", philo);

	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->n_meals++;
	pthread_mutex_unlock(philo->meal_lock);


	ft_sleep(philo->time_to_eat);
	philo->is_eating = 0;


	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
//
	pthread_mutex_lock(philo->meal_lock);
	if (philo->n_meals >= philo->number_of_times_each_philosopher_must_eat
			&& philo->number_of_times_each_philosopher_must_eat != -1)
	{
    pthread_mutex_unlock(philo->meal_lock);
		return(1);
  }
  pthread_mutex_unlock(philo->meal_lock);
	return(0);
}

void dream(t_philo *philo)
{
	print_message("is sleeping\n", philo);
	ft_sleep(philo->time_to_sleep);
}

void think(t_philo *philo)
{
	print_message("is thinking\n", philo);
}
