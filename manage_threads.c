#include "philo.h"

int create_thread(t_prog *prog, pthread_mutex_t *forks)
{
	pthread_t	main_threadID;
	int				i;
	
	if(pthread_create(&main_threadID, NULL, &monitor, prog->philos) != 0)
		kill_all("Error! Couldnt create thread", prog, forks);
	i = 0;
	while (i < prog->philos[0].number_of_philosophers)
	{
		if (pthread_create(&prog->philos[i].threadID, NULL, &routine,
				&prog->philos[i]) != 0)
			kill_all("Thread creation error", prog, forks);
		i++;
	}
	if (pthread_join(main_threadID, NULL) != 0)
		kill_all("Thread join error", prog, forks);

	i = 0;
	while (i < prog->philos[0].number_of_philosophers)
	{
		if (pthread_join(prog->philos[i].threadID, NULL) != 0)
			kill_all("Thread join error", prog, forks);
		i++;
	}
	return (0);
}