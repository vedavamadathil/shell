#include "system.h"

struct args *flags(WINDOW *window, char *line)
{
	struct args *flags = malloc(sizeof(struct args));
	char *word = malloc(sizeof(char) * LINE_BUF_SIZE);
	flags->flags = malloc(sizeof(char) * LINE_BUF_SIZE);
	char *begin = word;
	int letters = 0;
	flags->argc = 0;

	char **start = flags->flags;
	
	if (line == NULL) {
		free(flags);
		return NULL;
	}

	while (*line) {
		if (isspace(*line) && letters > 0) {
			*word = '\0';
			letters = 0;
			
			(*flags->flags) = begin;
			
			word = malloc(sizeof(char) * LINE_BUF_SIZE);
			begin = word;
			(flags->flags)++;
			flags->argc++;
		} else  {
			*(word++) = *line;
			letters++;
		}

		line++;
	}

	if (letters > 0) {
		*word = '\0';
		letters = 0;
		(*flags->flags) = begin;
		flags->argc++;
	}

	flags->flags = start;

	return flags;
}

struct item *parser(WINDOW *window, struct item *root, struct item *curr, char *input)
{
	struct args *cmds = flags(window, input);
	char **tokens = cmds->flags;
	int count = cmds->argc;

	if (count == 0)
		return NULL;

	if (strcmp(tokens[0], "exit") == 0) {
		status = QUIT;
	} else if (strcmp(tokens[0], "mkdir") == 0) {
		if (count > 1)
			mkdir(window, curr, NULL, tokens[1]);
		else
			wprintw(window, "mkdir: missing operand\n");
	} else if (strcmp(tokens[0], "ls") == 0) {
		list_dir(window, curr);
	} else {
		wprintw(window, "%s: command not found\n", tokens[0]);
	}

	return NULL;
}
