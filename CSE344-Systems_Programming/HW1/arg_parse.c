#include "arg_parse.h"

void warn_to_user(char c);
void is_valid_permissons(char *str);

struct arguments_set *parsed_arguments;

void init_parsed_arguments(){
	parsed_arguments = (struct arguments_set*) malloc(sizeof(struct arguments_set));
	if(parsed_arguments == NULL) fprintf(stderr, "malloc error at init_parsed_arguments\n");
	memset(parsed_arguments, 0, sizeof(struct arguments_set));
}

void fill_parsed_arguments(int argc, char *argv[]){
	char c;
	while((c = getopt (argc, argv, "f:b:t:p:l:w:")) != -1){
		switch(c){
			case 'f':
				parsed_arguments->_f = 1;
				parsed_arguments->file_name = optarg;
				break;
			case 'b':
				parsed_arguments->_b = 1;
				parsed_arguments->file_size = atoi(optarg);
				break;
			case 't':
				parsed_arguments->_t = 1;
				parsed_arguments->file_type = optarg[0];
				break;
			case 'p':
				parsed_arguments->_p = 1;
				is_valid_permissons(optarg);
				parsed_arguments->permissions = optarg;
				break;
			case 'l':
				parsed_arguments->_l = 1;
				parsed_arguments->number_of_link = atoi(optarg);
				break;
			case 'w':
				parsed_arguments->_w = 1;
				parsed_arguments->dir_base_path = optarg;
				break;
			case '?':
				warn_to_user(optopt);
				free_parsed_arguments();
				exit(1);
			default:
				exit(1);
		}
	}

	int index;
	for(index = optind; index < argc; index++){
		fprintf (stderr, "Non-option argument\n");
		free_parsed_arguments();
		exit(1);
	}
}

void warn_to_user(char c){
	char options[] = {'f', 'b', 't', 'p', 'l', 'w'};
	int len_opt = 5;

	int i=0;
	for(i=0 ; i<len_opt ; ++i){
		if(options[i] == c){
			fprintf(stderr, "Option -%c requires an argument.\n", c);
			free_parsed_arguments();
			exit(1);
		}
	}

	fprintf (stderr, "Unknown option `-%c'.\n", c);
}

void is_valid_permissons(char *str){
	if(strlen(str) != 9){
		fprintf(stderr, "invalid permission input, permissons must be 9 character\n");
		exit(1);
	}
}

void help_to_user(){
	fprintf(stderr, "%s%s%s%s%s%s%s%s", 
		"you can use these parameters\n",
		"-f : filename (case insensitive), supporting the following regular expression: +\n",
		"-b : file size (in bytes)\n",
		"-t : file type (d: directory, s: socket, b: block device, c: character device f: regular file, p: pipe, l: symbolic link)\n",
		"-p : permissions, as 9 characters (e.g. ‘rwxr-xr--’)\n",
		"-l: number of links\n",
		"-w: the path in which to search recursively (i.e. across all of its subtrees) (mandatory parameter)\n\n",
		"Example: ./myFind -w targetDirectoryPath -f \"lost+file\" -b 100 -t b\n"
	);
}

void free_parsed_arguments(){
	free(parsed_arguments);
}

int check_args(){
	if(!parsed_arguments->_w){
		fprintf(stderr, "-w is a mandatory parameter\n");
		free_parsed_arguments();
		return 1;
	}
	int cond = 	!parsed_arguments->_f &&
				!parsed_arguments->_b &&
				!parsed_arguments->_t &&
				!parsed_arguments->_p &&
				!parsed_arguments->_l;
	if(cond){
		fprintf(stderr, "There should be at least one search paramater for target file\n");
		help_to_user();
		free_parsed_arguments();
		return 1;
	}
	return 0;
}
