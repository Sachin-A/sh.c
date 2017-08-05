#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

#define DELIMITERS " \t\r\n\a"

void displayPrompt(char* username, char* hostname) {

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s@%s:%s$ ", username, hostname, cwd);

}

char* getCommand(void) {

	char *line = malloc(100), *currentPtr = line;
	int c;
	size_t bufferSize = 100, currentBufferSize = bufferSize;

	if(line == NULL) {
		return NULL;
	}

	while(1) {

		c = fgetc(stdin);
		if(c == EOF) {
			break;
		}
		else if(--currentBufferSize == 0) {
			currentBufferSize = bufferSize;
			char *longerLine = realloc(line, bufferSize *= 2);
			if(longerLine == NULL) {
				free(line);
				return NULL;
			}
			else {
				currentPtr = longerLine + (currentPtr - line);
				line = longerLine;
			}
		}
		else {
			*currentPtr = c;
			if(*currentPtr++ == '\n') {
				break;
			}
		}
	}
	*currentPtr = '\0';
	return line;
}

char** parseCommand(char* command) {

	size_t bufferSize = 64, unitSize = bufferSize;
	char **tokens = malloc(bufferSize * sizeof(char*));
	char *token = strtok(command, DELIMITERS);
	int tokenNumber = 0;

	while(token != NULL) {
		tokens[tokenNumber++] = token;
		if(tokenNumber >= bufferSize) {
			bufferSize += unitSize;
			tokens = realloc(tokens, bufferSize * sizeof(char*));
			if(tokens == NULL) {
				return NULL;
			}
		}

		token = strtok(NULL, DELIMITERS);
	}

	tokens[tokenNumber] = NULL;
	for(int i = 0; i <= tokenNumber; i++) {
		printf("%d: %s\n", i, tokens[i]);
	}
	return tokens;
}
