# Main Variables
NAME = minishell
GCC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LIBS = -I./includes/ -I./readline/include
LIBS_DIR = includes

# Compiled directories
SRC = src
OBJ = obj
SUBDIRS = main

# Folder directions
SRC_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(SRC)/, $(dir)))
OBJ_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(OBJ)/, $(dir)))

# File directions
SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.c=.o))
LIB_DIR = $(foreach dir, $(LIBS_DIR), $(wildcard $(dir)/*.h))

# Libft
LIBFT     = ft
LIBFT_DIR = ./lib$(LIBFT)/

# Readline Part
READLINE = readline
READLINE_DIR    = ./readline/lib
READLINE_PATH := $(addprefix $(shell pwd)/, readline)
READLINE_LIB = readline-lib
DEL_READLINE_LIB = rm -rf $(READLINE_LIB)
INSTALL_READLINE = make -C ./$(READLINE_LIB) && make -C ./$(READLINE_LIB) install

# PATH
FT_PATH = -L$(LIBFT_DIR) -l$(LIBFT) -L$(READLINE_DIR) -l$(READLINE)

all: readline $(NAME)
	@echo > /dev/null

bonus: all

readline : Makefile
	@if [ -d $(READLINE) ]; then \
		make READLINE_READY; \
	else \
		make compile_readline; \
	fi

compile_readline : Makefile
	$(DEL_READLINE_LIB) && cp -R readline-main $(READLINE_LIB)
	cd $(READLINE_LIB) && exec ./configure --prefix=${READLINE_PATH}
	$(INSTALL_READLINE) && $(DEL_READLINE_LIB)
	make READLINE_READY

$(NAME) : Makefile $(OBJS) $(LIB_DIR)
	@make WAIT_COMPILE_MSG
	@echo "${GREEN}-> Compiling LIBFT...${RESET}"
	@make -C $(LIBFT_DIR) all
	@$(GCC) -g $(CFLAGS) $(LIBS) $(FT_PATH) $(OBJS) -o $(NAME)
	@make DONE_MSG

$(OBJ)/%.o: $(SRC)/%.c $(LIB_DIR)
	@mkdir -p $(OBJ) $(OBJ_DIR)
	@echo "${YELLOW}Compiling $<${RESET}"
	@$(GCC) $(CFLAGS) $(LIBS) -c $< -o $@

clean : DELETE_OBJ_MSG
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)

fclean : clean DELETE_PROGRAM_MSG
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(READLINE)
	@$(RM) $(NAME)
	
re : fclean all

# Helper messages
READLINE_READY:
	@echo "${GREEN}Readline is Ready!${RESET}"
WAIT_COMPILE_MSG:
	@echo "${YELLOW}Please wait until program compiling...${RESET}"
DONE_MSG:
	@echo "${GREEN}! Minishell is ready !${RESET}"
DELETE_OBJ_MSG:
	@echo "${RED}Object files deleting...${RESET}"
DELETE_PROGRAM_MSG:
	@echo "${RED}! ATTENTION !\nMinishell is deleting...${RESET}"

# ANSI Colors
RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m