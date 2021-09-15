#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/file.h>
#include <math.h>
#include "util_from_others.h"

#define CHILD_NUMBER 8
#define PAIR_NUMBER 8

volatile sig_atomic_t _usr1 = 0;
volatile sig_atomic_t _usr2 = 0;
volatile sig_atomic_t _sig_int = 0;

void init_sig_handlers();
void init_the_sigsets(sigset_t *_to_block, sigset_t *_to_reload);
void handler_usr1(int sig_num);
void handler_usr2(int sig_num);
void create_run_children(pid_t children[CHILD_NUMBER], FILE *filep, sigset_t _to_reload);
void wait_for_children_r1(pid_t children[CHILD_NUMBER], sigset_t _to_reload);
void start_second_round_child(pid_t children[CHILD_NUMBER]);
void child_first_round(FILE *filep, int index, int coor_num);
void wait_for_second_round(sigset_t _to_reload);
float langrange_calculation(float x_n[PAIR_NUMBER], float y_n[PAIR_NUMBER], int coor_num);
void add_float_end(FILE *filep, float calculated_n, int index);
void child_second_round(FILE *filep, int index);
void parent_round(FILE *filep, int round);
float n_th_element(char *str, int index);
void clean_resources(FILE *filep);

int main(int argc, char *argv[]){
	sigset_t _to_block, _to_reload;
	pid_t children[CHILD_NUMBER];
	FILE *filep;

	if(argc != 2){
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}

	filep = fopen(argv[1], "r+");
	if(filep == NULL){
		perror("file open");
		exit(1);
	}

	init_sig_handlers();
	init_the_sigsets(&_to_block, &_to_reload);

	create_run_children(children, filep, _to_reload);

	wait_for_children_r1(children, _to_reload);

	parent_round(filep, 1);

	start_second_round_child(children);

	while(wait(NULL)!=-1);

	fflush(filep);
	parent_round(filep, 2);

	if(_sig_int){
		fprintf(stderr, "CTRL+C signal received\n");
	}

	clean_resources(filep);
	return 0;
}

void handler_usr1(int sig_num){
	if(sig_num == SIGUSR1){
		++_usr1;
	}
}

void handler_usr2(int sig_num){
	if(sig_num == SIGUSR2){
		++_usr2;
	}
}

void handler_sig_int(int sig_num){
	if(sig_num == SIGUSR2){
		++_sig_int;
	}
}

void handler_chld(int sig_num){
	int status;
	// pid_t pid;
	if(sig_num == SIGCHLD){
		wait(&status);
		// printf("%ld is dead, with status %d\n", (long)pid, status);
	}
}

void init_sig_handlers(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_usr1;
	sigaction(SIGUSR1, &sa, NULL);

	struct sigaction sa2;
	memset(&sa2, 0, sizeof(sa2));
	sa2.sa_handler = handler_usr2;
	sigaction(SIGUSR2, &sa2, NULL);

	struct sigaction sa3;
	memset(&sa3, 0, sizeof(sa3));
	sa3.sa_handler = handler_sig_int;
	sigaction(SIGINT, &sa3, NULL);
	
	struct sigaction sa4;
	memset(&sa4, 0, sizeof(sa4));
	sa4.sa_handler = handler_chld;
	sigaction(SIGCHLD, &sa4, NULL);

}

void init_the_sigsets(sigset_t *_to_block, sigset_t *_to_reload){
	sigfillset(_to_reload);
	sigdelset(_to_reload, SIGUSR1);
	sigdelset(_to_reload, SIGUSR2);
	sigdelset(_to_reload, SIGCHLD);
	sigdelset(_to_reload, SIGINT);
	//sigemptyset(_to_block);
	sigfillset(_to_block);
	//sigaddset(_to_block, SIGUSR2);
	if(sigprocmask(SIG_BLOCK, _to_block, NULL) == -1){
		perror("proc mask");
		exit(EXIT_FAILURE);
	}
}

void create_run_children(pid_t children[CHILD_NUMBER], FILE *filep, sigset_t _to_reload){
	for(int i=0 ; i<CHILD_NUMBER ; ++i){
		switch((children[i] = fork())){
			case -1:
				perror("fork");
				exit(EXIT_FAILURE);
			case  0:
								
				child_first_round(filep, i, 6);
				
				wait_for_second_round(_to_reload);

				child_second_round(filep, i);

				exit(EXIT_SUCCESS);
			default:
				break;
		}
	}
}

void wait_for_children_r1(pid_t children[CHILD_NUMBER], sigset_t _to_reload){
	for(int i=0 ; i<CHILD_NUMBER ; ++i){
		kill(children[i], SIGUSR2);
		sigsuspend(&_to_reload);
		if(errno != EINTR){
			perror("parent sigsuspend");
			exit(1);
		}
	}
}

