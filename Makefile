NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Source directories
SRCDIR = .
UTILSDIR = utils

# Source files
SRCS = $(SRCDIR)/pipex.c $(SRCDIR)/pipex_utils.c \
       $(UTILSDIR)/ft_split.c $(UTILSDIR)/ft_strdup.c $(UTILSDIR)/ft_strjoin.c \
       $(UTILSDIR)/ft_strlcat.c $(UTILSDIR)/ft_strlcpy.c $(UTILSDIR)/ft_strlen.c \
       $(UTILSDIR)/ft_strnstr.c $(UTILSDIR)/ft_substr.c

# Object files
OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re