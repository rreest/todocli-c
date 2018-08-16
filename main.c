#include <stdio.h>
#include <string.h>

int main(void)
{
	printf("TODO LIST APPLICATION\n");

	char cmd[8];

	while (strcmp(cmd, "q\n") != 0) {
		// Listen to the users input for a command
		fgets(cmd, 8, stdin);
		printf("[debug] cmd: %s", cmd);

		if (strcmp(cmd, "c\n") == 0) {
			printf("Creating new todo\n");
		} else if (strcmp(cmd, "l\n") == 0) {
			printf("Listing all todos\n");
		}
	}

	printf("Exiting... Goodbye!");
	return 0;
}
