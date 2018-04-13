#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvlasenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/01 15:10:23 by vvlasenk          #+#    #+#              #
#    Updated: 2017/01/01 15:10:25 by vvlasenk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	=	RTv1
LIBFT	=	libft.a

GCC		=	gcc
WWW		=	-Wall -Wextra -Werror
IGRAPH	=	-L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL \
			-framework AppKit

SRCTRV1	=	check_scene_file.c check_scene_file1.c check_scene_file2.c \
			check_scene_file3.c check_scene_file4.c data_parc.c data_parc1.c \
			data_parc2.c draw.c error.c findintersection.c init_data.c \
			init_data1.c math.c math1.c math2.c rtv1.c win_oi.c
SRCLIB	=	ft_memset.c ft_memcpy.c ft_memchr.c ft_memcmp.c \
			ft_strcmp.c ft_bzero.c ft_memmove.c ft_strlen.c \
			ft_strcpy.c ft_strncpy.c ft_memccpy.c ft_toupper.c \
			ft_strcat.c ft_strncat.c ft_strchr.c ft_strrchr.c \
			ft_strncmp.c ft_tolower.c ft_strstr.c ft_strdup.c \
			ft_strnstr.c ft_atoi.c ft_strlcat.c ft_isalpha.c \
			ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c \
			ft_putstr.c ft_putchar.c ft_memalloc.c ft_memdel.c \
			ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
			ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
			ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
			ft_strsplit.c ft_itoa.c ft_putendl.c ft_putnbr.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_lstmap.c ft_lstnew.c ft_lstiter.c ft_lstdelone.c \
			ft_lstdel.c ft_lstadd.c ft_putnbr_fd.c ft_nbrlen.c \
			get_next_line.c

OBJLIB	=	$(addprefix $(OBJDIRL),$(SRCLIB:.c=.o))
OBJRTV1	=	$(addprefix $(OBJDIRR),$(SRCTRV1:.c=.o))

INCLUDES=	-I./includes/

LIBFTDIR=	./libft/
OBJDIRL	=	./objlib/
OBJDIRR =	./objRTv1/
SRCDIR	=	./sources/

all: $(NAME)

$(NAME):	$(LIBFT) $(OBJDIRR) $(OBJRTV1)
			$(GCC) -o $@ $(IGRAPH) $(OBJRTV1) $(LIBFT)

$(LIBFT):	$(OBJDIRL) $(OBJLIB)
			ar rc $(LIBFT) $(OBJLIB)

$(OBJDIRL):
			mkdir -p $@

$(OBJDIRL)%.o:$(LIBFTDIR)%.c
			$(GCC) $(WWW) $(INCLUDES) -o $@ -c $<

$(OBJDIRR):
			mkdir -p $@

$(OBJDIRR)%.o:$(SRCDIR)%.c
			$(GCC) $(WWW) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJLIB) $(OBJDIRL) $(OBJRTV1) $(OBJDIRR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all
