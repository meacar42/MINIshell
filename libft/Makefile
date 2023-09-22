NAME	=	libft.a

SRCS	=	*.c

OBJS = $(SRCS:.c=.o)

CC	=	gcc
RM	=	rm -f
FLAGS	= -Wall -Wextra -Werror

$(NAME): 
		@$(CC) $(FLAGS) -c $(SRCS) 
		@ar rc $(NAME) $(OBJS)

all: $(NAME)

clean:
		@$(RM) $(OBJS) 
		@$(RM) $(BONUS_OBJS)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
