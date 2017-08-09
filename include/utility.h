#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdbool.h>

struct Node {

	char *command;
	struct Node *next;
};
struct Queue {

	struct Node *front;
	struct Node *rear;
	int size;
};
extern char *shellBuiltInFunctions[];
extern int (*shellBuiltIns[])(char**);
extern struct Queue *history;

void displayPrompt(char*, char*);
char* getCommand(void);
char** parseCommand(char*);
void enqueue(struct Queue*, char*);
void dequeue(struct Queue*);
int displayHistory(char**);
void recordHistory(struct Queue*, char*);
int checkIfShellBuiltIn(char*);

#endif // UTILITY_H_
