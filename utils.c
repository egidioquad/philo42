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
	while(++i < prog->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&prog->philos[i].meal_lock);
	}
	if (prog->philos)
		free(prog->philos);
	exit (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit(write(2, "signora mi scusi che ore sono?\n", 32));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void print_message(char *mess, t_philo *philo) {
	size_t	start;

  pthread_mutex_lock(&philo->prog->write_lock);
  if (!stato_freddato(philo)) {
			start = get_time();
      printf("%zu %d ", start - philo->prog->start_time, philo->philo_id);
      // Check if the message is " is dead" and print in red if true
      if (strcmp(mess, "is dead\n") == 0) {
          printf("\x1b[31m%s\x1b[0m", mess); // ANSI escape codes for red color
      } else {
          printf("%s", mess);
      }
  }
  pthread_mutex_unlock(&philo->prog->write_lock);
}


int	stato_freddato(t_philo *philo)
{
	if (philo->last_meal < get_time())
	{
		return(1);
	}
	return(0);
}

int	ft_sleep(size_t milli)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milli)
		usleep(1);
	return (0);
}