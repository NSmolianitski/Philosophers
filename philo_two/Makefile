
SRCS	=	utils/ph_actions.c utils/ph_atoi.c utils/ph_utils.c forks.c main.c philosophers.c

OBJS	=	$(SRCS:.c=.o)

HEADER	=	philo_two.h

NAME	=	philo_two

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

%.o:		%.c
			$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
