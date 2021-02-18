
SRCS	=	utils/ph_actions.c utils/ph_atoi.c utils/ph_itoa.c utils/ph_utils.c forks.c main.c monitoring.c philosophers.c

OBJS	=	$(SRCS:.c=.o)

HEADER	=	philo_one.h

NAME	=	philo_one.a

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

$(NAME):	$(OBJS) $(HEADER)
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(BOBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
