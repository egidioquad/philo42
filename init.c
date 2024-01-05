#include "philo.h"

void	init_prog(t_prog *prog, t_philo *philos)
{
	prog->philos = philos;
	prog->death = 0;
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	
}
//when working with pointers to structures in C, use the arrow -> operator

void init_forks(pthread_mutex_t *forks, int num_philos)
{
	int	x;

	x = 0;
	while (x < num_philos)
	{
		pthread_mutex_init(&forks[x], NULL);
		x++;
	}
}

void	init_fill_input(t_philo *philo, int argc, char **argv)
{
	philo->number_of_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);

	if (argc == 6)
	{
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
	else{
		philo->number_of_times_each_philosopher_must_eat = -1;
	}

}

void	init_philos(t_philo *philos, t_prog *prog, pthread_mutex_t *forks, int argc, char **argv)
{
	int	x;

	x = 0;
	while (x < ft_atoi(argv[1]))
	{
		init_fill_input(&philos[x], argc, argv);
		philos[x].philo_id = x + 1;
		philos[x].is_eating = 0;
		philos[x].start_time = get_time();
		philos[x].last_meal = get_time();
		philos[x].write_lock = &prog->write_lock;
		philos[x].dead_lock = &prog->dead_lock;
		philos[x].meal_lock = &prog->meal_lock;
		philos[x].is_dead = 0;
		philos[x].l_fork = &forks[x];
		if (x == 0)
			philos[x].r_fork = &forks[philos[x].number_of_philosophers - 1];
		else
			philos[x].r_fork = &forks[x - 1];
		x++;
	}

}
