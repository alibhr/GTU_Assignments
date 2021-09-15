#ifndef SEARCH_HELPER_H
#define SEARCH_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "arg_parse.h"
#include "reg_comparator.h"
#include "path_tree.h"

void my_search(char dir_name[]);
void show_results(char *base_dir);
void clean_tree();
void sig_int_handler();
int is_sigint();

#endif
