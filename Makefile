NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

SRCS =	philo.c			\
		philo_eat.c		\
		philo_time.c	\
		philo_death.c	\
		philo_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

#./philo 5 2000 500 500 500
#hellgrind