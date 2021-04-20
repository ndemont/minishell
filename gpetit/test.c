#include "../includes/minishell.h"

int main(void)
{
	int fd;
	char buf[1];
	struct termios term;
	struct termios original;

	fd = open("dromadaire.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	tcgetattr(STDIN_FILENO, &original);
	term = original;
	term.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	while (read(STDIN_FILENO, buf, 1) > 0)
	{
		write(STDIN_FILENO, "\n", 1);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
		write(STDIN_FILENO, buf, 1);
		tcgetattr(STDIN_FILENO, &original);
		term = original;
		term.c_lflag &= ~(ECHO);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
	return (0);
}
