#include "philo.h"

int create_thread(t_prog *prog, pthread_mutex_t *forks)
{
	int				i;
	
	i = 0;
	prog->start_time = get_time();
	while (i < prog->number_of_philosophers)
	{

		if (pthread_create(&prog->philos[i].threadID, NULL, &routine, (void *)&prog->philos[i]) != 0)
			kill_all("Error: pthread_create", prog, forks);
		i++;
	}
	i = 0;
	while (i < prog->number_of_philosophers)
	{
		if (pthread_join(prog->philos[i].threadID, NULL) != 0)
			kill_all("Error: pthread_join", prog, forks);
		i++;
	}
	return (0);
}	