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

LIBS =	Libft/libft.a

$(NAME): $(OBJS)
	make -C Libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make -C Libft clean

fclean: clean
	rm -f $(NAME)
	make -C Libft fclean

re: fclean all

#./philo 5 2000 500 500 500