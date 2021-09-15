#include "171044066_hw3.h"

sig_atomic_t sig_int_ = 0;

int main(int argc, char *argv[]){
	int max_process; 
	struct potato *potato_list;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	if(parse_command_args(argc, argv) == -1) return 1;

	if((max_process =  get_line_number(file_with_fifonames))==-1) return 1;
	if(max_process < 2){
		fprintf(stdout, "I need at lesat 2 fifoname\n");
		fflush(stdout);
		return 1;
	}

	potato_list = push_potato_shm(max_process);
	if(potato_list == NULL){
		return 1;
	}

	/*
	if(has_potato_or_not == 4){
		for(int i =0 ; i<max_process; ++i){
			printf("%s %ld\n", potato_list[i].fifoname, (long)(potato_list[i].pid));
			fflush(stdout);
		}
		fflush(stdout);
	}*/

	play_game(potato_list, max_process);

	if(sig_int_){
		fprintf(stderr, "CTRL+C signal received\n");
		return 1;
	}

	return 0;
}

void help_usage(char *exe_name){
	fprintf(stderr,
		"usage: %s -b haspotatoornot -s nameofsharedmemory -f filewithfifonames -m namedsemaphore\n",
		exe_name
	);

	fprintf(stderr, "%s%s%s%s",
		"haspotatoornot: can be 0 or a positive integer.\n",
		"namedsemaphore: named posix semaphore to be used for synchronization\n",
		"nameofsharedmemory: this will be the name of the posix named shared memory segment.\n",
		"filewithfifonames: this ascii file will contain the names of the fifoes\n"
	);
}

int parse_command_args(int argc, char *argv[]){
	int a0, a1, a2, a3;
	a0 = a1 = a2 = a3 = 1;

	if(argc == 1){
		help_usage(argv[0]);
		return -1;
	}

	char c;
	while((c = getopt (argc, argv, "b:s:f:m:")) != -1){
		switch(c){
			case 'b':
				has_potato_or_not = atoi(optarg);
				if(has_potato_or_not < 0){
					fprintf(stderr, "has_potato_or_not can't have negative value, it is set to 0.\n");
					has_potato_or_not = 0;
				}
				a0=0;
				break;
			case 's':
				name_of_sharedmemory = optarg;
				a1=0;
				break;
			case 'f':
				file_with_fifonames = optarg;
				a2=0;
				break;
			case 'm':
				namedsemaphore = optarg;
				a3=0;
				break;
			case '?':
				help_usage(argv[0]);
				return -1;
			default:
				return -1;
		}
	}

	if(a0 || a1 || a2 || a3){
		fprintf(stderr, "argument error\n");
		help_usage(argv[0]);
		return -1;
	}

	/*
	fprintf(stdout, "%d\n%s\n%s\n%s\n", 
		has_potato_or_not,
		name_of_sharedmemory,
		file_with_fifonames,
		namedsemaphore
	);
	*/

	return 0;
}

int get_line_number(char *file_name){
	FILE *filep = fopen(file_name, "r");

	if(filep == NULL){
		perror("file open 1");
		return -1;
	}

	struct flock lock;
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK;
	fcntl(filep->_fileno, F_SETLKW, &lock);

	char buf[BUFSIZ];
	int i=0;

	for(i = 0 ; fgets(buf, BUFSIZ, filep) ; ++i ){
		if(*buf == '\n') --i;
	}

	lock.l_type = F_UNLCK;
	fcntl(filep->_fileno, F_SETLKW, &lock);

	fflush(filep);
	fclose(filep);

	return i;
}

struct potato* push_potato_shm(int max_process){
	int fd;
	struct stat sb;
	int new_length;
	unsigned int n_th_process;
	char curr_fifoname[BUFSIZ];
	struct potato *curr_addr;

	mutex_sem = sem_open(namedsemaphore, O_RDWR | O_CREAT, 0666, 1);
	sem_wait(mutex_sem);
	
	barrier = sem_open(BARRIER_NAME, O_RDWR | O_CREAT, 0666, 0);

	if(mutex_sem == SEM_FAILED){
		perror("mutex error");
		return NULL;
	}

