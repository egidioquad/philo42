#include "philo.h"

int create_thread(t_prog *prog, pthread_mutex_t *forks)
{
	pthread_t	main_threadID;
	int				i;
	
	if(pthread_create(&main_threadID, NULL, &monitor, prog->philos) != 0)
		kill_all("Error! Couldnt create thread", prog, forks);
	i = -1;
	while (i < prog->philos[0].number_of_philosophers)
	{
		if (pthread_create(&prog->philos[i].threadID, NULL, &philo_routine,
				&prog->philos[i]) != 0)
			destory_all("Thread creation error", prog, forks);
		i++;
	}
}

/* Function Explanation:

	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

    Thread Creation: pthread_create creates a new thread and starts its execution.

    Thread ID: Upon successful creation, the identifier for the new thread is stored in the pthread_t variable provided (thread).

    Thread Attributes: The attr parameter allows you to specify attributes for the new thread, such as its scheduling policy, stack size, etc. If you don't need specific attributes, you can usually pass NULL to use default settings.

    Start Routine: The start_routine is the function that will be executed by the new thread once it's created. This function defines the behavior of the thread.

    Argument Passing: The arg parameter allows you to pass an argument to the start_routine. This can be used to pass data or information needed by the thread function (start_routine) during its execution.


  // Wait for the thread to finish executing
    pthread_join(my_thread, NULL);

 */