void wait_for_second_round(sigset_t _to_reload){
	sigsuspend(&_to_reload);
	if(errno != EINTR){
		perror("parent sigsuspend");
		exit(1);
	}
	
	if(kill(getppid(), SIGUSR1)==-1){
		perror("child kill");
		exit(1);
	}
	
	sigsuspend(&_to_reload);
	if(errno != EINTR){
		perror("parent sigsuspend");
		exit(1);
	}
}

void clean_resources(FILE *filep){
	if(filep != NULL)
		fclose(filep);
}

void start_second_round_child(pid_t children[CHILD_NUMBER]){
	// send signals to start the second round.
	for(int i=0 ; i<CHILD_NUMBER; ++i){
		kill(children[i], SIGUSR2);
	}
}

void child_first_round(FILE *filep, int index, int coor_num){
	struct flock lock;
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK;
	int cur = 0;

	// f(x_n) = y_n
	float x_n[PAIR_NUMBER], y_n[PAIR_NUMBER];
	float calculated_n;
	char buf[BUFSIZ];

	fcntl(filep->_fileno, F_SETLKW, &lock);

	rewind(filep);
	
	for(int i=0 ; i<=(index) ; ++i){
		fgets(buf, BUFSIZ, filep);
	}

	for(int i=0 ; i<PAIR_NUMBER ; ++i){
		sscanf((buf + cur) ,"%f", &x_n[i]);
		while(buf[cur] != ',' &&  buf[cur] != '\n' && buf[cur] != '\0')
			++cur;
		++cur;
		sscanf((buf + cur) ,"%f", &y_n[i]);
		while(buf[cur] != ',' &&  buf[cur] != '\n' && buf[cur] != '\0')
			++cur;
		++cur;
	}

	calculated_n = langrange_calculation(x_n, y_n, coor_num);

	/*
	for(int i=0 ; i<PAIR_NUMBER ; ++i){
		printf("%-5.2f, %-5.2f | ", x_n[i], y_n[i]);
	}
	printf("\n");
	*/

	add_float_end(filep, calculated_n, index);

	lock.l_type = F_UNLCK;
	fcntl(filep->_fileno, F_SETLKW, &lock);

	if(coor_num == 7){
		print_coefficients(x_n, y_n, index);
	}

}

float langrange_calculation(float x_n[PAIR_NUMBER], float y_n[PAIR_NUMBER], int coor_num){
	struct Data *f = (struct Data*)malloc(sizeof(struct Data)*coor_num);
	float temp;
	for(int i=0 ; i<coor_num ; ++i){
		f[i].x = x_n[i];
		f[i].y = y_n[i];	
	}

	temp = interpolate(f, x_n[7], coor_num);
	free(f);
	return temp;
}

void add_float_end(FILE *filep, float calculated_n, int index){
	char bigger_buf[PAIR_NUMBER][BUFSIZ];
	int _size;
	rewind(filep);
	for(int i=0 ; i<PAIR_NUMBER ; ++i){
		fgets(bigger_buf[i], BUFSIZ, filep);
	}

	rewind(filep);
	for (int i=0 ; i<PAIR_NUMBER ; ++i){
		if(index == i){
			_size = strlen(bigger_buf[i]);
			if(bigger_buf[i][_size-1] == '\n')
				bigger_buf[i][_size-1] = '\0'; 
			fprintf(filep, "%s,%.1f\n", bigger_buf[i], calculated_n);
		}
		else{
			fprintf(filep, "%s", bigger_buf[i]);
		}
	}
	fflush(filep);
}

void child_second_round(FILE *filep, int index){
	child_first_round(filep, index, 7);
}

void parent_round(FILE *filep, int round){
	struct flock lock;
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK;
	char buf[BUFSIZ];

	float f_x_7, x_x_7, sum=0.0;

	fcntl(filep->_fileno, F_SETLKW, &lock);

	rewind(filep);
	for(int i=0 ; i<PAIR_NUMBER ; ++i){
		fgets(buf, BUFSIZ, filep);
		f_x_7 = n_th_element(buf, 15);
		x_x_7 = n_th_element(buf, 16+round-1);
		sum += fabs(f_x_7 - x_x_7);
	}

	fprintf(stdout, "Error of polynomial of degree %d: %.1f\n", 4+round, sum/8.0);

	fflush(stdout);
	lock.l_type = F_UNLCK;
	fcntl(filep->_fileno, F_SETLKW, &lock);
}

float n_th_element(char *str, int index){
	float temp;
	for(int i=0 ; i<index && *str != '\0' ;++str){
		if(*str == ',') ++i;
	}
	sscanf(str, "%f", &temp);
	return temp;
}
