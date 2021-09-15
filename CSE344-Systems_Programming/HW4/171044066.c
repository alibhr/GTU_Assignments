#include "171044066.h"

int main(int argc, char *argv[]){
	int total_hw_done = 0;
	int total_cost=0;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	if(argc != 4){ print_usage(argv[EXE_NAME]); }
	remaining_money = atoi(argv[MONEY]);
	student_list_size=get_line_count(argv[STUDENTS_PATH]);

	init_semaphores();

	sem_wait(p_is_end);
	is_end = 0;
	sem_post(p_is_end);

	sem_wait(p_is_eof);
	is_eof = 0;
	sem_post(p_is_eof);

	start_students_for_hire(argv[STUDENTS_PATH]);

	start_cheater_student((void*)argv[HW_PATH]);
	
	select_student_for_hire();

	sem_wait(is_cheater_done);

	sem_wait(barrier);

	if(sig_int){
		for(int i=0 ; i<student_list_size ; ++i){
			pthread_kill(tid_list[i], SIGINT);
		}
	}

	for(int i=0 ; i<student_list_size ; ++i){
		pthread_join(tid_list[i], NULL);
	}

	fprintf(stdout, "Homeworks solved and money made by the students:\n");
	for(int i=0 ; i<student_list_size ; ++i){
		fprintf(stdout, "%s %d %d\n", student_list[i]->name, student_list[i]->hw_done, student_list[i]->hw_done * student_list[i]->cost);
		total_hw_done += student_list[i]->hw_done;
		total_cost += (student_list[i]->hw_done * student_list[i]->cost);
	}
	fprintf(stdout, "Total cost for %d homeworks %dTL\n", total_hw_done, total_cost);
	fprintf(stdout, "Money left at G’s account: %dTL\n", remaining_money);

	destroy_semaphores();
	free_queue(&hw_list);
	free_student_list();
	free(tid_list);

	if(sig_int){
		exit(EXIT_FAILURE);
	}

	return 0;
}

void sigint_handler(){
	sig_int = 1;
}

void print_usage(char *exe_name){
	fprintf(stderr, "usage: %s homeworkFilePath studentsFilePath money(integer)\n", exe_name);

	fprintf(stderr, "%s%s%s",
		"homeworkFilePath: contains the homeworks of h and her priorities\n",
		"studentsFilePath: contains the names and properties of the students-for-hire\n",
		"money(integer): represens h’s money\n"
	);
	destroy_semaphores();
	exit(EXIT_FAILURE);
}

void init_semaphores(){
	protect_hw_list = (sem_t*)malloc(sizeof(sem_t));
	sem_init(protect_hw_list, 0, 1);

	p_remain_money = (sem_t*)malloc(sizeof(sem_t));
	sem_init(p_remain_money, 0, 1);
	
	is_cheater_done = (sem_t*)malloc(sizeof(sem_t));
	sem_init(is_cheater_done, 0, 0);

	p_student_list = (sem_t*)malloc(sizeof(sem_t));
	sem_init(p_student_list, 0, 1);

	student_number = (sem_t*)malloc(sizeof(sem_t));
	sem_init(student_number, 0, 0);

	p_is_eof = (sem_t*)malloc(sizeof(sem_t));
	sem_init(p_is_eof, 0, 1);

	hw_list_size = (sem_t*)malloc(sizeof(sem_t));
	sem_init(hw_list_size, 0, 0);

	p_is_end = (sem_t*)malloc(sizeof(sem_t));
	sem_init(p_is_end, 0, 1);

	is_printed = (sem_t*)malloc(sizeof(sem_t));
	sem_init(is_printed, 0, 0);

	barrier = (sem_t*)malloc(sizeof(sem_t));
	sem_init(barrier, 0, 0);
}

