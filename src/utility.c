#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utility.h"

#define DELIMITERS " \t\r\n\a"

char *shellBuiltInFunctions[] = {
	"history"
};

int (*shellBuiltIns[])(char**) = {
	displayHistory
};

void displayPrompt(char *username, char *hostname) {

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s@%s:%s$ ", username, hostname, cwd);

}

char *getCommand(void) {

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

char **parseCommand(char *command) {

	size_t bufferSize = 64, unitSize = bufferSize;
	char **tokens = malloc(bufferSize * sizeof(char*));
	char *temp = malloc(strlen(command) + 1);
	strcpy(temp, command);
	char *token = strtok(temp, DELIMITERS);
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
	return tokens;
}

void enqueue(struct Queue *list, char *command) {
	struct Node* t = (struct Node*)malloc(sizeof(struct Node));
	t->next = NULL;
	t->command = malloc(strlen(command) + 1);

	strcpy(t->command, command);
	t->command[strlen(t->command) - 1] = '\0';

	if(list->rear == NULL) {
		list->front = list->rear = t;
		return;
	}

	list->rear->next = t;
	list->rear = t;
	list->size++;
}

void dequeue(struct Queue *list) {
	struct Node *t = list->front;

	if(t == NULL) {
		printf("There is nothing to show!\n");
		return;
	}
	else if(t->next != NULL) {
		t = t->next;
		free(list->front);
		list->front = t;
	}
	else {
		free(list->front);
		list->front = NULL;
		list->rear = NULL;
	}
	list->size--;
}

int displayHistory(char** parsedCommand) {

	struct Node* iterator;
	struct Node* rear;
	bool bg = false;

	for(int i = 0; parsedCommand[i] != '\0'; i++) {
		if(strcmp(parsedCommand[i],"bg") == 0) {
			bg = true;
			break;
		}
	}
	if(bg == true) {
		iterator = backgroundJobs->front;
		rear = backgroundJobs->rear;
		printf("Background Jobs\n");

	}
	else {
		iterator = history->front;
		rear = history->rear;
		printf("History\n");
	}
	int commandNum = 0;

	if(iterator == NULL && rear == NULL) {
		printf("There is nothing to show!\n");
		return EXIT_FAILURE;
	}
	while(iterator != NULL) {
		printf("[%d]: %s\n", commandNum, iterator->command);
		iterator = iterator->next;
		commandNum++;
	}
	return EXIT_SUCCESS;
}

void record(struct Queue *list, char *command) {
	if(list->size == 5) {
		dequeue(list);
		enqueue(list, command);
	}
	else {
		enqueue(list, command);
	}
}

int checkIfShellBuiltIn(char* cmd) {
	for(int i = 0; i < (sizeof(shellBuiltInFunctions)/sizeof(char*)); i++) {
		if(strcmp(shellBuiltInFunctions[i], cmd) == 0) {
			return i;
		}
	}
	return -1;
}

int checkIfBackgroundJob(char** parsedCommand) {
	int i;
	for(i = 0; parsedCommand[i] != '\0'; i++) ;
	if (strcmp(parsedCommand[i-1],"&") == 0) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}