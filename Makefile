NAME = philo

SRC = init.c main.c manage_threads.c monitor_threads.c routine.c utils.c minilibft/ft_atoi.c
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -lpthread -g 

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@gcc $(FLAGS) -o $(NAME) $(OBJ)
	@rm -f $(OBJ)
	
%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
