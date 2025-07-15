NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = philo.c			\
	  philo_utils.c		\
	  utils.c			\
	  init.c        	\
	  time.c			\
	  philo_routine.c	\


OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	

all: $(NAME)

clean:
	rm -f $(OBJ)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
