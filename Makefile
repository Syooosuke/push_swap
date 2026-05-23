NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I includes -I libft

SRCS_DIR    = srcs
OBJS_DIR    = objs

SRCS        = $(SRCS_DIR)/main.c 

OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

STACK_SRCS  = $(SRCS_DIR)/stack/node_new.c \
              $(SRCS_DIR)/stack/stack_init.c \
              $(SRCS_DIR)/stack/stack_utils.c \
              $(SRCS_DIR)/stack/stack_free.c

OPS_SRCS    = $(SRCS_DIR)/operations/op_swap.c \
              $(SRCS_DIR)/operations/op_push.c \
              $(SRCS_DIR)/operations/op_rotate.c \
              $(SRCS_DIR)/operations/op_reverse.c

SIMPLE_SRCS = $(SRCS_DIR)/algorithims/simple_sort.c

MEDIUM_SRCS = $(SRCS_DIR)/algorithims/medium_sort.c

COMPLEX_SRCS = $(SRCS_DIR)/algorithims/complex_sort.c

SORT_UTILS_SRCS = $(SRCS_DIR)/algorithims/sort_utils.c

DISORDER_SRCS = $(SRCS_DIR)/disorder/compute_disorder.c

STACK_TEST  = tests/stack_test

MEDIUM_TEST = tests/medium_test

COMPLEX_TEST = tests/complex_test

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test_stack: $(STACK_TEST)
	./$(STACK_TEST)

test: test_stack

test_random: $(STACK_TEST)
	bash tests/random_simple_sort.sh

test_medium: $(MEDIUM_TEST)
	./$(MEDIUM_TEST)

test_medium_random: $(MEDIUM_TEST)
	bash tests/random_medium_sort.sh

test_complex: $(COMPLEX_TEST)
	./$(COMPLEX_TEST)

test_complex_random: $(COMPLEX_TEST)
	bash tests/random_complex_sort.sh

$(STACK_TEST): tests/stack_test_main.c $(STACK_SRCS) $(OPS_SRCS) $(SIMPLE_SRCS)
	$(CC) $(CFLAGS) tests/stack_test_main.c $(STACK_SRCS) $(OPS_SRCS) $(SIMPLE_SRCS) -o $(STACK_TEST)

$(MEDIUM_TEST): tests/medium_test_main.c $(STACK_SRCS) $(OPS_SRCS) $(MEDIUM_SRCS) $(SORT_UTILS_SRCS) $(DISORDER_SRCS)
	$(CC) $(CFLAGS) tests/medium_test_main.c $(STACK_SRCS) $(OPS_SRCS) $(MEDIUM_SRCS) $(SORT_UTILS_SRCS) $(DISORDER_SRCS) -o $(MEDIUM_TEST)

$(COMPLEX_TEST): tests/complex_test_main.c $(STACK_SRCS) $(OPS_SRCS) $(COMPLEX_SRCS) $(SORT_UTILS_SRCS) $(DISORDER_SRCS)
	$(CC) $(CFLAGS) tests/complex_test_main.c $(STACK_SRCS) $(OPS_SRCS) $(COMPLEX_SRCS) $(SORT_UTILS_SRCS) $(DISORDER_SRCS) -o $(COMPLEX_TEST)

clean:
	rm -rf $(OBJS_DIR)
	rm -f $(STACK_TEST)
	rm -f $(MEDIUM_TEST)
	rm -f $(COMPLEX_TEST)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test test_complex test_complex_random test_medium test_medium_random test_random test_stack
