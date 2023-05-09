# Main Variables
NAME = minishell
FLAGS = -Wall -Wextra -Werror
MAKE = make
ECHO = echo
RM = rm -rf
LIBS_INCLUDE = -I./includes/ -I./readline/include
LIBS = includes
LIBS_PATH = -L${LIBFT_DIR} -l${LIBFT} -L${READLINE_DIR} -l${READLINE}

# Libft Variables
LIBFT = ft
LIBFT_DIR = ./lib${LIBFT}
LIBFT_SRC := ${shell find ${LIBFT_DIR} -name '*.c' -type f}
LIBFT_MAKE = ${LIBFT_DIR}/Makefile
LIBFT_ALL = ${LIBFT_DIR} ${LIBFT_MAKE} ${LIBFT_SRC}

# Readline Variables
READLINE := readline
READLINE_CHECK = ./${READLINE}/
READLINE_DIR = ./${READLINE}/lib
PATH_READLINE := ${addprefix ${shell pwd}/, readline}
DEL_READLINE_LIB = rm -rf readline-lib
READLINE_MAKE_INSTALL = ${MAKE} -C ./readline-lib && ${MAKE} -C ./readline-lib install
CREATE_TMP_READLINE = cp -R readline-main readline-lib
CONFIGURE_READLINE = cd readline-lib && exec ./configure --prefix=${PATH_READLINE}

# Compiled Directories
SRC = src
OBJ = obj
SUBDIRS = main errors here_doc my_exe parsing utils memory make_exe

# Folder Directions
SRC_DIR = ${foreach dir, ${SUBDIRS}, ${addprefix ${SRC}/, ${dir}}}
OBJ_DIR = ${foreach dir, ${SUBDIRS}, ${addprefix ${OBJ}/, ${dir}}}

# File Directions
SRCS = ${foreach dir, ${SRC_DIR}, ${wildcard ${dir}/*.c}}
OBJS = ${subst ${SRC}, ${OBJ}, ${SRCS:.c=.o}}
LIB_DIR = ${foreach dir, ${LIBS}, ${wildcard ${dir}/*.h}}

# Main Part
all : check_readline ${NAME} 
bonus : all

${NAME} : ${LIB_DIR} Makefile ${OBJS} ${SRCS} ${LIBFT_ALL} ${READLINE_CHECK}
	@${MAKE} WAIT_COMPILE_MSG
	@${MAKE} COM_TOUCHES
	@${MAKE} -C ${LIBFT_DIR} all
	@cc ${FLAGS} ${LIBS_INCLUDE} ${LIBS_PATH} ${OBJS} -o ${NAME}
	@cd src/here_doc && mkdir -p tmp
	@${MAKE} DONE_MSG

${OBJ}/%.o : ${SRC}/%.c ${LIB_DIR}
	@mkdir -p ${OBJ} ${OBJ_DIR}
	@cc ${CFLAGS} ${LIBS_INCLUDE} -c $< -o $@

clean :
	@${MAKE} DELETE_OBJ_MSG
	@${MAKE} -C ${LIBFT_DIR} clean
	@${RM} ${OBJ}

fclean : clean
	@${RM} ${READLINE_CHECK}
	@${MAKE} DELETE_PROGRAM_MSG
	@${MAKE} -C ${LIBFT_DIR} fclean
	@${DEL_READLINE_LIB}
	@${RM} ${NAME}

re : fclean 
	@${MAKE} all

# Readline Part
check_readline : Makefile ${READLINE}
	${if ${wildcard ${READLINE}}, \
		@echo > /dev/null, \
		@${MAKE} create_readline \
	}

create_readline : Makefile
	@${MAKE} START_CREATE_READLINE
	@${DEL_READLINE_LIB} && ${CREATE_TMP_READLINE}
	@${MAKE} CREATE_TMP_READ_LINE
	@${MAKE} CONFIGURE_MSG
	@${CONFIGURE_READLINE}
	@${READLINE_MAKE_INSTALL}
	@${MAKE} FINISH_READLINE
	@${DEL_READLINE_LIB}

.PHONY : all clean fclean re bonus readline create_readline check_readline

# ANSI Colors
RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m

# Helper messages
START_CREATE_READLINE :
	@${ECHO} "${BLUE}Start Building the Readline Library!!${RESET}"
CONFIGURE_MSG :
	@${ECHO} "${YELLOW}	!!Attention!!	 ${RESET}"
	@${ECHO} "${YELLOW}The Readline Library is being Configured!!${RESET}"
	@${ECHO} "${YELLOW}Please do not Interrupt the Process!!${RESET}"
	@${ECHO} "${YELLOW}Thank you for your Understanding..${RESET}"
CREATE_TMP_READ_LINE :
	@${ECHO} "${BLUE}Create a Temporary Variable..${RESET}"
FINISH_READLINE :
	@${ECHO} "${GREEN}! Readline Installed !${RESET}"
WAIT_COMPILE_MSG :
	@${ECHO} "${BLUE}Please wait until program compiling..${RESET}"
COM_TOUCHES :
	@${ECHO} "${BLUE}Compilation Finishing Touches${RESET}"
DONE_MSG :
	@${ECHO} "${GREEN}! Minishell is ready !${RESET}"
DELETE_OBJ_MSG :
	@${ECHO} "${RED}Object files deleting..${RESET}"
DELETE_PROGRAM_MSG :
	@${ECHO} "${RED}Readline is deleting..${RESET}"
	@${ECHO} "${RED}Minishell is deleting..${RESET}"
