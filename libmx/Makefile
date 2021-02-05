LIBMX = libmx
NAME = libmx.a
SRCD = src
OBJD = obj
SRC = mx_isalpha.c \
	mx_atoi.c \
	mx_binary_search.c \
	mx_bubble_sort.c \
	mx_count_substr.c \
	mx_count_words.c \
	mx_create_node.c \
	mx_del_extra_spaces.c \
	mx_del_strarr.c \
	mx_delete_first_needle.c \
	mx_foreach.c \
	mx_get_char_index.c \
	mx_get_substr_index.c \
	mx_hex_to_nbr.c \
	mx_isdigit.c \
	mx_itoa.c \
	mx_list_size.c \
	mx_memccpy.c \
	mx_memchr.c \
	mx_memcmp.c \
	mx_memcpy.c \
	mx_memmem.c \
	mx_memmove.c \
	mx_memrchr.c \
	mx_memset.c \
	mx_nbr_to_hex.c \
	mx_numlen.c \
	mx_pop_back.c \
	mx_pop_front.c \
	mx_pow.c \
	mx_print_strarr.c \
	mx_printchar.c \
	mx_printint.c \
	mx_printlist.c \
	mx_printstr.c \
	mx_push_back.c \
	mx_push_front.c \
	mx_quicksort.c \
	mx_read_line.c \
	mx_replace_substr.c \
	mx_sort_list.c \
	mx_sqrt.c \
	mx_str_reverse.c \
	mx_strcat.c \
	mx_strcmp.c \
	mx_strcpy.c \
	mx_strdel.c \
	mx_strdup.c \
	mx_strjoin.c \
	mx_strlen.c \
	mx_strncpy.c \
	mx_strndup.c \
	mx_strnew.c \
	mx_strsplit.c \
	mx_strstr.c \
	mx_strtrim.c \
	mx_swap_char.c \
	mx_ustrlen.c \
	mx_whitespace.c \
	mx_printerr.c \
	mx_print_charerr.c \
	mx_strncmp.c \
	mx_count_arr_el.c \
	mx_free_void_arr.c \
	mx_numlen.c \
	mx_tolower.c \
	mx_toupper.c \
	mx_str_tolower.c \
		
OBJS = $(addprefix $(OBJD)/, $(SRC:%.c=%.o))

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror
AR = ar rcs
CC = clang

all: $(LIBMX) clean

$(LIBMX) : $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJS): $(OBJD)

$(OBJD):
	@mkdir -p $@

$(OBJD)/%.o: $(SRCD)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@


uninstall:
	@rm -rf $(OBJD)
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJD)

reinstall: uninstall all
