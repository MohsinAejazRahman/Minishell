# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 14:18:07 by skhastag          #+#    #+#              #
#    Updated: 2024/05/23 01:27:53 by skhastag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -std=c99

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
	ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			 ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)


all: $(NAME)
$(NAME): $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus
