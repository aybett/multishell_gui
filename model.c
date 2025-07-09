#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SHM_NAME "/my_shared_mem"
#define BUF_SIZE 1024

typedef struct {
    sem_t sem;
    size_t count;
    char buffer[BUF_SIZE];
} SharedMem;

SharedMem *shm = NULL;

void model_init_shared_memory() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(SharedMem));

    shm = mmap(NULL, sizeof(SharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    sem_init(&shm->sem, 1, 1);
    shm->count = 0;
}

void model_send_message(const char *msg) {
    sem_wait(&shm->sem);
    snprintf(shm->buffer, BUF_SIZE, "%s", msg);
    shm->count++;
    sem_post(&shm->sem);
}

char *model_read_message() {
    static char msg[BUF_SIZE];
    sem_wait(&shm->sem);
    strncpy(msg, shm->buffer, BUF_SIZE);
    sem_post(&shm->sem);
    return msg;
}

void model_execute_command(const char *command, char *output, size_t max_len) {
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        snprintf(output, max_len, "Failed to run command\n");
        return;
    }

    char buffer[128];
    size_t total_len = 0;
    output[0] = '\0';

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        if (total_len + len < max_len) {
            strcat(output, buffer);
            total_len += len;
        } else {
            strncat(output, buffer, max_len - total_len - 1);
            total_len = max_len;
            break;
        }
    }

    int status = pclose(fp);
    if (status == -1) {
        snprintf(output, max_len, "Failed to close command stream\n");
    } else if (status != 0) {
        snprintf(output, max_len, "Command exited with status %d\n", WEXITSTATUS(status));
    }
}
