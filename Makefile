#Colors------------------------------------------------------------
#\033[38;2;255;0;0m 38;2 indicates 24-bit color mode.
#                   255;0;0 amount of red, green, and blue
CYAN = \033[0;96m
ORANGE = \033[38;2;255;146;3m
RED = \033[38;2;255;0;0m
GREEN = \033[38;2;0;255;0m
PINK = \033[38;2;255;55;255m
L_VIOLET = \033[38;2;171;0;205m
VIOLET = \033[38;2;154;0;255m
RESET = \033[0m
#------------------------------------------------------------------

#Emojis-------------------------
EMOJI_HAPPY := \xF0\x9F\x98\x83
EMOJI_SAD := \xF0\x9F\x98\xA2
EMOJI_CELEBRATE := \xF0\x9F\x8E\x89
EMOJI_CLOCK := \xE2\x8F\xB0
EMOJI_ROBOT := \xF0\x9F\xA4\x96
CLEANING_TOOL := \xF0\x9F\xA7\xBD
#--------------------------------

# Binary name
NAME = minishell

# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

# Folders & files
LIBFT = -L libft -lft
HEADER = minishell.h
BUILTINS = cd echo env exit export pwd unset export_utils
ENV = env get_env sort_env shlvl
EXEC = bin builtin exec
MAIN = minishell redir signal
PARSING = line tokens expansions
TOOLS = fd free token type expansions parsing

# Source files
SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

# Object files
OBJ = $(SRC:c=o)

all:header $(NAME)

header:
	@echo "	$(PINK) ______   __  __   ______   __       __     	 __       ______   ______  ______  ______   	"$(RESET)
	@echo "	$(PINK)/\  ___\ /\ \_\ \ /\  ___\ /\ \     /\ \    	/\ \     /\  __ \ /\  == \/\  ___\/\___  \  	"$(RESET)
	@echo "	$(PINK)\ \___  \\ \  __ \\ \  __\ \ \ \____\ \ \____\ \ \____\ \ \/\ \\ \  _-/\ \  __\\/_/  /__ 	"$(RESET)
	@echo "	$(PINK) \/\_____\\ \_\ \_\\ \_____\\ \_____\\ \_____\\ \_____\\ \_____\\ \_\   \ \_____\/\_____\	"$(RESET)
	@echo "	$(PINK)  \/_____/ \/_/\/_/ \/_____/ \/_____/ \/_____/ \/_____/ \/_____/ \/_/    \/_____/\/_____/	"$(RESET)
	@echo "	$(PINK)                                                                                         	"$(RESET)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/
	@echo "$(EMOJI_CLOCK)$(ORANGE)Compiling Minishell...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(EMOJI_HAPPY)$(GREEN)DONE ✓✓$(RESET)"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "$(RESET)$(ORANGE)Cleaning libft...$(RESET)"
	@make clean -C libft/
	@echo "$(RESET)$(ORANGE)Cleaning binaries...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(RESET)$(GREEN)CLEANED ✓✓$(RESET)"

fclean:
	@echo "$(RESET)$(ORANGE)Cleaning object files...$(RESET)"
	@make fclean -C libft/
	@echo "$(RESET)$(ORANGE)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(RESET)$(ORANGE)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RESET)$(GREEN)ALL CLEANED ✓✓$(RESET)"

re: fclean all

test: all
	./minishell

norm:
	@echo "$(CYAN)\nChecking norm for $(NAME)...$(RESET)\n"
	@norminette $(SRC) includes/ && echo "$(EMOJI_HAPPY)$(GREEN)Norm check passed!$(RESET)$(EMOJI_CELEBRATE)" || echo "$(EMOJI_SAD)$(RED)Norm check failed!$(RESET)$(EMOJI_SAD)"
	@echo "$(CYAN)\nChecking norm for LIBFT...$(RESET)\n"
	@norminette $(SRC) libft/ && echo "$(EMOJI_HAPPY)$(GREEN)Norm check passed!$(RESET)$(EMOJI_CELEBRATE)" || echo "$(EMOJI_SAD)$(RED)Norm check failed!$(RESET)$(EMOJI_SAD)"

.PHONY: clean fclean re test norm
