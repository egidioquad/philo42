#include "philo.h"

void check_input(int argc, char **argv)
{
	int	i;
	int x;

	if (argc < 5 || argc > 6)
	{
		printf("Input valid arguments");
		exit(2);
	}
	i = 0;

	while (++i <= 5)
	{
		x = ft_atoi2(argv[i]);
		if (x == 0)
		{
			exit(write(2, "Invalid input", 14));
		}
	}
}


int main(int argc, char **argv)
{
	pthread_mutex_t	forks[ft_atoi2(argv[1])];
	t_philo	philos[ft_atoi2(argv[1])];
	t_prog		prog;

	check_input(argc, argv);
	init_prog(&prog, philos); //passing as a pointer address to modify the original structure
	init_forks(forks, ft_atoi2(argv[1]));
	create_thread(&prog, forks);
	return (0);
}


/*
// args  5 800 200 200 7
		5 — The number of philosophers
		800 — The time a philosopher will die if he doesn’t eat
		200 — The time it takes a philosopher to eat
		200 — The time it takes a philosopher to sleep
		7 — Number of times all the philosophers need to eat before terminating the program **optional





	 */