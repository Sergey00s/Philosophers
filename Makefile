NAME = philo

SRCS = ft_atoi.c \
		main.c \
		utils.c \
		put_funcs.c \
		self_utils.c \
		self_utils_second.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -pthread $(OBJS) -o $(NAME)

.c.o:
	$(CC) -c $< -o $@
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all, clean, fclean, re
