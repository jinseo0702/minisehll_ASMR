CC = clang
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS = -g 
RM = rm -rf

#SRC = lab/s_fuc_indoc.c
SRC = src/mns/main.c \
src/mns/control_node.c \
src/mns/init_env.c \
src/builtins/ft_env.c \
src/builtins/ft_unset.c \
src/builtins/ft_cd.c \
src/builtins/ft_pwd.c \
src/builtins/ft_export.c \
src/builtins/ft_exit.c \
src/builtins/ft_echo.c \
src/builtins/ft_check_builtins.c \
src/excute/about_file.c \
src/excute/excute.c \
src/excute/is_access.c \
src/prompt/prompt.c \
src/prompt/heredoc.c \
src/parser/split_pipe.c \
src/parser/splitcmd.c \
src/parser/re_env.c \
src/error/error.c \


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
