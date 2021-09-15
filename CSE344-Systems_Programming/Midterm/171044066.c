#include "171044066.h"

int main(int argc, char *argv[]){
	int n_nurses;
	int n_vaccinators;
	int n_citizens;
	int buffer_size;
	int time_each_citizen;
	char *inputfilepath;
	atexit(clean_resources);

	sigset_t my_mask;
	if(sigemptyset(&my_mask)){
		perror("sigemptyset");
		exit(EXIT_FAILURE);
	}

	if(sigaddset(&my_mask, SIGUSR1)){
		perror("sigaddset");
		exit(EXIT_FAILURE);
	}

	if(sigprocmask(SIG_BLOCK, &my_mask, &old)){
		perror("sigprocmask");
		exit(EXIT_FAILURE);
	}

	parse_args(
		argc,
		argv,
		&n_nurses,
		&n_vaccinators,
		&n_citizens,
		&buffer_size,
		&time_each_citizen,
		&inputfilepath
	);
	citizen_pids = (pid_t*) malloc (sizeof(pid_t) * n_citizens);
	if(citizen_pids == NULL){
		fprintf(stderr, "citizen_pids malloc error\n");
		exit(EXIT_FAILURE);
	}
	
	//TODO: check for file validity

	fprintf(stdout, "Welcome to the GTU344 clinic. Number of citizens to vaccinate c=%d with t=%d doses.\n", n_citizens, time_each_citizen);

	if(init_sig_handlers()==-1){
		exit(EXIT_FAILURE);
	}

	if(init_semaphores(buffer_size)==-1){
		exit(EXIT_FAILURE);
	}

	if(init_buffer(inputfilepath, n_citizens, n_vaccinators)==-1){
		exit(EXIT_FAILURE);	
	}

	if(sig_int){
		fprintf(stderr, "CTRL+C signal is received");
		exit(EXIT_FAILURE);
	}

	run_citizens(n_citizens, time_each_citizen);

	if(sig_int){
		fprintf(stderr, "CTRL+C signal is received");
		exit(EXIT_FAILURE);
	}

	run_nurses(n_nurses);

	if(sig_int){
		fprintf(stderr, "CTRL+C signal is received");
		exit(EXIT_FAILURE);
	}
	
	run_vaccinators(n_vaccinators, (time_each_citizen*n_citizens));
	if(sig_int){
		fprintf(stderr, "CTRL+C signal is received");
		exit(EXIT_FAILURE);
	}
	//clean_resources();

	return 0;
}

