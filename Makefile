NAME = ft_ping

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iincludes

SRCS =	srcs/main.c \
		srcs/init.c \
		srcs/parser.c \
		srcs/error.c \
		srcs/cleanup.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c includes/ft_ping.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re