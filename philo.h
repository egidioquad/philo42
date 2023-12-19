#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo {
	int	number_of_philosophers;
	size_t time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat; //optional

	size_t	start_time;
	size_t	last_meal;
	int	n_meals;
	int	is_eating;
	int	philo_id;
	int is_dead;

	pthread_t				threadID;

	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

}	t_philo;


typedef struct s_prog
{
	int							death;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo					*philos;
}					t_prog;

void	*monitor(void *pointer);


#endif