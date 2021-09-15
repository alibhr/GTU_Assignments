#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

#define MAX_LINE_LEN 4096
#define STAMP_LEN 32

int _id;
char *_host;
char *_port;
char *_pathToQueryFile;

sig_atomic_t sig_int = 0;
char curr_timestamp[STAMP_LEN];

int parse_arguments(int argc, char *argv[]);
void print_usage(char *exe_name);
void sigint_handler();
void init_signals();
void run_client(char *exe_name);
void handle_queries(int fd);
char *get_timestamp();

#endif
