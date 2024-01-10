#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>


typedef struct s_philo {
	int	n_meals;
	int	is_eating;
	int	philo_id;
	int is_dead;

	size_t	last_meal;
	
	pthread_mutex_t	meal_lock;

	pthread_t				threadID;
	pthread_t				monitorID;

	
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

	struct s_prog					*prog;

}	t_philo;


typedef struct s_prog
{
	int							death;

	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	size_t	start_time;

	int	number_of_philosophers;
	int	number_of_times_each_philosopher_must_eat;

	size_t time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;

	t_philo	*philos;
}					t_prog;

void	*monitor(void *pointer);
void	*routine(void *pointer);

//main
int main(int argc, char **argv);
int il_vero_main(int argc, char **argv);

void check_input(int argc, char **argv);
//thread
int create_thread(t_prog *prog, pthread_mutex_t *forks);
//
int	check_freddo(t_philo *philo);
int	check_overeat(t_philo *philo);
//routine
void eat(t_philo *philo);
void dream(t_philo *philo);
void think(t_philo *philo);
//init
void	init_prog(t_prog *prog, pthread_mutex_t *forks, int argc, char **argv);
void	init_forks(pthread_mutex_t *forks, int num_philos);
void	init_fill_input(t_prog *prog, int argc, char **argv);
t_philo	*init_philos(t_prog *prog, pthread_mutex_t *forks);

//utils
void	kill_all(char *str, t_prog *prog, pthread_mutex_t *forks);
size_t	get_time(void);
void	print_message(char *mess, t_philo *philo);
int	stato_freddato(t_philo *philo);
int	ft_sleep(size_t milli);
//minilib
int	ft_atoi(char *str);
int ft_strlen(char *str);



#endif