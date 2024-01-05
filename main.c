#include "philo.h"

void check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		exit(write(2, "Invalid arguments\n", 19));
	}
	i = 0; //parte da argv 1
	while (++i < 4)
	{
		if (!ft_atoi(argv[i]))
		{
			exit(write(2, "Invalid input\n", 15));
		}
	}
	if (argc == 6)
	{
		if (!ft_atoi(argv[5]))
		{
			exit(write(2, "Invalid input\n", 15));
		}
	}
}


int main(int argc, char **argv)
{
	check_input(argc, argv);
	il_vero_main(argc, argv);
	return (0);
}

int il_vero_main(int argc, char **argv)
{
	pthread_mutex_t	forks[ft_atoi(argv[1])];
	t_philo	philos[ft_atoi(argv[1])];
	t_prog		prog;

	//check_input(argc, argv);
	init_prog(&prog, philos); //passing as a pointer address to modify the original structure
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &prog, forks, argc, argv);
	create_thread(&prog, forks);
	kill_all("tHE eND", &prog, forks);
	return (0);
}

//./philo 5 800 200 200
//./philo 5 800 200 200 7