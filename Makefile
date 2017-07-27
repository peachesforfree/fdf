NAME = fdf

FLAGS = -Wall -Werror -Wextra

LIBS = libs/minilibx/libmlx.a\
	   libs/libft/libft.a

SRCS = fdf_main.c\
	   fdf_read.c\
	   fdf_draw.c\
	   fdf_strings.c\
	   fdf_events.c

OBJS = $(SRCS:.c=.o)

INC = includes/

FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	@make -C libs/libft
	@make -C libs/minilibx
	@gcc $(FLAGS) $(SRCS) -I$(INC) $(LIBS) $(FRAMEWORKS) 

clean:
	@/bin/rm -f rm $(OFILES)
	@make -C libs/libft/ clean
	@make -C libs/minilibx/ clean	

fclean: clean
	@/bin/rm -f rm $(NAME)
	@make -C libs/libft/ fclean
	@make -C libs/minilibx/ fclean

re: fclean all
