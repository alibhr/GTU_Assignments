#include "search_helper.h"

int _comparator(struct stat curr_stat, char *d_name);
char find_file_type(mode_t m);
char* get_permissions(mode_t m);
void sig_int_handler();
void print_the_tree(N_Ary_Node *root, int depth);

extern struct arguments_set *parsed_arguments;

N_Ary_Node *path_tree = NULL;
__sig_atomic_t sigusr1_count = 0;

void my_search(char dir_name[]){

	DIR *curr_dir = NULL;
	struct dirent *curr_dirent=NULL;
	struct stat curr_stat;

	curr_dir = opendir(dir_name);
	if(curr_dir == NULL){
		if(errno == EACCES){
			fprintf(stderr, "permission denied but searching is continue from other files\n");
			fprintf(stderr, "\tpermission denied from this dir: %s\n", dir_name);
		}
		else{
			perror("opendir");
		}
		return;
	}

	while((curr_dirent = readdir(curr_dir))!= NULL){
		if(sigusr1_count){
			closedir(curr_dir);
			return;
		}

		if(strcmp(curr_dirent->d_name,".")!=0 && strcmp(curr_dirent->d_name,"..")!=0){

			int new_size = strlen(curr_dirent->d_name) + strlen(dir_name) + 2;
			char *new_path = (char*)malloc(sizeof(char) * new_size);
			if(new_path == NULL){
				fprintf(stderr, "malloc error at my_search\n");
				closedir(curr_dir);
				return;
			}

			strcpy(new_path, dir_name);
			strcat(new_path, "/");
			strcat(new_path, curr_dirent->d_name);

			lstat(new_path, &curr_stat);

			if(_comparator(curr_stat, curr_dirent->d_name))
				add_element(&path_tree, new_path);
			
			if(S_ISDIR(curr_stat.st_mode)) my_search(new_path);

			free(new_path);
		}
	}

	if(closedir(curr_dir) == -1) perror("closedir");
}

int _comparator(struct stat curr_stat, char *d_name){
	int __f, __b, __t, __p, __l;
	__f = __b = __t = __p = __l = 1;

	if(parsed_arguments->_f) __f = str_eq_reg(parsed_arguments->file_name, d_name);

	if(parsed_arguments->_b) __b = curr_stat.st_size == parsed_arguments->file_size;

	if(parsed_arguments->_t) __t = find_file_type(curr_stat.st_mode) == parsed_arguments->file_type;
	
	if(parsed_arguments->_p){
		char* permissions = get_permissions(curr_stat.st_mode);
		__p = !strcmp(permissions, parsed_arguments->permissions);
		free(permissions);
	}

	if(parsed_arguments->_l) __l = (int)curr_stat.st_nlink == parsed_arguments->number_of_link;

	return __f && __b && __t && __p && __l;
}

char find_file_type(mode_t m){
	if(S_ISDIR(m))  return 'd';
	if(S_ISREG(m))  return 'f';
	if(S_ISCHR(m))  return 'c';
	if(S_ISBLK(m))  return 'b';
	if(S_ISFIFO(m)) return 'p';
	if(S_ISSOCK(m)) return 's';
	if(S_ISLNK(m))  return 'l';

	return '\0';
}

char* get_permissions(mode_t m){
	char *permissions = (char*)malloc(sizeof(char)*10);
	if(permissions == NULL) {
		fprintf(stderr, "malloc error at get_permissions\n");
		return '\0';
	}

	permissions[0] = (m & S_IRUSR) ? 'r': '-';
	permissions[1] = (m & S_IWUSR) ? 'w': '-';
	permissions[2] = (m & S_IXUSR) ? 'x': '-';

	permissions[3] = (m & S_IRGRP) ? 'r': '-';
	permissions[4] = (m & S_IWGRP) ? 'w': '-';
	permissions[5] = (m & S_IXGRP) ? 'x': '-';

	permissions[6] = (m & S_IROTH) ? 'r': '-';
	permissions[7] = (m & S_IWOTH) ? 'w': '-';
	permissions[8] = (m & S_IXOTH) ? 'x': '-';

	permissions[9] = '\0';

	return permissions;
}

void show_results(char *base_dir){
	if(path_tree == NULL){
		fprintf(stderr, "No file found\n");
		return;
	}
	
	int counter=1;
	N_Ary_Node *temp = path_tree;
	
	int i=0;
	for(i=0 ; base_dir[i] != '\0' ; ++i){
		if(base_dir[i] == '/') ++counter;
	}

	for(i=0 ; i<counter ; ++i){
		temp = temp->child;
	}

	fprintf(stdout, "%s\n", base_dir);
	print_the_tree(temp, 1);
}

void print_the_tree(N_Ary_Node *root, int depth){
	if(sigusr1_count){
		fprintf(stderr, "\nctr+c signal is received, process is terminated!!\n");
		clean_tree();
		free_parsed_arguments();
		exit(1);
	}

	if(root == NULL)
		return;

	fprintf(stdout, "|");
	for(int i=0 ; i<depth ; ++i) fprintf(stdout, "--");
	fprintf(stdout, "%s\n", root->filename);


	if(root->child != NULL)
		print_the_tree(root->child, depth+1);

	if(root->next != NULL)
		print_the_tree(root->next, depth);
}

void clean_tree(){
	free_tree(&path_tree);
}

void sig_int_handler(){
	sigusr1_count = 1;
}

int is_sigint(){
	return sigusr1_count;
}
