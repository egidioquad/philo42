#include "philo.h"

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

void	init_fill_input(t_prog *prog, int argc, char **argv)
{
	prog->number_of_philosophers = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);

	if (argc == 6)
		prog->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		prog->number_of_times_each_philosopher_must_eat = -1;
}

t_philo	*init_philos(t_prog *prog, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int	x;

	philos = (t_philo *)malloc(sizeof(t_philo) * prog->number_of_philosophers);
	if (!philos)
		exit(write(2, "Error: malloc failed\n", 22));

	x = 0;
	while (x < prog->number_of_philosophers)
	{
		pthread_mutex_init(&philos[x].meal_lock, NULL);
		philos[x].philo_id = x + 1;
		philos[x].n_meals = 0;
		philos[x].is_eating = 0;
		philos[x].is_dead = 0;
	

		philos[x].prog = prog;
		philos[x].l_fork = &forks[x];
		if (x == 0)
			philos[x].r_fork = &forks[prog->number_of_philosophers - 1];
		else
			philos[x].r_fork = &forks[x - 1];
		x++;
	}
	return (philos);
}

void	init_prog(t_prog *prog, pthread_mutex_t *forks, int argc, char **argv)
{
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	init_fill_input(prog, argc, argv);
	init_forks(forks, prog->number_of_philosophers);
	prog->death = 0;
	prog->philos = init_philos(prog, forks);
}