int get_line_count(char *filename){
	FILE *filep = fopen(filename,"r");
	char buf[BUFFER_SIZE];
	int counter=0;

	if(filep==NULL){
		fprintf(stderr, "file error: %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while(fgets(buf, BUFFER_SIZE, filep)){
		if(*buf != '\n')
			++counter;
	}

	lseek(filep->_fileno, 0, SEEK_SET);

	fclose(filep);
	return counter;
}

void destroy_semaphores(){
	//sem_close(protect_hw_list);
	sem_destroy(protect_hw_list);
	if(protect_hw_list != NULL){
		free(protect_hw_list);
		//protect_hw_list=NULL;
	}

	//sem_close(p_remain_money);
	sem_destroy(p_remain_money);
	if(p_remain_money != NULL){
		free(p_remain_money);
		//p_remain_money = NULL;
	}

	//sem_close(is_cheater_done);
	sem_destroy(is_cheater_done);
	if(is_cheater_done != NULL){
		free(is_cheater_done);
		//is_cheater_done = NULL;
	}

	//sem_close(p_student_list);
	sem_destroy(p_student_list);
	if(p_student_list != NULL){
		free(p_student_list);
		//p_student_list = NULL;
	}

	//sem_close(student_number);
	sem_destroy(student_number);
	if(student_number != NULL){
		free(student_number);
		//student_number = NULL;
	}

	//sem_close(p_is_eof);
	sem_destroy(p_is_eof);
	if(p_is_eof != NULL){
		free(p_is_eof);
		//p_is_eof = NULL;
	}

	//sem_close(hw_list_size);
	sem_destroy(hw_list_size);
	if(hw_list_size != NULL){
		free(hw_list_size);
		//hw_list_size = NULL;
	}

	//sem_close(p_is_end);
	sem_destroy(p_is_end);
	if(p_is_end != NULL){
		free(p_is_end);
		//p_is_end = NULL;
	}

	//sem_close(is_printed);
	sem_destroy(is_printed);
	if(is_printed != NULL){
		free(is_printed);
		//is_printed = NULL;
	}

	//sem_close(barrier);
	sem_destroy(barrier);
	if(barrier != NULL){
		free(barrier);
		//barrier = NULL;
	}
}

void start_cheater_student(void *arg){
	int error;
	pthread_t tid;
	pthread_attr_t attr;

	if((error = pthread_attr_init(&attr)) != 0){
		fprintf(stderr, "pthread_attr_init %s\n", strerror(error));
		exit(EXIT_FAILURE);
	}
	if((error = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) != 0){
		fprintf(stderr, "pthread_attr_setdetachstate %s\n", strerror(error));
		pthread_attr_destroy(&attr);
		exit(EXIT_FAILURE);
	}

	if((error = pthread_create(&tid, &attr, cheater_student, arg)) != 0){
		fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
		pthread_attr_destroy(&attr);
		exit(EXIT_FAILURE);
	}

	if((error=pthread_attr_destroy(&attr)) != 0){
		fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
		exit(EXIT_FAILURE);
	}
}

void* cheater_student(void *arg){
	int fd;
	char homework='-';
	int is_n_eof = 1;

	fd = open((char*)arg, O_RDONLY);
	if(fd == -1){
		fprintf(stderr, "cheater student file error: %s\n", (char*)arg);
		sem_post(is_cheater_done);
		sem_wait(p_is_eof);
		is_eof = 1;
		sem_post(p_is_eof);

		sem_post(hw_list_size);
		return (void*) -1;
	}

	while(TRUE){

		if(sig_int){
			close(fd);

			sem_post(is_cheater_done);

			sem_wait(p_is_eof);
			is_eof = 1;
			sem_post(p_is_eof);
			sem_post(hw_list_size);
			return NULL;
		}

		is_n_eof = read(fd, &homework, sizeof(char));

		if(is_n_eof == 0) {
			fprintf(stdout, "H has no other homeworks, terminating.\n");
			close(fd);
			sem_post(is_cheater_done);

			sem_wait(p_is_eof);
			is_eof = 1;
			sem_post(p_is_eof);

			sem_post(hw_list_size);
			return NULL;
		}

		sem_wait(p_is_end);
		if(is_end){
			fprintf(stdout, "H has no more money for homeworks, terminating.\n");
			close(fd);

			sem_post(is_cheater_done);
			sem_post(p_is_end);

			sem_wait(p_is_eof);
			is_eof = 1;
			sem_post(p_is_eof);
			sem_post(hw_list_size);
			return NULL;
		}
		sem_post(p_is_end);

		switch(homework){
			case 'C':
			case 'S':
			case 'Q':
				sem_wait(p_remain_money);
				fprintf(stdout, "H has a new homework %c; remaining mony is %dTL\n", homework, remaining_money);
				sem_post(p_remain_money);
				
				sem_wait(protect_hw_list);
				offer_char(&hw_list, homework);
				sem_post(hw_list_size);
				sem_post(protect_hw_list);
			break;

			default:
			break;
		}
	}
}

void start_students_for_hire(char *studentsFilePath){
	FILE *filep=NULL;
	char buf[BUFFER_SIZE];
	struct student_for_hire *s;

	tid_list = (pthread_t*)malloc(sizeof(pthread_t) * student_list_size);

	student_list = (struct student_for_hire **)malloc(sizeof(struct student_for_hire *) * student_list_size);
	for(int i=0 ; i<student_list_size ; ++i) student_list[i] = NULL;

	filep = fopen(studentsFilePath, "r");

	if(filep == NULL){
		fprintf(stderr, "file error: %s\n", studentsFilePath);
		exit(EXIT_FAILURE);
	}

	lseek(filep->_fileno, 0, SEEK_SET);

	for(int i=0 ; i<student_list_size && fgets(buf, BUFFER_SIZE, filep) != 0 ; ++i){
		s = (struct student_for_hire*) malloc(sizeof(struct student_for_hire));
		sscanf(buf, "%s%d%d%d", s->name, &s->quality, &s->speed, &s->cost);
		s->available = 1;
		s->homework = '-';
		s->hw_done = 0;
		init_student_sem(&s->mut);
		
		sem_wait(p_student_list);
		student_list[i] = s;
		sem_post(p_student_list);
	}

	for(int i=0 ; i<student_list_size ; ++i){
		start_a_thread(i);
	}

	sem_wait(p_student_list);
	fprintf(stdout, "%d students-for-hire threads have been created.\n", student_list_size);
	for(int i=0 ; i<student_list_size ; ++i){
		s = student_list[i];

		fprintf(stdout, "%-15s%-10d %-10d %-10d\n",
			s->name,
			s->quality,
			s->speed,
			s->cost
		);
	}
	sem_post(p_student_list);

	fclose(filep);
	filep=NULL;
}

void start_a_thread(int i){
	pthread_t tid;

	sem_wait(p_student_list);
	pthread_create(&tid, NULL, do_student, student_list[i]);
	sem_post(p_student_list);

	tid_list[i] = tid;
}

void* do_student(void *arg){
	struct student_for_hire *self = ((struct student_for_hire*)(arg));
	sem_post(student_number);
	
	while(TRUE){
		if(sig_int){
			return NULL;
		}

		fprintf(stdout, "%s is waiting for homework\n", self->name);
		fflush(stdout);
		sem_wait(self->mut);

		if(sig_int){
			return NULL;
		}

		sem_wait(p_is_end);
		if(is_end){
			sem_post(p_is_end);
			return NULL;
		}
		sem_post(p_is_end);

		sem_wait(p_student_list);
		sem_wait(p_remain_money);
		++(self->hw_done);
		fprintf(stdout, "%s is solving homework %c for %d, H has %dTL left.\n", self->name, self->homework, self->cost, remaining_money);
		fflush(stdout);
		sem_post(p_remain_money);
		sem_post(p_student_list);

		//be sure that the solving message is printed.
		sem_post(is_printed);

		if(self->speed < 6) sleep(6 - self->speed);

		sem_wait(p_student_list);
		self->available = 1;
		sem_post(p_student_list);

		sem_post(student_number);
	}

	return NULL;
}

void init_student_sem(sem_t **sem){
	*sem = (sem_t*)malloc(sizeof(sem_t));
	sem_init(*sem, 0, 0);
}

void free_student_list(){
	for(int i=0 ; i<student_list_size ; ++i){
		if(student_list[i] != NULL) {
			sem_close(student_list[i]->mut);
			sem_destroy(student_list[i]->mut);
			free(student_list[i]->mut);

			free(student_list[i]);
		}
	}

	if(student_list != NULL) free(student_list);
}

void select_student_for_hire(){
	char homework;
	struct student_for_hire* student=NULL;

	while(TRUE){
		sem_wait(student_number);

		sem_wait(hw_list_size);
		
		if(sig_int){
			fprintf(stdout, "Termination signal received, closing.\n");
			sem_wait(p_is_end);
			is_end = 1;
			sem_post(p_is_end);

			for(int i=0 ; i<student_list_size ; ++i){
				sem_wait(p_student_list);	
				sem_post(student_list[i]->mut);
				sem_post(p_student_list);
			}
			sem_post(barrier);
			return;
		}

		sem_wait(p_is_eof);
		if(is_eof && is_empty(&hw_list)){
			fprintf(stdout, "No more homeworks left or coming in, closing.\n");
			sem_wait(p_is_end);
			is_end = 1;
			sem_post(p_is_end);

			for(int i=0 ; i<student_list_size ; ++i){
				sem_wait(p_student_list);	
				sem_post(student_list[i]->mut);
				sem_post(p_student_list);
			}
			sem_post(barrier);
			return;
		}
		sem_post(p_is_eof);

		sem_wait(protect_hw_list);
		homework = poll_char(&hw_list);
		sem_post(protect_hw_list);

		/*
		sem_wait(p_student_list);
		for(int i=0 ; i<student_list_size ; ++i){
			printf("%s %d\n", student_list[i]->name, student_list[i]->available);
		}
		sem_post(p_student_list);
		*/

		switch(homework){
			case 'C':
				sem_wait(p_student_list);
				student = find_max(student_list, cheapest);
				sem_post(p_student_list);
			break;

			case 'S':
				sem_wait(p_student_list);
				student = find_max(student_list, fastest);
				sem_post(p_student_list);
			break;

			case 'Q':
				sem_wait(p_student_list);
				student = find_max(student_list, max_quality);
				sem_post(p_student_list);
			break;

			default:
				continue;
			break;
		}

		sem_wait(p_remain_money);
		if(remaining_money < student->cost){
			fprintf(stdout, "Money is over, closing.\n");
			sem_wait(p_is_end);
			is_end = 1;
			sem_post(p_is_end);

			sem_post(p_remain_money);

			for(int i=0 ; i<student_list_size ; ++i){
				sem_post(student_list[i]->mut);
			}
			sem_post(barrier);
			return;
		}
		remaining_money -= student->cost;
		sem_post(p_remain_money);
		
		sem_wait(p_student_list);
		student->homework = homework;
		student->available = 0;
		sem_post(student->mut);
		sem_post(p_student_list);

		//be sure that the solving message is printed.
		sem_wait(is_printed);
	}
}

struct student_for_hire* find_max(struct student_for_hire **list, int (*compare)(struct student_for_hire *, struct student_for_hire *)){
	struct student_for_hire max_e;
	int ret = 0;
	
	for(int i=0 ; i<student_list_size ; ++i){
		if(student_list[i]->available){
			max_e = *(list[i]);
			ret = i;
			break;
		}
	}
	
	for(int i=0 ; i<student_list_size ; ++i){
		if(compare(&max_e, list[i]) < 0 && list[i]->available){
			max_e = *(list[i]);
			ret = i;
		}
	}
	return list[ret];
}

int fastest(struct student_for_hire *s1, struct student_for_hire *s2){
	return (s1->speed) - (s2->speed);
}

int cheapest(struct student_for_hire *s1, struct student_for_hire *s2){
	return (s2->cost) - (s1->cost);
}

int max_quality(struct student_for_hire *s1, struct student_for_hire *s2){
	return (s1->quality) - (s2->quality);
}
