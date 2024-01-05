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
	int	number_of_times_each_philosopher_must_eat;

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
void	*routine(void *pointer);

//main
int main(int argc, char **argv);
int il_vero_main(int argc, char **argv);

void check_input(int argc, char **argv);
//thread
int create_thread(t_prog *prog, pthread_mutex_t *forks);
//
int	check_freddo(t_philo *philo);
int	check_filosofi_morti(t_philo *philos);
int	check_eat_all(t_philo *philos);

//routine
int eat(t_philo *philo);
void dream(t_philo *philo);
void think(t_philo *philo);
//init
void	init_prog(t_prog *prog, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int num_philos);
void	init_fill_input(t_philo *philo, int argc, char **argv);
void	init_philos(t_philo *philos, t_prog *prog, pthread_mutex_t *forks, int argc, char **argv);

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