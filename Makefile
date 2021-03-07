##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## The supreme makefile
##

## MAIN
MAIN_NM =	nm/main.c
MAIN_OBJDUMP = objdump/main.c

## SRC
SRC_NM	= nm/elf_64/sym_type.c \
		  nm/elf_64/sym_print.c \
		  nm/elf_32/sym_print.c \
		  nm/elf_32/sym_type.c \
		  all/file.c

SRC_OBJDUMP = all/file.c \
			  objdump/elf_64/strtab.c

## NAME
NAME_NM	=	my_nm
NAME_OBJDUMP = my_objdump

## OBJ
OBJ_NM	=	$(SRC_NM:.c=.o)
OBJ_OBJDUMP	=	$(SRC_OBJDUMP:.c=.o)
OBJ_MAIN_NM	=	$(MAIN_NM:.c=.o)
OBJ_MAIN_OBJDUMP = 	$(MAIN_OBJDUMP:.c=.o)


CC		=	gcc

CPPFLAGS		+=	-Wall -Wextra -I include -g3

all: nm objdump

nm:	$(NAME_NM)

$(NAME_NM): $(OBJ_MAIN_NM) $(OBJ_NM)
			$(CC) -o $(NAME_NM) $(OBJ_MAIN_NM) $(OBJ_NM) $(CPPFLAGS)

objdump:	$(NAME_OBJDUMP)
$(NAME_OBJDUMP): 	$(OBJ_OBJDUMP) $(OBJ_MAIN_OBJDUMP)
					$(CC) -o $(NAME_OBJDUMP) $(OBJ_MAIN_OBJDUMP) $(OBJ_OBJDUMP) $(CPPFLAGS)

clean:
	rm -f $(OBJ_MAIN_NM)
	rm -f $(OBJ_MAIN_OBJDUMP)
	rm -f $(OBJ_NM)
	rm -f $(OBJ_OBJDUMP)

fclean:	clean
	rm -f $(NAME_NM)
	rm -f $(NAME_OBJDUMP)

re:	fclean	all

.PHONY: clean fclean re