APP_NAME = ush

LIBMXF = libmx

LIB_NAME = libmx.a

INC = \
	inc/ \
	libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
	ushell/*.c \
	read_str/*.c \
	parse_str/*.c \
	execute_str/*.c \
	sub_command/*.c \
	utility_functions/*c \
	redirect/*.c \
	commands/*.c \
	pids/*.c \
	history/*.c )

OBJ = *.o

CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install: libmx/libmx.a ush

libmx/libmx.a:
	@make -C $(LIBMXF)

ush : $(SRC) inc/ush.h libmx/libmx.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME) -ltermcap
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)

uninstall : clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME)

clean :
	@make clean -C $(LIBMXF)
	@rm -rf $(OBJ_DIR)

reinstall : uninstall install