#include <stdio.h>
#include "search_helper.h"

extern struct arguments_set *parsed_arguments;

int main(int argc, char *argv[]){

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_int_handler;
	sigaction(SIGINT, &sa, NULL);

	if(argc < 2){
		help_to_user();
		return 1;
	}

	init_parsed_arguments();
	fill_parsed_arguments(argc, argv);
	if(check_args()) return 1;

	my_search(parsed_arguments->dir_base_path);
	if(is_sigint()){
		fprintf(stderr, "\nctr+c signal is received, process is terminated!!\n");
	}
	else{
		show_results(parsed_arguments->dir_base_path);
	}

	clean_tree();
	free_parsed_arguments();

	return 0;
}