	if(barrier == SEM_FAILED){
		perror("barrier error");
		sem_post(mutex_sem);
		sem_close(mutex_sem);
		sem_unlink(namedsemaphore);
		return NULL;
	}
	
	fd = shm_open(name_of_sharedmemory, O_CREAT | O_RDWR, 0666);
	if(fd == -1){
		perror("fd error");
		sem_post(mutex_sem);
		sem_close(mutex_sem);
		sem_unlink(namedsemaphore);
		sem_close(barrier);
		sem_unlink(BARRIER_NAME);
		return NULL;
	}

	if(fstat(fd, &sb) == -1){
		perror("fstat error");
		sem_post(mutex_sem);
		sem_close(mutex_sem);
		sem_unlink(namedsemaphore);
		sem_close(barrier);
		sem_unlink(BARRIER_NAME);
		close(fd);
		return NULL;
	}

	new_length = sb.st_size + sizeof(struct potato);

	if(ftruncate(fd, new_length) == -1){
		perror("ftruncate error");
		sem_post(mutex_sem);
		sem_close(mutex_sem);
		sem_unlink(namedsemaphore);
		sem_close(barrier);
		sem_unlink(BARRIER_NAME);
		close(fd);
		return NULL;
	}

	n_th_process = (unsigned int)(sb.st_size / sizeof(struct potato));

	curr_addr = (struct potato *) mmap(NULL, new_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);

	if(curr_addr == NULL){
		perror("curr_addr is NULL");
		sem_post(mutex_sem);
		return NULL;
	}

	get_line_(file_with_fifonames, curr_fifoname, n_th_process);
	curr_addr[n_th_process].pid = getpid();
	curr_addr[n_th_process].heat = has_potato_or_not;
	strcpy(curr_addr[n_th_process].fifoname, curr_fifoname);

	//printf("HERE %d %s %ld %d\n", n_th_process, curr_addr[n_th_process].fifoname, (long)getpid(), new_length);
	//fflush(stdout);
	if(mkfifo(curr_addr[n_th_process].fifoname, 0666)){
		if(errno != EEXIST){
			perror("mkfifo");
			sem_post(mutex_sem);
			sem_close(mutex_sem);
			sem_unlink(namedsemaphore);
			sem_close(barrier);
			sem_unlink(BARRIER_NAME);
			return NULL;
		}
	}

	if((n_th_process + 1) == (unsigned int)max_process) sem_post(barrier);

	sem_post(mutex_sem);

	sem_wait(barrier);
	sem_post(barrier);

	sem_close(mutex_sem);
	sem_unlink(namedsemaphore);

	sem_close(barrier);
	sem_unlink(BARRIER_NAME);

	return curr_addr;
}

int get_line_(char *filename, char fifo_name[BUFSIZ], int index){
	int len = 0;
	int i = 0;
	char *is_null = NULL;

	FILE *filep = fopen(filename, "r");
	if(filep == NULL){
		perror("file open 2");
		return -1;
	}

	struct flock lock;
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK;
	
	fcntl(filep->_fileno, F_SETLKW, &lock);

	for(i=0 ; (is_null = fgets(fifo_name, BUFSIZ, filep)) && i < index; ++i);

	if(!is_null || fifo_name[0] == '\n'){
		return -1;
	}

	len = strlen(fifo_name);
	if(fifo_name[len-1] == '\n') fifo_name[len-1] = '\0'; 

	lock.l_type = F_UNLCK;
	fcntl(filep->_fileno, F_SETLKW, &lock);

	fflush(filep);
	fclose(filep);

	return 0;
}

void sigint_handler(){
	sig_int_ = 1;
}

