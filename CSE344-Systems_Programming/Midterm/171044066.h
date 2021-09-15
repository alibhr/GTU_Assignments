#ifndef _171044066_H
#define _171044066_H

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TRUE 1
#define SHM_NAME "shm_name"
#define SHM_BUF_NAME "buf_name"
#define SHM_VACCINATOR "shm_vaccinator"
#define SHM_NAME_SIZ 64

enum { EMPTY=0, FULL_ONES, FULL_TWOS, MUT, CALL_CITIZEN, RESPONSE_CITIZEN, CITIZEN_MUT, MAX_SEM };
enum { ONES=0, TWOS, FILEP, VACCINATED, LAST_VACC, LAST_NURSE, RUN_CITIZEN, CALLED_PID, REMAIN_CITIZEN, MAX_VAC };

struct _vaccinator{
	pid_t pid;
	int doses;
	int index;
};

void parse_args(int argc, char *argv[], int *n, int *v, int *c, int *b, int *t, char **i);
void help_usage(char *exe_name);
int init_sig_handlers();
void sig_int_handler();
int init_semaphores(int max_buf_size);
int init_buffer(char *inputfilepath, int n_citizens, int n_vaccinator);
void run_citizens(int n_citizenz, int time_each_citizen);
void do_citizen(int j, int time_each_citizen);
void run_nurses(int n_nurses);
void do_nurse(int i, int n_nurses);
void run_vaccinators(int n_vaccinators, int limit);
void do_vaccinator(int limit, int i, int n_vaccinators);
void clean_resources();
void handler_usr1();

volatile sig_atomic_t sig_int = 0;
volatile sig_atomic_t sig_usr1 = 0;

sem_t full_ones;
sem_t empty;
sem_t full_twos;
sem_t mut;

sem_t call_citizen;
sem_t response_citizen;
sem_t citizen_mut;

sem_t *all_sems;
int *buff;

sigset_t old;

struct _vaccinator *vaccs; 
pid_t *citizen_pids;

int is_child=0;

#endif
