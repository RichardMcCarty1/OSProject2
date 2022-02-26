#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

struct Queue {
    int front, rear, size;
    unsigned capacity;
    char** array;
};

struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (char**)malloc(queue->capacity * sizeof(char*));
    return queue;
}

int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
 
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
void enqueue(struct Queue* queue, char* line)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = line;
    queue->size = queue->size + 1;
}
 
char* dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    char* line = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return line;
}
 
// Function to get front of queue
char* front(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    return queue->array[queue->front];
}
 
// Function to get rear of queue
char* rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    return queue->array[queue->rear];
}
void readQueue(struct Queue* qu) {
    printf("%s", dequeue(qu));
}
int main(int argc, char *argv[]) {        
    if(argc < 2) {
        printf("Must specify a count of consumer tasks to run\n");
        return -1;
    }
    printf("Number of consumer tasks to run: %d\n", atoi(argv[1]));
    struct Queue* qu = createQueue(1000);
    char *line = NULL;
    size_t length = 0; 
    ssize_t lineSize = 0;
    lineSize = getline(&line, &length, stdin);
    //Stops at EOF
    while(lineSize >= 1) {
        enqueue(qu, line);
        printf("%s", dequeue(qu));
        lineSize = getline(&line, &length, stdin);
    }
    while(!isEmpty(qu)) {
        
    }
    free(line);
    return 0;
}



