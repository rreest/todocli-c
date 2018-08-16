/*
 * The coziest to-do console application on our blue planet.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Declarations */
void make_new_todo();
void list_todos();
void save_todo(char[]);

/* Code */

int main(void)
{
	printf("TODO LIST APPLICATION\n");

	char cmd[8];

	while (strcmp(cmd, "q\n") != 0) {
		// Listen to the users input for a command
		fgets(cmd, 8, stdin);
		printf("[debug] cmd: %s", cmd);

		if (strcmp(cmd, "c\n") == 0) {
			make_new_todo();
		} else if (strcmp(cmd, "l\n") == 0) {
			list_todos();
		}
	}

	printf("Exiting... Goodbye!");
	return 0;
}

/* Make a new to-do. Prompts the user for input. */
void make_new_todo()
{
	char todo_body[64];

	printf("[debug] creating new todo\n");

	// Get to-do content from user
	printf("new todo: ");
	fgets(todo_body, 64, stdin);

	// Save it
	save_todo(todo_body);

	printf("saved!\n");
}

/* Save a to-do persistently. */
void save_todo(char body[])
{
	FILE *todo_file = fopen("todos.txt", "a+");
	if (todo_file == NULL)
		printf("error: couldn't open todo file for writing");

	fputs(body, todo_file);
	fclose(todo_file);
}

/* List all to-dos. */
void list_todos()
{
	FILE *todo_file;
	char *line = NULL;
	size_t len = 0;
	int lineno;

	printf("[debug] listing all todos\n");

	todo_file = fopen("todos.txt", "r");
	if (todo_file == NULL) {
		printf("couldn't open todo file for reading");
		return;
	}

	// Print all to-do lines
	lineno = 1;
	while (getline(&line, &len, todo_file) != -1) {
		printf("%d: %s", lineno, line);
		lineno++;
	}

	// Cleanup
	fclose(todo_file);
	if (line)
		free(line);
}
