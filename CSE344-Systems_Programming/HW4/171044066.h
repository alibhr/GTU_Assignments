#ifndef _171044066_H
#define _171044066_H

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>

#include "queue.h"

#define TRUE 1
#define BUFFER_SIZE 64

struct student_for_hire{
	char name[BUFFER_SIZE];
	int quality;
	int speed;
	int cost;
	int available;
	sem_t *mut;
	char homework;
	int hw_done;
};

void sigint_handler();

void print_usage(char *exe_name);

int get_line_count(char *filename);

void init_semaphores();
void destroy_semaphores();

void start_cheater_student(void *arg);
void* cheater_student(void *arg);

void start_students_for_hire(char *studentsFilePath);
void init_student_sem(sem_t **sem);
void start_a_thread(int i);
void* do_student(void *arg);
void free_student_list();
void select_student_for_hire();

struct student_for_hire* find_max(struct student_for_hire **list, int (*compare)(struct student_for_hire *, struct student_for_hire *));
int fastest(struct student_for_hire *s1, struct student_for_hire *s2);
int cheapest(struct student_for_hire *s1, struct student_for_hire *s2);
int max_quality(struct student_for_hire *s1, struct student_for_hire *s2);

enum { EXE_NAME=0, HW_PATH, STUDENTS_PATH, MONEY };

Queue *hw_list=NULL;
sem_t *protect_hw_list=NULL;
sem_t *hw_list_size=NULL;

sem_t *p_remain_money=NULL;
int remaining_money;

sem_t *is_cheater_done=NULL;

sem_t *p_student_list=NULL;
int student_list_size=0;
struct student_for_hire *(*student_list)=NULL;

pthread_t *tid_list;

sem_t *student_number;

int is_eof=0;
sem_t *p_is_eof;

int is_end;
sem_t *p_is_end;

sem_t *is_printed;

sig_atomic_t sig_int = 0;

sem_t *barrier;

#endif
