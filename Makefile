#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := so_long
CC        := gcc
FLAGS    := -Wall -Wextra -Werror
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      src/action_collect.c \
                          src/action_hook.c \
                          src/action_move.c \
                          src/autorisation.c \
						  src/exit_game.c \
                          src/gnl.c \
                          src/graph_mlx.c \
                          src/graph_mlx1.c \
                          src/graph_mlx2.c \
                          src/help.c \
                          src/so_long.c \
                          src/utils.c \
                          src/verify_contour.c \
                          src/verify_data.c \
                          src/verify_matrix.c
                          
OBJS        := $(SRCS:.c=.o)

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

UNAME		:=	$(shell uname)

#Custom command for MacOS vs Linux
ifeq ($(UNAME), Darwin)
.c.o:
	${CC} ${FLAGS} -Imlx -c $< -o ${<:.c=.o}
endif

ifeq ($(UNAME), Linux)
.c.o:
	${CC} ${FLAGS} -Imlx_linux -c $< -o ${<:.c=.o}
endif
##

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@ $(MAKE) -C mlx all >/dev/null 2>&1
			@ cp ./mlx/libmlx.a .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

ifeq ($(UNAME), Linux)
$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

all:		${NAME}

ifeq ($(UNAME), Darwin)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif

ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif


ifeq ($(UNAME), Linux)
fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

ifeq ($(UNAME), Darwin)
fclean:		clean
			@ ${RM} ${NAME}
			@ rm libmlx.a
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

re:			fclean all

.PHONY:		all clean fclean re


