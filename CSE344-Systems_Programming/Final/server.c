#include "server.h"

int main(int argc, char *argv[]){
	clock_t start;
	char *time_stamp;

	log_filep = stderr;
	if(is_double_instantiation() == -1){
		exit(EXIT_FAILURE);
	}

	log_filep = stdout;
	init_signals();

	if(parse_arguments(argc, argv) == -1){
		sem_close(against_double_instantiation);
		sem_unlink(SEM_NAME);
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	become_daemon();

	log_filep = fopen(_pathToLogFile, "w");
	if(log_filep == NULL){
		sem_close(against_double_instantiation);
		sem_unlink(SEM_NAME);
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:file open error\n", time_stamp);
		free(time_stamp);
		exit(EXIT_FAILURE);
	}

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:Executing with parameters:\n", time_stamp);
	free(time_stamp);

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:\n-p %d\n-o %s\n-l %d\n-d %s\n",
		time_stamp,
		_port,
		_pathToLogFile,
		_poolSize,
		_datasetPath
	);
	free(time_stamp);

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:Loading dataset...\n", time_stamp);
	free(time_stamp);

	start = clock();
	if(create_the_table(_datasetPath) == -1){
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:Dataset could not be loaded (file path might be wrong)\n", time_stamp);
		free(time_stamp);
		
		exit(EXIT_FAILURE);
	}

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:Dataset loaded in %.2lf seconds with %d records.\n", time_stamp, ((double)(clock() - start) / CLOCKS_PER_SEC), row_len - 1);
	free(time_stamp);

	init_the_mutex();
	init_counter();
	init_the_available();
	init_the_barrier();
	init_lock_mutex();

	create_pool_threads();

	run_the_server();

	clean_garbage();

	return 0;
}

void sigint_handler(){
	sig_int = 1;
}

void init_signals(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	//sigaction(SIGPIPE, &sa, NULL);
	
}

void sleep_half_second(){
	struct timespec requested_time = { (time_t)0, (long)500000000L };
	struct timespec remaining_time = { (time_t)0, (long)0L };

	nanosleep(&requested_time, &remaining_time);
}

void print_usage(char *exe_name){
	char *time_stamp;
	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:Usage: %s -p PORT -o pathToLogFile -l poolSize -d datasetPath\n", time_stamp, exe_name);
	free(time_stamp);

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:\n%s%s%s%s",
		time_stamp, 
		"PORT: this is the port number the server will use for incoming connections.\n",
		"pathToLogFile: is the relative or absolute path of the log file to which the server daemon will write all of its output (normal output & errors).\n",
		"poolSize: the number of threads in the pool (>= 2).\n",
		"datasetPath: is the relative or absolute path of a csv file containing a single table.\n"
	);
	free(time_stamp);
}

int parse_arguments(int argc, char *argv[]){
	int a0, a1, a2, a3;
	a0 = a1 = a2 = a3 = 1;
	char *time_stamp;

	if(argc != 9){
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:invalid arguments\n", time_stamp);
		free(time_stamp);
		return -1;
	}

	char c;
	while((c=getopt(argc, argv, "p:o:l:d:")) != -1){
		switch(c){
			case 'p':
				_port = atoi(optarg);
				if(_port <=1000){
					time_stamp = get_timestamp();
					fprintf(log_filep, "%s -:invalid port number (>1000, the first 1000 are reserved to kernel processes)\n", time_stamp);
					free(time_stamp);
					return -1;
				}
				a0 = 0;
				break;
			case 'o':
				_pathToLogFile = optarg;
				a1 = 0;
				break;
			case 'l':
				_poolSize = atoi(optarg);
				if(_poolSize < 2){
					time_stamp = get_timestamp();
					fprintf(log_filep, "%s -:pool size should be greater than 2.\n", time_stamp);
					free(time_stamp);
					return -1;
				}
				a2 = 0;
				break;
			case 'd':
				_datasetPath = optarg;
				a3 = 0;
				break;
			case '?':
				return -1;
			default:
				return -1;
		}
	}

	if(a0 || a1 || a2 || a3){
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:argument error\n", time_stamp);
		free(time_stamp);
		return -1;
	}

	return 0;
}

