DIR_HEADERS	= -I./include/

DIR_SRCS	= ./srcs/

SRC			=	0_main.c \
				1_init.c \
				utils.c \
				2_eat.c \
				3_sleep_and_think.c \

SRCS		= $(addprefix $(DIR_SRCS), $(SRC))

OBJS		= $(SRCS:.c=.o)

NAME		= philo

GCC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra -g

%.o:%.c
			$(GCC) -pthread $(CFLAGS) $(DIR_HEADERS) -c $< -o $@

$(NAME):	$(OBJS) include/*
			$(GCC) $(CFLAGS) -pthread $(DIR_HEADERS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
