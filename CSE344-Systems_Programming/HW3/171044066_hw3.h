#ifndef _171044066_HW3_H
#define _171044066_HW3_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
#include <signal.h>

void help_usage();
int parse_command_args(int argc, char *argv[]);
int get_line_number(char *file_name);
struct potato* w_push_potato_shm(int max_process);
struct potato* push_potato_shm(int max_process);
int get_line_(char *filename, char fifo_name[BUFSIZ], int index);
void sigint_handler();
int play_game(struct potato *potato_list, int max_process);

struct potato{
	pid_t pid;
	int heat;
	char fifoname[BUFSIZ];
};

int has_potato_or_not;
char *file_with_fifonames;

char *namedsemaphore;

char *name_of_sharedmemory;
sem_t *mutex_sem;

#define BARRIER_NAME "barrier_nameee"
sem_t *barrier;

#define LAST_BARRIER_NAME "last_barrier_nameee"
#define LAST_SEMAPHORE_NAME "last_semaphore_name"
#define COUNT_SHM "count_shm"
sem_t *last_mutex_sem;
sem_t *last_barrier;
void set_last_barrier(int max);

#endif
