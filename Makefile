# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 15:11:48 by jkong             #+#    #+#              #
#    Updated: 2022/03/22 15:11:48 by jkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o .h
.PHONY: all clean fclean re bonus

CC = cc
CFLAGS = -I $(INCLUDES_DIR)
C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))
RM = rm -f

SRCS_BASE = app.c game.c checker.c \
			solver.c solver_micro.c solver_mini.c solver_qsort.c \
			operation.c visualize.c util.c \
			libft.c libft_try_atoi.c libft_split.c \
			safe_mem.c safe_io.c
OBJECTS_DIR = objs/

TARGET = push_swap
SRCS = $(SRCS_BASE) app_solver.c
OBJS = $(addprefix $(OBJECTS_DIR), $(SRCS:.c=.o))

TARGET_BONUS = checker

SRCS_BONUS = $(SRCS_BASE) app_checker.c
OBJS_BONUS = $(addprefix $(OBJECTS_DIR), $(SRCS_BONUS:.c=.o))

INCLUDES_DIR = includes/
HEADER_BASE = push_swap.h
HDRS = $(addprefix $(INCLUDES_DIR), $(HEADER_BASE))

#C_DEBUG_FLAGS = -g3 -fsanitize=address
CFLAGS += $(C_DEBUG_FLAGS)
LDFLAGS += $(C_DEBUG_FLAGS)

all: $(TARGET) bonus
clean:					;	$(RM) -r $(OBJECTS_DIR)
fclean: clean			;	$(RM) $(TARGET) $(TARGET_BONUS)
re: fclean all
bonus: $(TARGET_BONUS)

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJS) $(OBJS_BONUS): $(HDRS) | $(OBJECTS_DIR)

$(addprefix $(OBJECTS_DIR), %.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^
	
$(TARGET_BONUS): $(OBJS_BONUS)
	$(CC) -o $@ $(LDFLAGS) $^
