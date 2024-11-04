CC = cc
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g
RM = rm -rf

#SRC = lab/s_fuc_indoc.c
SRC = src/mns/main.c \
src/mns/control_node.c \
src/mns/init_env.c \
src/builtins/ft_env.c \
src/builtins/ft_unset.c \
src/prompt/prompt.c

OBJS = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME): $(OBJS)
	@make -C libft/
	@$(CC) $(OBJS) -L libft/ -lft -o $(NAME) -lreadline

clean :
	@make clean -C libft/
	@$(RM) $(OBJS)

fclean :
	@make fclean -C libft/
	@$(RM) $(OBJS) $(NAME)

re : 
	@make fclean
	@make all

.PHONY: all clean fclean re
