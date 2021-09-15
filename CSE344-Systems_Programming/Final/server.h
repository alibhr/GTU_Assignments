#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <semaphore.h>

#include "queue.h"

#define EVER ;;
#define TRUE 1
#define MAX_LINE_LEN 4096

#define BD_MAX_CLOSE 8192
#define DEV_PATH "/dev/null"

#define SEM_NAME "against_double_instantiation"
sem_t *against_double_instantiation;

volatile sig_atomic_t sig_int = 0;
volatile sig_atomic_t sig_term = 0;
volatile sig_atomic_t sig_hub = 0;

uint16_t _port;
char *_pathToLogFile;
int _poolSize;
char *_datasetPath;

Queue *request_fd_queue = NULL;
pthread_mutex_t m_queue;
pthread_cond_t ok_to_poll;
int len_of_queue = 0;

pthread_mutex_t m_available;
pthread_cond_t c_available;
int i_available;
void init_the_available();

pthread_mutex_t m_barrier;
pthread_cond_t c_barrier;
int i_barrier;
void init_the_barrier();

// Test //
pthread_mutex_t m_counter;
int counter = 0;
void init_counter();
//////////

pthread_t *tids;
int *worker_ids;

FILE *log_filep = NULL;

int AR=0;   // Number of active reader
int AW=0;   // Number of active writer
int WR=0;   // Number of waiting reader
int WW=0;   // Number of waiting writer
pthread_cond_t okToRead;
pthread_cond_t okToWrite;
pthread_mutex_t lock;
void init_lock_mutex();

#define BUF_SIZE 127

// memory operations //
char ***csv_table = NULL;
int row_len;
int col_len;

int find_col_len(char *filename);
int find_row_len(char *filename);
int create_the_table(char *filename);
int str_replace(char *str, char old_char, char new_char);
void free_table();
void print_table();
void parse_query(char *query, int *is_select, int *is_selected);
void handle_query(char *query, int fd ,int worker_id);
char comma_or_space(char *str);
int column_index(char *str);
///////////////////////

void sigint_handler();
void init_signals();
void create_pool_threads();
void sleep_half_second();
void print_usage(char *exe_name);
int parse_arguments(int argc, char *argv[]);
void run_the_server();
void clean_garbage();
void server_main_thread(int fd, struct sockaddr_in addr);
void* run_helper_threads(void *arg);
void do_helper_thread(int worker_id);
void init_the_mutex();
char *get_timestamp();

void become_daemon();
void sig_int_handler();
void sig_term_handler();
void sig_hub_handler();

int is_double_instantiation();

#endif
