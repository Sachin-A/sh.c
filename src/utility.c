#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

#define DELIMITERS " \t\r\n\a"

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
	return tokens;
}

void enqueue(struct Queue *history, char *command) {
	struct Node* t = (struct Node*)malloc(sizeof(struct Node));
	t->next = NULL;
	t->command = malloc(strlen(command) + 1);

	strcpy(t->command, command);
	t->command[strlen(t->command) - 1] = '\0';

	if(history->rear == NULL) {
		history->front = history->rear = t;
		return;
	}

	history->rear->next = t;
	history->rear = t;
	history->size++;
}

void dequeue(struct Queue *history) {
	struct Node *t = history->front;

	if(t == NULL) {
		printf("There is nothing to show in history!\n");
		return;
	}
	else if(t->next != NULL) {
		t = t->next;
		free(history->front);
		history->front = t;
	}
	else {
		free(history->front);
		history->front = NULL;
		history->rear = NULL;
	}
	history->size--;
}

void displayHistory(struct Queue *history) {

	struct Node* iterator = history->front;
	int commandNum = 0;

	printf("History\n");

	if(iterator == NULL && history->rear == NULL) {
		printf("There is nothing to show in history!");
		return;
	}
	while(iterator != NULL) {
		printf("[%d]: %s\n", commandNum, iterator->command);
		iterator = iterator->next;
		commandNum++;
	}
}

void recordHistory(struct Queue *history, char *command) {
	if(history->size == 100) {
		dequeue(history);
		enqueue(history, command);
	}
	else {
		enqueue(history, command);
	}
}
