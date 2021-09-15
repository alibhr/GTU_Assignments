#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
-f : filename (case insensitive), supporting the following regular expression: +
-b : file size (in bytes)
-t : file type (d: directory, s: socket, b: block device, c: character device f: regular file, p: pipe, l: symbolic link)
-p : permissions, as 9 characters (e.g. ‘rwxr-xr--’)
-l: number of links
-w: the path in which to search recursively (i.e. across all of its subtrees)
*/

struct arguments_set{
	int _f, _b, _t, _p, _l, _w;
	char *dir_base_path, *file_name, *permissions;
	int file_size, number_of_link;
	char file_type;
};

void init_parsed_arguments();
void fill_parsed_arguments(int argc, char *argv[]);
void help_to_user();
void free_parsed_arguments();
int check_args();

#endif
