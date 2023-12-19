#include "philo.h"

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer; //typecasting 
	//This allows the function to interpret pointer as a pointer to a t_philo structure.
	while (1)
		if (check_dead(philos) == 1 || check_ate_all(philos) == 1)
			break ;
	return (pointer);
}