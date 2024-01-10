#include "philo.h"

								//prog->philo
void	*routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;

	philo->last_meal = get_time();
 	if (philo->philo_id % 2)
		ft_sleep(philo->prog->time_to_eat - 1); 

	pthread_create(&philo->monitorID, NULL, &monitor, pointer);
	pthread_detach(philo->monitorID);

	while(!stato_freddato(philo) && philo->prog->death == 0)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	print_message("returning\n", philo);
	return(pointer);
}


void eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		print_message("\t\t\tLOCKED LOCKED\n", philo);
	print_message("has taken a r fork\n", philo);

	if (philo->prog->number_of_philosophers == 1)
	{
		ft_sleep(philo->prog->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a l fork\n", philo);


	print_message("\t\tBEFORELOCK\n", philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->is_eating = 1;


	philo->n_meals++;


	philo->last_meal = get_time();
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
	print_message("\t\tAFTER LOCK\n", philo);

	
	print_message("is eating\n", philo);
	ft_sleep(philo->prog->time_to_eat);


	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void dream(t_philo *philo)
{
	print_message("is sleeping\n", philo);
	ft_sleep(philo->prog->time_to_sleep);
}

void think(t_philo *philo)
{
	print_message("is thinking\n", philo);
}
