NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -I $(INCDIR) -I $(INCLIBDIR) -I $(LIB)

LIB			=	libft
LIBFT		=	$(LIB)/libft.a
INCLIBDIR	=	libft/includes

SRCDIR		=	src
INCDIR		=	inc
OBJDIR		=	obj
PARSDIR		=	src/parsing
BUILTDIR    =   src/builtins
EXECDIR		=	src/exec

BUILT       =   cd utils_cd echo env exit export utils_export unset pwd
EXEC		=	main exec cmd init path pipes free free2 handle_error fds fds_manager loop
SRCPARS		=	tokens is is_fd parser check add add_fd utils envp check_red handle
BUILTS      =   $(addprefix $(BUILTDIR)/, $(addsuffix .c, $(BUILT)))
EXECS		=	$(addprefix $(EXECDIR)/, $(addsuffix .c, $(EXEC)))
SRCS		=	$(addprefix $(PARSDIR)/, $(addsuffix .c, $(SRCPARS)))
OBJS		=	$(addprefix $(OBJDIR)/, $(BUILT:=.o) $(EXEC:=.o) $(SRCPARS:=.o))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "Compilation de $(NAME) terminée."

$(LIBFT):
	@$(MAKE) --quiet -C $(LIB)
	@echo "Libft compilée."

$(OBJDIR)/%.o: $(PARSDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilation de $<"

$(OBJDIR)/%.o: $(BUILTDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilation de $<"

$(OBJDIR)/%.o: $(EXECDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilation de $<"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) --quiet -C $(LIB) clean
	@echo "Nettoyage des fichiers objets."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --quiet -C $(LIB) fclean
	@echo "Nettoyage complet."

re: fclean all

norm:
	@echo "Norminette de $(NAME) dans $(LIB), $(BUILTDIR), $(PARSDIR) $(EXECDIR) et $(INCDIR)..."
	@if norminette $(LIB)/* $(BUILTDIR)/*.c $(PARSDIR)/*.c $(EXECDIR)/*.c $(INCDIR)/*.h | grep -v "OK!" | grep -q "Error!"; then \
		norminette $(LIB)/* $(BUILTDIR)/*.c $(PARSDIR)/*.c $(EXECDIR)/*.c $(INCDIR)/*.h | grep -v "OK!" | \
		while read line; do \
			if echo $$line | grep -q "Error!"; then \
				echo "\033[0;31m$$line\033[0m"; \
			else \
				echo "$$line"; \
			fi; \
		done; \
	else \
		echo "\033[0;32mAll files are norminette friendly !\033[0m"; \
	fi

.PHONY: all clean fclean re norm
