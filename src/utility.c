#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utility.h"

void displayPrompt(void) {
	
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("user@sh.c:%s ", cwd);

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
