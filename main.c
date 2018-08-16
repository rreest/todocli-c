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
void delete_todo();
void delete_todo_nr(long nr);

#define TODO_FNAME "todos.txt"
#define TEMP_FNAME "_todo_temp.txt"

/* Code */

int main(void)
{
	printf("TODO LIST APPLICATION\n");

	char cmd[8];

	while (strcmp(cmd, "q\n") != 0) {
		// Listen to the users input for a command
		fgets(cmd, 8, stdin);

		if (strcmp(cmd, "c\n") == 0) {
			make_new_todo();
		} else if (strcmp(cmd, "l\n") == 0) {
			list_todos();
		} else if (strcmp(cmd, "d\n") == 0) {
			delete_todo();
		}
	}

	printf("Exiting... Goodbye!");
	return 0;
}

/* Make a new to-do. Prompts the user for input. */
void make_new_todo()
{
	char todo_body[64];

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
	FILE *todo_file = fopen(TODO_FNAME, "a+");
	if (todo_file == NULL)
		printf("error: couldn't open todo file for writing");

	fputs(body, todo_file);
	fclose(todo_file);
}

/* Delete a to-do from the list. Prompts the user for input. */
void delete_todo()
{
	long lineno;
	char *line, *endptr;
	size_t len = 0;

	// Ask the user which to-do to delete
	printf("todo to delete: ");
	getline(&line, &len, stdin);
	lineno = strtol(line, &endptr, 10);

	if (lineno < 1) {
		printf("invalid line number");
		return;
	}

	// Delete the to-do
	delete_todo_nr(lineno);

	printf("deleted todo nr. %ld\n", lineno);
}

/* Delete the n-th to-do in the list. */
void delete_todo_nr(long nr)
{
	FILE *temp;
	FILE *todo_file;
	char *line = NULL;
	size_t len = 0;

	temp = fopen(TEMP_FNAME, "w+");
	if (temp == NULL) {
		printf("couldn't open temp file while deleting todo");
		return;
	}

	todo_file = fopen(TODO_FNAME, "r+");
	if (todo_file == NULL) {
		printf("couldn't open todo file while deleting todo");
		fclose(temp);
		return;
	}

	// Copy the todos to the temp file
	while (getline(&line, &len, todo_file) != -1) {
		fputs(line, temp);
	}

	// Reopen the to-do file, clearing contents
	freopen(TODO_FNAME, "w+", todo_file);
	// Reverse the pointer in the temp file back to the beginning of the stream
	rewind(temp);

	int lineno = 0;
	while (getline(&line, &len, temp) != -1) {
		if (++lineno != nr)
			fputs(line, todo_file);
	}

	fclose(todo_file);
	fclose(temp);
	remove(TEMP_FNAME);
}

/* List all to-dos. */
void list_todos()
{
	FILE *todo_file;
	char *line = NULL;
	size_t len = 0;
	int lineno;

	todo_file = fopen(TODO_FNAME, "r");
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
