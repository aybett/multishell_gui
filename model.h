#ifndef MODEL_H
#define MODEL_H

#include <semaphore.h>
#include <stddef.h>  // size_t için

#define BUF_SIZE 1024

typedef struct {
    sem_t sem;
    size_t count;
    char buffer[BUF_SIZE];
} SharedMem;

void model_init_shared_memory();
void model_send_message(const char *msg);
char *model_read_message();
void model_execute_command(const char *command, char *output, size_t max_len);

#endif
