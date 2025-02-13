##
## EPITECH PROJECT, 2023
## CSFML bootstrap
## File description:
## Makefile
##


NAME	=	my_rpg

SRCS	=	$(wildcard menu/src/*.c) \
			$(wildcard 2D_map/src/*.c) \
			$(wildcard raycast/src/*.c) \

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I./include

LDFLAGS		=	-L./ -lcsfml-graphics -lcsfml-window -lcsfml-system \
				-lcsfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) *~
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re:	fclean all
