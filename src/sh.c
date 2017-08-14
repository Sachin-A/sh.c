#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utility.h"

struct Queue* history = NULL;
struct Queue* backgroundJobs = NULL;

int main(int argc, char **argv)
{
	if(!history) {
		history = (struct Queue*)malloc(sizeof(struct Queue));
	}
	if(!backgroundJobs) {
		backgroundJobs = (struct Queue*)malloc(sizeof(struct Queue));
	}
	history->size = 0;
	backgroundJobs->size = 0;
	int functionNo;

	printf("Enter username: ");
	char* username = getCommand();
	username[strlen(username) - 1] = '\0';
	
	printf("Enter hostname: ");
	char* hostname = getCommand();
	hostname[strlen(hostname) - 1] = '\0';

	while (1) {

		int childPid, status;
		char *command, **parsedCommand;

		displayPrompt(username, hostname);
		command = getCommand();
		record(history, command);

		parsedCommand = parseCommand(command);

		if ( (functionNo = checkIfShellBuiltIn(parsedCommand[0])) != -1) {
			shellBuiltIns[functionNo](parsedCommand);
		} else {
			childPid = fork();
			if (childPid == 0) {
				if (checkIfBackgroundJob(parsedCommand) == 0) {
					setpgid(0, 0);
				}
				execvp(parsedCommand[0], parsedCommand);
			} else {
				if (checkIfBackgroundJob(parsedCommand) == 0) {
					record(backgroundJobs, command);
				} else {
					waitpid(childPid, &status, WUNTRACED);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
