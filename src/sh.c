#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

int main(int argc, char **argv)
{
	while (1) {
		
		int childPid;
		char *command, *parsedCommand;

		displayPrompt();

		command = getCommand();

		printf("%s", command);
		
		/*parsedCommand = parseCommand(command);

		recordCommand(parsedCommand);

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
