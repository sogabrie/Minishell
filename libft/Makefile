NAME = libft.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LIBS   = -I ../includes/

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) Makefile
		@ar rcs $(NAME) $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean $(NAME) 

.PHONY : all clean fclean re
