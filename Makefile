CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex.c pipex_util.c
OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
