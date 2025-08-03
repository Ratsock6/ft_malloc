NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

SRC_DIR = .
OBJ_DIR = build
LIBFT_DIR = libft

SRCS = malloc.c free.c realloc.c show_alloc_mem.c memory_zone.c utils.c
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -I$(LIBFT_DIR)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(NAME) symlink

$(NAME): $(OBJ_DIR) $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LIBFT_DIR)/libft.a

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

symlink:
	ln -sf $(NAME) $(LINK)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(LINK)

re: fclean all