void parse_args(int argc, char *argv[], int *n, int *v, int *c, int *b, int *t, char **i){
	int a0, a1, a2, a3, a4, a5;
	a0 = a1 = a2 = a3 = a4 = a5 = 1;
	int temp = 0;

	char ch;
	while((ch = getopt(argc, argv, "n:v:c:b:t:i:")) != -1){
		temp = atoi(optarg);
		switch(ch){
			case 'n':
				if(temp >= 2) { *n = temp; }
				else { help_usage(argv[0]); exit(EXIT_FAILURE); }
				a0 = 0;
			break;

			case 'v':
				if(temp >= 2) { *v = temp; }
				else { help_usage(argv[0]); exit(EXIT_FAILURE); }
				a1 = 0;
			break;
			
			case 'c':
				if(temp >= 3) { *c = temp; }
				else { help_usage(argv[0]); exit(EXIT_FAILURE); }
				a2 = 0;
			break;

			case 'b':
				*b = temp;
				a3 = 0;
			break;

			case 't':
				if(temp >= 1) { *t = temp; }
				else { help_usage(argv[0]); exit(EXIT_FAILURE); }
				a4 = 0;
			break;

			case 'i':
				*i = optarg;
				a5 = 0;
			break;
			
			case '?':
				help_usage(argv[0]);
				exit(EXIT_FAILURE);
			break;
		}
	}

	if(a0 || a1 || a2 || a3 || a4 || a5){
		fprintf(stderr, "argument error\n");
		help_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if(*b < ( (*t) * (*c) ) + 1) { help_usage(argv[0]); exit(EXIT_FAILURE); }

}

void help_usage(char *exe_name){
	fprintf(stderr,
		"usage: %s -n 3 -v 2 -c 3 -b 11 -t 3 -i inputfilepath\n",
		exe_name
	);

	fprintf(stderr, "%s%s%s%s%s%s",
		"n >= 2: the number of nurses (integer)\n",
		"v >= 2: the number of vaccinators (integer)\n",
		"c >= 3: the number of citizens (integer)\n",
		"b >= tc+1: size of the buffer (integer)\n",
		"t >= 1: how many times each citizen must receive the 2 shots (integer)\n",
		"i: pathname of the input file\n"
	);
}

int init_sig_handlers(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_int_handler;
	if(sigaction(SIGINT, &sa, NULL)){
		perror("sigaction sigint");
		return -1;
	}

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler_usr1;
	if(sigaction(SIGUSR1, &sa, NULL)){
		perror("sigaction sigusr");
		return -1;
	}
	return 0;
}

void sig_int_handler(){
	if(is_child)
		exit(EXIT_FAILURE);
	else
		sig_int = 1;
}

void handler_usr1(){
	sig_usr1 = 1;
}

int init_semaphores(int max_buf_size){
	int fd;
	struct stat sb;

	char shm_name[SHM_NAME_SIZ];
	sprintf(shm_name, "%ld", (long)getpid());
	strcat(shm_name, SHM_NAME);
	//fprintf(stdout, "shm_name: %s\n", shm_name);

	fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
	if(fd == -1){
		perror("shm_open shm_name");
		return -1;
	}

	if(fstat(fd, &sb) == -1){
		perror("fstat");
		shm_unlink(shm_name);
		close(fd);
		return -1;		
	}

	if(sb.st_size == 0){
		ftruncate(fd, sizeof(sem_t) * MAX_SEM);
	}

	all_sems = (sem_t*)mmap(NULL, sizeof(sem_t) * MAX_SEM, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(all_sems == MAP_FAILED){
		perror("mmap error");
		shm_unlink(shm_name);
		close(fd);
		return -1;
	}

	close(fd);

	if(
		sem_init(&full_ones, 1, 0)			== -1 ||
		sem_init(&empty, 1, max_buf_size)	== -1 ||
		sem_init(&full_twos, 1, 0)			== -1 ||
		sem_init(&mut, 1, 1)				== -1 ||
		sem_init(&call_citizen, 1, 0)		== -1 ||
		sem_init(&response_citizen, 1, 0)	== -1 ||
		sem_init(&citizen_mut, 1, 1)
	){ perror("sem_init"); shm_unlink(shm_name); return -1; }

	all_sems[FULL_ONES] = full_ones;
	all_sems[EMPTY] = empty;
	all_sems[FULL_TWOS] = full_twos;
	all_sems[MUT] = mut;
	all_sems[CALL_CITIZEN] = call_citizen;
	all_sems[RESPONSE_CITIZEN] = response_citizen;
	all_sems[CITIZEN_MUT] = citizen_mut;

	return 0;
}

int init_buffer(char *inputfilepath, int n_citizens, int n_vaccinator){
	char shm_buf_name[SHM_NAME_SIZ];
	sprintf(shm_buf_name, "%ld", (long)getpid());
	strcat(shm_buf_name, SHM_BUF_NAME);
	//fprintf(stdout, "shm_buf_name: %s\n", shm_buf_name);

	char shm_vaccinator[SHM_NAME_SIZ];
	sprintf(shm_vaccinator, "%ld", (long)getpid());
	strcat(shm_vaccinator, SHM_VACCINATOR);
	//fprintf(stdout, "shm_vaccinator: %s\n", shm_vaccinator);

	int fd = shm_open(shm_buf_name, O_CREAT | O_RDWR, 0666);
	if(fd == -1){
		perror("shm_open shm_buf");
		return -1;
	}

	struct stat sb;
	if(fstat(fd, &sb)==-1){
		perror("fstat");
		close(fd);
		shm_unlink(shm_buf_name);
		return -1;
	}

	if(sb.st_size == 0){
		ftruncate(fd, sizeof(int) * MAX_VAC);
	}
	buff = (int*)mmap(NULL, sizeof(int) * MAX_VAC, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(buff == MAP_FAILED){
		perror("mmap error");
		shm_unlink(shm_buf_name);
		close(fd);
		return -1;
	}

	close(fd);
	*buff = 0;

	buff[FILEP] = open(inputfilepath, O_RDONLY);
	buff[VACCINATED] = 0;
	buff[LAST_NURSE] = 0;
	buff[LAST_VACC]  = 0;
	buff[RUN_CITIZEN] = 0;
	buff[CALLED_PID] = 0;
	buff[REMAIN_CITIZEN] = n_citizens;

	if(buff[FILEP] == -1){
		perror("file error");
		shm_unlink(shm_buf_name);
		close(buff[FILEP]);
		return -1;
	}

	fd = shm_open(shm_vaccinator, O_CREAT | O_RDWR, 0666);
	if(fd == -1){
		perror("shm_open shm_vaccinator");
		shm_unlink(shm_buf_name);
		close(buff[FILEP]);
		return -1;
	}

	if(fstat(fd, &sb)==-1){
		perror("fstat");
		shm_unlink(shm_buf_name);
		shm_unlink(shm_vaccinator);
		close(fd);
		close(buff[FILEP]);
		return -1;
	}

	if(sb.st_size == 0){
		ftruncate(fd, sizeof(struct _vaccinator) * n_vaccinator);
	}

	vaccs = (struct _vaccinator*) mmap (NULL, sizeof(struct _vaccinator) * n_vaccinator, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(vaccs == MAP_FAILED){
		perror("mmap error");
		shm_unlink(shm_buf_name);
		shm_unlink(shm_vaccinator);
		close(fd);
		close(buff[FILEP]);
		return -1;
	}

	close(fd);

	return 0;
}

void run_citizens(int n_citizenz, int time_each_citizen){
	for(int i=0 ; i<n_citizenz ; ++i){
		switch((citizen_pids[i] = fork())){
			case -1:
				fprintf(stderr, "citizen fork error\n");
				exit(EXIT_FAILURE);
			break;

			case  0:
				is_child = 1;
				do_citizen(i, time_each_citizen);
			break;

			default:
			break;
		}
	}
}

void do_citizen(int j, int time_each_citizen){
	if(citizen_pids != NULL){
		free(citizen_pids);
		citizen_pids = NULL;
	}

	int counter=0;
	int flag=0;

	for(int i=0 ; i<time_each_citizen ; ++i){
		sem_wait(&all_sems[CALL_CITIZEN]);

		sem_wait(&all_sems[CITIZEN_MUT]);
		buff[CALLED_PID] = getpid();
		++counter;

		if(i+1 == time_each_citizen){
			--buff[REMAIN_CITIZEN];
			flag = 1;
		}

		sem_post(&all_sems[RESPONSE_CITIZEN]);
		sigsuspend(&old);
		fprintf(stdout, "Citizen %d (pid=%ld) is vaccinated for the %d th time: the clinic has %d vaccine1 and %d vaccine2. ", j, (long)getpid(), counter, buff[ONES], buff[TWOS]);
		if(flag) {fprintf(stdout, "The citizen is leaving. Remaining citizens to vaccinate: %d", buff[REMAIN_CITIZEN]);flag=0;}
		fprintf(stdout, "\n");

		sem_post(&all_sems[CITIZEN_MUT]);
	}

	exit(EXIT_SUCCESS);
}

void run_nurses(int n_nurses){
	for(int i=0 ; i<n_nurses ; ++i){
		switch(fork()){
			case -1:
				fprintf(stderr, "producer fork error\n");
				exit(EXIT_FAILURE);
			break;

			case  0:
				is_child = 1;
				do_nurse(i, n_nurses);
			break;

			default:
			break;
		}
	}
}

void do_nurse(int i, int n_nurses){
	int is_eof;
	char ch;
	while(TRUE){

		sem_wait(&all_sems[EMPTY]);

		sem_wait(&all_sems[MUT]);
		
		struct flock lock;
		memset(&lock, 0, sizeof(lock));
		lock.l_type = F_RDLCK;
		fcntl(buff[FILEP], F_SETLKW, &lock);
		
		is_eof = read(buff[FILEP], &ch, 1);

		lock.l_type = F_UNLCK;
		fcntl(buff[FILEP], F_SETLKW, &lock);

		if(is_eof == 0){
			// fprintf(stdout, "I am at EOF, bye\n");
			++buff[LAST_NURSE];
			if(buff[LAST_NURSE] == n_nurses){
				fprintf(stdout, "Nurses have carried all vaccines to the buffer, terminating.\n");
			}
			if(citizen_pids != NULL){
				free(citizen_pids);
				citizen_pids = NULL;
			}
			sem_post(&all_sems[MUT]);
			sem_post(&all_sems[EMPTY]);
			exit(EXIT_SUCCESS);
		}

		if(ch == '1'){
			++buff[ONES];
			fprintf(stdout, "Nurse %d (pid=%ld) has brought vaccine 1: ", i, (long)getpid());
			fprintf(stdout, "the clinic has %d vaccine1 and %d vaccine2.\n", buff[ONES], buff[TWOS]);
			sem_post(&all_sems[MUT]);
			sem_post(&all_sems[FULL_ONES]);
		}

		else if(ch == '2'){
			++buff[TWOS];
			fprintf(stdout, "Nurse %d (pid=%ld) has brought vaccine 2: ", i, (long)getpid());
			fprintf(stdout, "the clinic has %d vaccine1 and %d vaccine2.\n", buff[ONES], buff[TWOS]);
			sem_post(&all_sems[MUT]);
			sem_post(&all_sems[FULL_TWOS]);
		}

		else{
			// fprintf(stderr, "Invalid input from file: %c <-> %d\n", ch, ch);
			sem_post(&all_sems[MUT]);
			sem_post(&all_sems[EMPTY]);
		}
	}
}

void run_vaccinators(int n_vaccinators, int limit){
	for(int i=0 ; i<n_vaccinators ; ++i){
		switch(fork()){
			case -1:
				fprintf(stderr, "consumer fork error\n");
				exit(EXIT_FAILURE);
			break;

			case  0:
				is_child = 1;
				sem_wait(&all_sems[MUT]);
				
				//memcpy(&vaccs[i], &va, sizeof(struct _vaccinator));
				vaccs[i].doses = 0;
				vaccs[i].index = i;
				vaccs[i].pid = getpid();

				sem_post(&all_sems[MUT]);

				do_vaccinator(limit, i, n_vaccinators);
			break;

			default:
			break;
		}
	}
}

void do_vaccinator(int limit, int i, int n_vaccinators){
	while(TRUE){
		sem_wait(&all_sems[MUT]);
		if(buff[VACCINATED] >= limit){
			//fprintf(stdout, "vaccinator bye.\n");
			++buff[LAST_VACC];
			if(buff[LAST_VACC] == n_vaccinators){
				fprintf(stdout, "All citizens have been vaccinated .\n");
				for(int k=0 ; k<n_vaccinators ; ++k){
					printf("Vaccinator %d (pid=%ld) vaccinated %d doses. ", vaccs[k].index, (long)vaccs[k].pid, vaccs[k].doses);
				}
				fprintf(stdout, "The clinic is now closed. Stay healthy\n");
			}

			sem_post(&all_sems[MUT]);
			if(citizen_pids != NULL){
				free(citizen_pids);
				citizen_pids = NULL;
			}
			exit(EXIT_SUCCESS);
		}
		else{
			++buff[VACCINATED];
		}
		sem_post(&all_sems[MUT]);

		sem_wait(&all_sems[FULL_ONES]);
		sem_wait(&all_sems[FULL_TWOS]);
		sem_wait(&all_sems[MUT]);

		sem_post(&all_sems[CALL_CITIZEN]);
		sem_wait(&all_sems[RESPONSE_CITIZEN]);
		++buff[RUN_CITIZEN];
		--buff[ONES];
		--buff[TWOS];

		++vaccs[i].doses;
		fprintf(stdout, "Vaccinator %d (pid=%ld) is inviting citizen pid=%ld to the clinic\n", i, (long)getpid(), (long)buff[CALLED_PID]);
		kill((pid_t)buff[CALLED_PID], SIGUSR1);

		sem_post(&all_sems[MUT]);
		sem_post(&all_sems[EMPTY]);
		sem_post(&all_sems[EMPTY]);
	}
}

void clean_resources(){

	while(wait(NULL)!=-1);

	char shm_name[SHM_NAME_SIZ];
	sprintf(shm_name, "%ld", (long)getpid());
	strcat(shm_name, SHM_NAME);
	// fprintf(stdout, "clean shm_name: %s\n", shm_name);

	char shm_buf_name[SHM_NAME_SIZ];
	sprintf(shm_buf_name, "%ld", (long)getpid());
	strcat(shm_buf_name, SHM_BUF_NAME);
	// fprintf(stdout, "clean shm_buf_name: %s\n", shm_buf_name);

	char shm_vaccinator[SHM_NAME_SIZ];
	sprintf(shm_vaccinator, "%ld", (long)getpid());
	strcat(shm_vaccinator, SHM_VACCINATOR);
	// fprintf(stdout, "clean shm_vaccinator: %s\n", shm_vaccinator);

	if(citizen_pids != NULL){
		free(citizen_pids);
		citizen_pids = NULL;
	}
	
	sem_close(&full_ones);
	sem_close(&empty);
	sem_close(&full_twos);
	sem_close(&mut);

	sem_destroy(&full_ones);
	sem_destroy(&empty);
	sem_destroy(&full_twos);
	sem_destroy(&mut);
	sem_destroy(&call_citizen);
	sem_destroy(&response_citizen);
	sem_destroy(&citizen_mut);

	shm_unlink(shm_buf_name);
	shm_unlink(shm_name);
	shm_unlink(shm_vaccinator);

	close(buff[FILEP]);
}