int play_game(struct potato *potato_list, int max_process){
	int fd_read, fd_write, fd_common;
	struct flock lock1;
	struct flock lock2;
	struct potato temp;

	for(int i=0 ; i<max_process ; ++i){
		if(potato_list[i].pid == getpid()){
			fd_read = open(potato_list[i].fifoname, O_RDONLY);
			if(fd_read == -1){
				perror("file1");
				return 1;
			}
		}
		else{
			fd_write = open(potato_list[i].fifoname, O_WRONLY);
			if(fd_write == -1){
			}
		}
	}

	for(int i=0 ; i<max_process ; ++i){
		if(getpid() == potato_list[i].pid){
			fd_common = open(potato_list[(i+1)%max_process].fifoname, O_WRONLY);
			if(fd_common == -1){
				//perror("file3");
				return 1;
			}

			memset(&lock1, 0, sizeof(lock1));
			lock1.l_type = F_WRLCK;
			fcntl(fd_common, F_SETLKW, &lock1);
			
			write(fd_common, &potato_list[i], sizeof(struct potato));

			lock1.l_type = F_UNLCK;
			fcntl(fd_common, F_SETLKW, &lock1);
		}

		if(getpid() == potato_list[(i+1)%max_process].pid){
			fd_common = open(potato_list[(i+1)%max_process].fifoname, O_RDONLY);
			if(fd_common == -1){
				perror("file4");
				return 1;
			}

			memset(&lock2, 0, sizeof(lock2));
			lock2.l_type = F_WRLCK;
			fcntl(fd_common, F_SETLKW, &lock2);

			read(fd_common, &temp, sizeof(struct potato));
			fprintf(stdout, "pid=%ld sending potato number %ld to %s\n", (long)temp.pid, (long)getpid(), temp.fifoname);
			fflush(stdout);

			lock2.l_type = F_UNLCK;
			fcntl(fd_common, F_SETLKW, &lock2);
		}
	}

	set_last_barrier(max_process);

	for(int i=0 ; i<max_process ; ++i){
		unlink(potato_list[i].fifoname);
	}

	shm_unlink(name_of_sharedmemory);

	return 0;
}

void set_last_barrier(int max){
	int fd;
	struct stat sb;
	int *addr;

	last_mutex_sem = sem_open(LAST_SEMAPHORE_NAME, O_RDWR | O_CREAT, 0666, 1);
	sem_wait(last_mutex_sem);

	last_barrier = sem_open(LAST_BARRIER_NAME, O_RDWR | O_CREAT, 0666, 0);

	if(last_mutex_sem == SEM_FAILED){
		perror("last mutex error");
		return;
	}
	
	if(last_barrier == SEM_FAILED){
		perror("last barrier error");
		sem_post(last_mutex_sem);
		sem_close(last_mutex_sem);
		sem_unlink(LAST_SEMAPHORE_NAME);
		return;
	}

	fd = shm_open(COUNT_SHM, O_CREAT | O_RDWR, 0666);
	if(fd == -1){
		perror("fd error");
		sem_post(last_mutex_sem);
		sem_close(last_mutex_sem);
		sem_unlink(LAST_SEMAPHORE_NAME);
		sem_close(last_barrier);
		sem_unlink(LAST_BARRIER_NAME);
		return;
	}

	if(fstat(fd, &sb) == -1){
		perror("fstat error");
		sem_post(last_mutex_sem);
		sem_close(last_mutex_sem);
		sem_unlink(LAST_SEMAPHORE_NAME);
		sem_close(last_barrier);
		sem_unlink(LAST_BARRIER_NAME);
		close(fd);
		return;
	}

	if(sb.st_size == 0){
		ftruncate(fd, 4);
	}

	addr = (int *) mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	if(addr == NULL){
		perror("addr is NULL error");
		sem_post(last_mutex_sem);
		sem_close(last_mutex_sem);
		sem_unlink(LAST_SEMAPHORE_NAME);
		sem_close(last_barrier);
		sem_unlink(LAST_BARRIER_NAME);
		close(fd);
	}

	if(sb.st_size != 0){
		++(*addr);
	}
	else{
		*addr = 0;
	}

	if((*addr) + 1 == max) sem_post(last_barrier);

	sem_post(last_mutex_sem);

	sem_wait(last_barrier);
	sem_post(last_barrier);

	sem_close(last_mutex_sem);
	sem_unlink(LAST_SEMAPHORE_NAME);

	sem_close(last_barrier);
	sem_unlink(LAST_BARRIER_NAME);

	shm_unlink(COUNT_SHM);
}
