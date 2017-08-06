#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int main(int argc, char **argv)
{
	struct Queue *history = (struct Queue*)malloc(sizeof(struct Queue));
	history->size = 0;

	printf("Enter username: ");
	char* username = getCommand();
	username[strlen(username) - 1] = '\0';
	
	printf("Enter hostname: ");
	char* hostname = getCommand();
	hostname[strlen(hostname) - 1] = '\0';

	while (1) {

		int childPid;
		char *command, **parsedCommand;

		displayPrompt(username, hostname);

		command = getCommand();

		recordHistory(history, command);

		displayHistory(history);

		parsedCommand = parseCommand(command);

		/*if (checkIfBuiltIn(parsedCommand)) {
			executeShellBuiltIn(parsedCommand);
		} else {
			childPid = fork();
			if (childPid == 0) {
				execvp(parsedCommand);
			} else {
				if (checkIfBackgroundJob(parsedCommand)) {
					recordBackgroundJob(parsedCommand);
				} else {
					waitpid(childPid);
				}
			}
		}*/
	}

	return EXIT_SUCCESS;
}
