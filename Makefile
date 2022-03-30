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
.PHONY: all clean fclean re

CC = gcc
CFLAGS = -I $(INCLUDES_DIR)
C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))
RM = rm -f

TARGET = push_swap

SRCS_BASE = app.c game.c operation.c \
			libft.c libft_try_atoi.c libft_split.c
SRCS = $(SRCS_BASE)
OBJECTS_DIR = objs/
OBJS = $(addprefix $(OBJECTS_DIR), $(SRCS_BASE:.c=.o))

INCLUDES_DIR = includes/
HEADER_BASE = push_swap.h
HDRS = $(addprefix $(INCLUDES_DIR), $(HEADER_BASE))

C_DEBUG_FLAGS = -g3 -fsanitize=address
CFLAGS += $(C_DEBUG_FLAGS)
LDFLAGS += $(C_DEBUG_FLAGS)

all: $(TARGET)	;
clean:			;	$(RM) -r $(OBJECTS_DIR)
fclean: clean	;	$(RM) $(TARGET)
re: fclean all	;

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJS): $(HDRS) | $(OBJECTS_DIR)

$(addprefix $(OBJECTS_DIR), %.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^
