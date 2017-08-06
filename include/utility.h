#ifndef UTILITY_H_
#define UTILITY_H_

struct Node {

	char *command;
	struct Node *next;
};

struct Queue {

	struct Node *front;
	struct Node *rear;
	int size;
};

void displayPrompt(char*, char*);
char* getCommand(void);
char** parseCommand(char*);
void enqueue(struct Queue* history, char* command);
void dequeue(struct Queue* history);
void displayHistory(struct Queue* history);
void recordHistory(struct Queue* history, char* command);

#endif // UTILITY_H_
