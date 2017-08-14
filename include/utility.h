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
extern struct Queue *backgroundJobs;

void displayPrompt(char*, char*);
char* getCommand(void);
char** parseCommand(char*);
void enqueue(struct Queue*, char*);
void dequeue(struct Queue*);
int displayHistory(char**);
void record(struct Queue*, char*);
int checkIfShellBuiltIn(char*);
int checkIfBackgroundJob(char**);

#endif // UTILITY_H_