void create_pool_threads(){
	tids = (pthread_t *) malloc (sizeof(pthread_t) * _poolSize);
	worker_ids = (int *) malloc (sizeof(int) * _poolSize);

	for(int i=0 ; i<_poolSize ; ++i){
		worker_ids[i] = i + 1;
		pthread_create(&tids[i], NULL, run_helper_threads, (void*) (worker_ids + i));
	}
}

void run_the_server(){
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	char *time_stamp;
	if(fd == -1){
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:socket failed\n", time_stamp);
		free(time_stamp);
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	int opt = 1;
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1){
		close(fd);
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:setsockopt error\n", time_stamp);
		free(time_stamp);
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = INADDR_ANY;
	//inet_aton(HOST, &(addr.sin_addr));

	if(bind(fd, (struct sockaddr*)(&addr), sizeof(addr)) == -1){
		close(fd);
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:bind error\n", time_stamp);
		free(time_stamp);
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if(listen(fd, 200) < 0){
		close(fd);
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:listen error\n", time_stamp);
		free(time_stamp);
		perror("listen");
		exit(EXIT_FAILURE);
	}

	server_main_thread(fd, addr);

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:Termination signal received, waiting for ongoing threads to complete.\n", time_stamp);
	free(time_stamp);

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:All threads have terminated, server shutting down.\n", time_stamp);
	free(time_stamp);

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:total number of handled query: %d\n", time_stamp, counter);
	free(time_stamp);

	close(fd);
}

void clean_garbage(){

	if(log_filep != NULL && log_filep != stdout){
		fclose(log_filep);
	}

	free_table();

	for(int i=0 ; i<_poolSize ; ++i){
		pthread_cond_broadcast(&ok_to_poll);
	}

	for(int i=0 ; i<_poolSize ; ++i){
		pthread_join(tids[i], NULL);
	}

	pthread_mutex_destroy(&m_queue);
	pthread_mutex_destroy(&m_counter);
	pthread_mutex_destroy(&m_barrier);
	pthread_mutex_destroy(&lock);

	while(!is_empty(&request_fd_queue)){
		close(poll_int(&request_fd_queue));
		--len_of_queue;
	}

	free_queue(&request_fd_queue);
	free(tids);
	free(worker_ids);

	sem_close(against_double_instantiation);
	sem_unlink(SEM_NAME);
}

void server_main_thread(int fd, struct sockaddr_in addr){
	int addr_len = sizeof(addr);
	int cfd;
	char *time_stamp;

	for(EVER){

		cfd = accept(fd, (struct sockaddr *)(&addr), (socklen_t*)(&addr_len));

		if(sig_int){
			break;
		}

		if(cfd == -1){
			time_stamp = get_timestamp();
			fprintf(log_filep, "%s -:accept error\n", time_stamp);
			free(time_stamp);

			perror("accept");
			break;
		}

		pthread_mutex_lock(&m_available);
			while(i_available == 0){
				time_stamp = get_timestamp();
				fprintf(log_filep, "%s -:No thread is available! Waiting…\n", time_stamp);
				free(time_stamp);
				pthread_cond_wait(&c_available, &m_available);
				if(sig_int) break;
			}
			--i_available;
		pthread_mutex_unlock(&m_available);
		if(sig_int) break;


		pthread_mutex_lock(&m_queue);
			offer_int(&request_fd_queue, cfd);
			++len_of_queue;
			pthread_cond_broadcast(&ok_to_poll);
		pthread_mutex_unlock(&m_queue);
	}
}

void* run_helper_threads(void *arg){
	int worker_id = *((int*)arg);
	char *time_stamp;

	pthread_mutex_lock(&m_available);
		++i_available;
		pthread_cond_signal(&c_available);
	pthread_mutex_unlock(&m_available);

	pthread_mutex_lock(&m_barrier);
		++i_barrier;
		if(i_barrier == _poolSize){
			time_stamp = get_timestamp();
			fprintf(log_filep, "%s -:A pool of %d threads has been created\n", time_stamp, _poolSize);
			free(time_stamp);
			pthread_cond_broadcast(&c_barrier);
		}
	pthread_mutex_unlock(&m_barrier);

	pthread_mutex_lock(&m_barrier);
	while(i_barrier != _poolSize){
		pthread_cond_wait(&c_barrier, &m_barrier);
		if(sig_int) break;
	}
	pthread_mutex_unlock(&m_barrier);

	do_helper_thread(worker_id);

	return NULL;
}

void do_helper_thread(int worker_id){
	int fd;
	char req_buf[BUFSIZ];
	int req_len=0;
	char *time_stamp;

	bzero(req_buf, BUFSIZ);

	for(EVER){
		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:Thread #%d: waiting for connection\n", time_stamp, worker_id);
		free(time_stamp);
		if(sig_int) break;

		pthread_mutex_lock(&m_queue);
			if(sig_int){
				pthread_mutex_unlock(&m_queue);
				break;
			}
			while(len_of_queue == 0){
				pthread_cond_wait(&ok_to_poll, &m_queue);
				if(sig_int) {
					pthread_mutex_unlock(&m_queue);
					return;
				}
			}
			fd = poll_int(&request_fd_queue);
			--len_of_queue;
		pthread_mutex_unlock(&m_queue);

		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:A connection has been delegated to thread id #%d\n", time_stamp, worker_id);
		free(time_stamp);

		int go = 1;
		write(fd, &go, sizeof(int));

		while(TRUE){
			//get request
			read(fd, &req_len, sizeof(int));
			if(req_len < 0) break;
			read(fd, req_buf, req_len);
			
			pthread_mutex_lock(&m_counter);
			++counter;
			pthread_mutex_unlock(&m_counter);

			handle_query(req_buf, fd, worker_id);
		}
		close(fd);
		pthread_mutex_lock(&m_available);
			++i_available;
			pthread_cond_signal(&c_available);
		pthread_mutex_unlock(&m_available);
	}
}

void init_the_mutex(){
	pthread_mutexattr_t mtxAttr;
	int s;

	s = pthread_mutexattr_init(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_DEFAULT);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutex_init(&m_queue, &mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_destroy(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}
}

void init_counter(){
	counter = 0;
	pthread_mutexattr_t mtxAttr;
	int s;

	s = pthread_mutexattr_init(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_DEFAULT);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutex_init(&m_counter, &mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_destroy(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}
}

void init_the_available(){
	i_available = 0;
	
	pthread_mutexattr_t mtxAttr;
	int s;

	s = pthread_mutexattr_init(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_DEFAULT);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutex_init(&m_available, &mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_destroy(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}
}

void init_the_barrier(){
	i_barrier = 0;
	
	pthread_mutexattr_t mtxAttr;
	int s;

	s = pthread_mutexattr_init(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_DEFAULT);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutex_init(&m_barrier, &mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_destroy(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}
}

void init_lock_mutex(){
	pthread_mutexattr_t mtxAttr;
	int s;

	s = pthread_mutexattr_init(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_DEFAULT);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutex_init(&lock, &mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}

	s = pthread_mutexattr_destroy(&mtxAttr);
	if(s != 0){
		strerror(s);
		exit(EXIT_FAILURE);
	}
}

int find_col_len(char *filename){
 	int _col_len = 0;
	char c;
	FILE *filep = fopen(filename, "r");

	if(filep == NULL) return -1;

	while((c = fgetc(filep)) != EOF && c != '\r' && c != '\n'){
		if(c == '\"'){
			while((c = fgetc(filep))!=EOF && c != '\"');
			c = fgetc(filep);
		}
	
		if(c == ',') ++_col_len;
	}

	fclose(filep);
	return _col_len + 1;
}

int find_row_len(char *filename){
	int _row_len = 0;
	char c;
	FILE *filep = fopen(filename, "r");

	if(filep == NULL) return -1;

	while((c = (fgetc(filep))) != EOF){
		if(c == '\"'){
			while((c = (fgetc(filep))) != EOF && c != '\"');
			c = (fgetc(filep));
		}
	
		if(c == '\n') ++_row_len;
	}

	fclose(filep);
	return _row_len;
}

int create_the_table(char *filename){
	char *buf;
	int fd;
	struct stat stat_buf;
	int cell_len;

	col_len = find_col_len(filename);
	if(col_len < 0) return -1;
	// fprintf(stdout, "col_len: %d\n", col_len);

	row_len =  find_row_len(filename);
	if(row_len < 0) return -1;
	// fprintf(stdout, "row_len: %d\n",row_len);


	csv_table = (char***) malloc (sizeof(char**) * row_len);
	if(csv_table == NULL) return -1;
	for(int i=0 ; i<row_len ; ++i){
		csv_table[i] = (char **) malloc (sizeof(char*) * col_len);
		if(csv_table[i] == NULL) return -1;
	}

	fd = open(filename, O_RDONLY);
	if(fd == -1) return -1;

	fstat(fd, &stat_buf);
	buf = (char*) mmap(NULL, stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	cell_len=0;
	int k=0;
	int begin;
	for(int i=0 ; i<row_len ; ++i){
		for(int j=0 ; j<col_len ; ++j){
			//while(buf[k] == ' ' || buf[k] == '\n' || buf[k] == '\r') ++k;

			if(buf[k] == '\"'){
				++k;
				while(buf[k] != '\"'){
					++k;
					++cell_len;
				}
				++k;
				begin = k - cell_len - 1;
			}
			else{
				while(buf[k] != '\0' && buf[k] != ',' && buf[k] != '\n'){
					++k;
					++cell_len;
				}
				begin = k - cell_len;
			}

			++k;

			csv_table[i][j] = (char*) malloc (sizeof(char) * (cell_len + 1));
			
			strncpy(csv_table[i][j], (buf + begin), cell_len);
			csv_table[i][j][cell_len] = '\0';
			str_replace(csv_table[i][j], '\r', '\0');

			cell_len = 0;
		}
	}
	munmap(buf, stat_buf.st_size);
	return 0;
}

int str_replace(char *str, char old_char, char new_char){
	for(int i=0 ; str[i] != '\0' ; ++i){
		if(str[i] == old_char){
			str[i] = new_char;
			return 1;
		}
	}
	return 0;
}

void free_table(){
	for(int i=0 ; i<row_len ; ++i){
		for(int j=0 ; j<col_len ; ++j){
			free(csv_table[i][j]);
		}
	}

	for(int i=0 ; i<row_len ; ++i){
		free(csv_table[i]);
	}
	free(csv_table);
}

void print_table(){
	int k=0;
	for(int i=0 ; i<row_len ; ++i){
		for(k=0 ; k<col_len - 1 ; ++k){
			printf("%s,", csv_table[i][k]);
		}
		printf("%s\n", csv_table[i][k]);
	}
}

void handle_query(char *query, int fd ,int worker_id){
	char resp_buf[MAX_LINE_LEN];
	bzero(resp_buf, MAX_LINE_LEN);

	int *is_selected = (int*) malloc(sizeof(int) * col_len);
	for(int i=0 ; i<col_len ; ++i) is_selected[i] = 0;
	int is_select;
	int record_number=0;

	char temp_query[BUFSIZ];
	char *token;
	char *rest = temp_query;
	int index=0;
	char **values = (char**) malloc (sizeof(char*) * col_len);
	for(int i=0 ; i<col_len ; ++i) values[i] = NULL;
	char *search_value = NULL;
	int search_index = 0;
	char *time_stamp;

	parse_query(query, &is_select, is_selected);

	time_stamp = get_timestamp();
	fprintf(log_filep, "%s -:Thread #%d: received query '%s'\n", time_stamp, worker_id, query);
	free(time_stamp);

	write(fd, &is_select, sizeof(int));

	//printf("HERE\n");
	fflush(stdout);

	if(is_select){

		pthread_mutex_lock(&lock);

		while((AW + WW) > 0){	// if any writers, wait
			++WR;
			pthread_cond_wait(&okToRead, &lock);
			--WR;
		}
		++AR;

		pthread_mutex_unlock(&lock);

		///////////////////////////////// Access DB /////////////////////////////////
		write(fd, &row_len, sizeof(int));
		sleep_half_second();
		for(int i=0 ; i<row_len ; ++i){
			for(int j=0 ; j<col_len ; ++j){
				if(is_selected[j]){
					strcat(resp_buf, csv_table[i][j]);
					strcat(resp_buf, " ");
				}
			}
			// printf("%s\n", resp_buf);
			++record_number;

			write(fd, resp_buf, MAX_LINE_LEN);
			bzero(resp_buf, MAX_LINE_LEN);
		}
		write(fd, &record_number, sizeof(int));

		time_stamp = get_timestamp();
		fprintf(log_filep, "%s -:Thread #%d: query completed, %d records have been returned.\n", time_stamp, worker_id, record_number);
		free(time_stamp);
		///////////////////////////////// Access DB /////////////////////////////////

		pthread_mutex_lock(&lock);

		--AR;

		if(AR == 0 && WW > 0)
			pthread_cond_signal(&okToWrite);
		
		pthread_mutex_unlock(&lock);
	}
	else{
		pthread_mutex_lock(&lock);

		while((AW + AR) > 0){
			++WW;
			pthread_cond_wait(&okToWrite, &lock);
			--WW;
		}
		++AW;

		pthread_mutex_unlock(&lock);

		///////////////////////////////// Access DB /////////////////////////////////
		strcpy(temp_query, query);
		rest = temp_query;
		token = strtok_r(temp_query, " ", &rest);

		if(strcmp(token, "UPDATE") == 0){
			token = strtok_r(NULL, " ", &rest);
			if(strcmp(token, "TABLE") == 0){
				token = strtok_r(NULL, " ", &rest);
				if(strcmp(token, "SET") == 0){
					token = strtok_r(NULL, "=", &rest);
					while(TRUE){
						//printf("col name: %s\n", token);
						index = column_index(token);
						if(index >= 0) is_selected[index] = 1;

						if(comma_or_space(rest) == ' '){
							token = strtok_r(NULL, " ", &rest);
							++token;
							str_replace(token, '\'', '\0');
							values[index] = token;
							//printf("value: %s\n", token);
							break;
						}
						else{
							token = strtok_r(NULL, ",", &rest);
							while(*rest == ' ') ++rest;
							++token;
							str_replace(token, '\'', '\0');
							values[index] = token;
							//printf("value: %s\n", token);
						}

						token = strtok_r(NULL, "=", &rest);
					}
					token = strtok_r(NULL, " ", &rest);
					token = strtok_r(NULL, "=", &rest);
					index = column_index(token);
					search_index = index;
					//printf("%s\n", token);

					token = strtok_r(NULL, ",", &rest);
					search_value = token;
					//printf("%s\n", token);

					++search_value;
					str_replace(search_value, '\'', '\0');

					//printf("%s %d\n", search_value, search_index);

					for(int i=0 ; i<row_len ; ++i){
						for(int j=0 ; j<col_len ; ++j){
							if(is_selected[j]){
								if(strcmp(csv_table[i][search_index], search_value) == 0){
									++record_number;
									free(csv_table[i][j]);
									csv_table[i][j] = (char*) malloc (sizeof(char) * (strlen(values[j])+1));
									strcpy(csv_table[i][j], values[j]);
								}
							}
						}
					}
				}
			}
			write(fd, &record_number, sizeof(int));
		}
		///////////////////////////////// Access DB /////////////////////////////////

		pthread_mutex_lock(&lock);

		--AW;

		if(WW > 0) pthread_cond_signal(&okToWrite);
		else if(WR > 0) pthread_cond_broadcast(&okToRead);

		pthread_mutex_unlock(&lock);
	}

	free(values);
	free(is_selected);
}

void parse_query(char *query, int *is_select, int *is_selected){
	char c;
	int index;
	char temp[BUFSIZ];
	strcpy(temp, query);

	char *token;
	char *rest = temp;
	token = strtok_r(temp, " ", &rest);

	/*
	token = strtok_r(NULL, " ", &rest);
	printf("%s\n", token);
	token = strtok_r(NULL, " ", &rest);
	printf("%s\n", token);
	*/

	for(int i=0 ; i<col_len ; ++i) is_selected[i] = 0;

	if(token != NULL && strcmp(token, "SELECT") == 0){
		*is_select = 1;
		c = comma_or_space(rest);
		if(c == ' '){
			token = strtok_r(NULL, " ", &rest);
			if(token != NULL && strcmp(token, "DISTINCT") == 0){
				c = comma_or_space(rest);
				if(c == ' '){
					token = strtok_r(NULL, " ", &rest);
					if(token != NULL && strcmp(token, "*") == 0){
						for(int i=0 ; i<col_len ; ++i){
							is_selected[i] = 1;
						}
					}
					else{
						index = column_index(token);
						if(index >= 0) is_selected[index] = 1;
					}
				}
				else if(c == ','){
					token = strtok_r(NULL, ",", &rest);
					while(1){
						if(token == NULL) break;
						if(strcmp(token, "FROM") == 0) break;

						index = column_index(token);
						if(index >=0 ) is_selected[index] = 1;

						while(*rest == ' ') ++rest;

						if(comma_or_space(rest) == ' ') token = strtok_r(NULL, " ", &rest);
						else token = strtok_r(NULL, ",", &rest);
					}
				}
				
			}
			else if(token != NULL && strcmp(token, "*") == 0){
				for(int i=0 ; i<col_len ; ++i){
					is_selected[i] = 1;
				}
			}
			else{
				index = column_index(token);
				if(index >= 0) is_selected[index] = 1;
			}
		}
		else if(c == ','){
			token = strtok_r(NULL, ",", &rest);
			while(1){
				if(token == NULL) break;
				if(strcmp(token, "FROM") == 0) break;

				index = column_index(token);
				if(index >=0 ) is_selected[index] = 1;

				while(*rest == ' ') ++rest;

				if(comma_or_space(rest) == ' ') token = strtok_r(NULL, " ", &rest);
				else token = strtok_r(NULL, ",", &rest);
			}
		}
	}else{
		*is_select = 0;
	}

	/*
	int j=0;
	for(j=0 ; j<col_len-1 ; ++j)
		printf("%d, ", is_selected[j]);
	printf("%d\n", is_selected[j]);*/
}

char comma_or_space(char *str){
	for(int i=0 ; str[i] !='\0' ; ++i){
		if(str[i] == ' ') return ' ';
		else if(str[i] == ',') return ',';
	}
	return '\0';
}

int column_index(char *str){
	for(int i=0 ; i<col_len ; ++i){
		if(strcmp(csv_table[0][i], str) == 0){
			return i;
		}
	}
	return -1;
}

char *get_timestamp(){
	char *ret_val = (char*) malloc (sizeof(char) * 32);

	time_t curr_time;
	struct tm *s_time;
	curr_time = time(NULL);
	s_time = localtime(&curr_time);
	sprintf(ret_val, "%02d-%02d-%02d", s_time->tm_hour, s_time->tm_min, s_time->tm_sec);
	return ret_val;
}

void become_daemon(){
	int maxfd, fd;
	struct sigaction sa;

	switch(fork()){
		case -1	: exit(EXIT_FAILURE);
		case  0	: break;
		default	: exit(EXIT_SUCCESS);
	}

	if(setsid() == -1){
		perror("setsid()");
		exit(EXIT_FAILURE);
	}

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_hub_handler;
	sigaction(SIGHUP, &sa, NULL);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_term_handler;
	sigaction(SIGTERM, &sa, NULL);

	switch(fork()){
		case -1	: exit(EXIT_FAILURE);
		case  0	: break;
		default	: exit(EXIT_SUCCESS);
	}

	umask(0);

	fd = ((maxfd = sysconf(_SC_OPEN_MAX)) > 0) ? maxfd-1 : BD_MAX_CLOSE-1;
	for( ; fd>=0 ; --fd) {
		close(fd);
	}

	close(STDIN_FILENO);

	fd = open(DEV_PATH, O_RDWR);	

	if(fd != STDIN_FILENO) exit(EXIT_FAILURE);

	if(dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO) exit(EXIT_FAILURE);

	if(dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO) exit(EXIT_FAILURE);
}

void sig_term_handler(){
	/*
		SIGTERM signal should result in an orderly shutdown of the daemon.	
	*/

	sig_term = 1;
}

void sig_hub_handler(){
	/*
		SIGHUP signal provides a way to trigger the daemon to reinitialize itself 
		by rereading its configuration file and reopening any log files it may be using.
	*/

	sig_hub = 1;
}

int is_double_instantiation(){
	against_double_instantiation = sem_open(SEM_NAME, O_RDWR | O_CREAT | O_EXCL, 0666, 1);

	if(against_double_instantiation == SEM_FAILED){
		fprintf(log_filep, "Double instantiation error\n");
		return -1;
	}

	return 0;
}
