
SRCS	=	utils/ph_actions.c utils/ph_atoi.c utils/ph_utils.c main.c philosophers.c utils/queue.c

OBJS	=	$(SRCS:.c=.o)

HEADER	=	philo_three.h

NAME	=	philo_three

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
