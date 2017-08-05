#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int main(int argc, char **argv)
{
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

		printf("Command: %s", command);
		
		parsedCommand = parseCommand(command);

		/*recordCommand(Command);

		if (checkIfBuiltIn(parsedCommand)) {
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
