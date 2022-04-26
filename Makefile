# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/01 23:48:34 by marvin            #+#    #+#              #
#    Updated: 2022/02/01 23:48:34 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

HEADER = minitalk.h

SERVER = server
SERVER_SRC = server.c utils.c
SERVER_OBJS = ${SERVER_SRC:.c=.o}

CLIENT = client
CLIENT_SRC = client.c utils.c
CLIENT_OBJS = ${CLIENT_SRC:.c=.o}

UTILS = utils
UTILS_SRC = utils.c
UTILS_OBJS = ${UTILS_SRC:.c=.o}

GCC = gcc

GFLAGS = -Wall -Wextra -Werror

RM = rm -f

.c.o:
	${GCC} ${GFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${SERVER} ${CLIENT}

${SERVER}: ${SERVER_OBJS} ${HEADER}
	${GCC} ${GFLAGS} ${SERVER_OBJS} -o $@

${CLIENT}: ${CLIENT_OBJS} ${HEADER}
	${GCC} ${GFLAGS} ${CLIENT_OBJS} -o $@

bonus:

clean:
	${RM} ${SERVER_OBJS} ${CLIENT_OBJS} ${UTILS_OBJS}

fclean: clean
	${RM} ${SERVER} ${CLIENT}

re: fclean all

.PHONY: all bonus clean fclean re