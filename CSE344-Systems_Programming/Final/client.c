#include "client.h"

int main(int argc, char *argv[]){

	init_signals();

	if(parse_arguments(argc, argv) == -1){
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	run_client(argv[0]);

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
}

void print_usage(char *exe_name){
	fprintf(stderr, "%sUsage: %s -i id -a 127.0.0.1 -p PORT -o pathToQueryFile\n", get_timestamp(), exe_name);

	fprintf(stderr, "%s%s%s%s%s",
		get_timestamp(),
		"-a: IPv4 address of the machine running the server\n",
		"-p: port number at which the server waits for connections (>1000, the first 1000 are reserved to kernel processes)\n",
		"-o: relative or absolute path of the file containing an arbitrary number of queries\n",
		"-i: integer id of the client (>=1)\n"
	);
}

int parse_arguments(int argc, char *argv[]){
	int a0, a1, a2, a3;
	a0 = a1 = a2 = a3 = 1;

	if(argc != 9){
		fprintf(stderr, "%sinvalid argumet\n",get_timestamp());
		return -1;
	}

	char c;
	while((c = getopt(argc, argv, "i:a:p:o:")) != -1){
		switch(c){
			case 'i':
				_id = atoi(optarg);
				if(_id < 1){
					fprintf(stderr, "%sinteger id of the client (>=1)\n", get_timestamp());
					return -1;
				}
				a0 = 0;
				break;
			case 'a':
				_host = optarg;
				a1 = 0;
				break;
			case 'p':
				_port = optarg;
				if(atoi(_port) <= 1000){
					fprintf(stdout, "%sinvalid port number (>1000, the first 1000 are reserved to kernel processes)\n", get_timestamp());
					return -1;
				}
				a2 = 0;
				break;
			case 'o':
				_pathToQueryFile = optarg;
				a3 = 0;
				break;
			case '?':
				return -1;
			default :
				return -1;
		}
	}

	if(a0 || a1 || a2 || a3){
		fprintf(stderr, "%sargument error\n", get_timestamp());
		return -1;
	}

	/*
	fprintf(stdout, "_id: %d\n_port: %s\n_pathToQueryFile: %s\n_host.s_addr: %s\n", 
		_id,
		_port,
		_pathToQueryFile,
		_host
	);*/

	return 0;
}

void run_client(char *exe_name){
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(_port));
	if(inet_aton(_host, &addr.sin_addr) == 0){
		fprintf(stderr, "%sinvalid ipv4 address\n", get_timestamp());
		print_usage(exe_name);
		exit(EXIT_FAILURE);
	}

	
	int fd;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	fprintf(stdout, "%sClient-%d connecting to %s:%s\n", get_timestamp(), _id, _host, _port);

	int go;
	if(connect(fd, (struct sockaddr *) &addr, sizeof(addr)) != -1){
		read(fd, &go, sizeof(int));
	}
	else{
		close(fd);
		fprintf(stderr, "%sconnection failed\n", get_timestamp());
		perror("connection");
		close(fd);
		exit(EXIT_FAILURE);
	}

	handle_queries(fd);

	close(fd);
}

void handle_queries(int fd){
	char req_buf[BUFSIZ];
	bzero(req_buf, BUFSIZ);
	int req_len=0;

	char resp_buf[MAX_LINE_LEN];
	bzero(resp_buf, MAX_LINE_LEN);
	int resp_len=0;
	int eof_len = -1;

	int id_of_query;

	int counter=0;
	int is_select=0;

	int record_number=0;

	clock_t start;

	FILE *filep = fopen(_pathToQueryFile, "r");
	if(filep == NULL){
		perror("file open");
		exit(EXIT_FAILURE);
	}

	while(fgets(req_buf, BUFSIZ, filep)){
		sscanf(req_buf, "%d %[^\n]s", &id_of_query, req_buf);
		if( id_of_query != _id) continue;

		fprintf(stdout, "%sClient-%d connected and sending query '%s'\n", get_timestamp(), _id, req_buf);

		req_len = strlen(req_buf) + 1;
		write(fd, &req_len, sizeof(int));
		write(fd, req_buf, req_len);
		//write(fd, buf, BUFSIZ);

		read(fd, &is_select, sizeof(int));

		if(is_select){
			start = clock();
			read(fd, &resp_len, sizeof(int));
			//printf("resp_len: %d\n", resp_len);
			for(int i=0 ; i<resp_len ; ++i){
				read(fd, resp_buf, MAX_LINE_LEN);
				fprintf(stdout, "%s\n", resp_buf);
				bzero(resp_buf, MAX_LINE_LEN);

			}
			read(fd, &record_number, sizeof(int));
			fprintf(stdout, "%sServer’s response to Client-%d is %d records, and arrived in %.3f seconds.\n",
				get_timestamp(),
				_id, record_number,
				((double)(clock() - start) / CLOCKS_PER_SEC) * 10
			);
		}
		else{
			read(fd, &record_number, sizeof(int));
			fprintf(stdout, "%s%d record is updated\n", get_timestamp(), record_number);
		}

		bzero(req_buf, BUFSIZ);

		++counter;
	}
	write(fd, &eof_len, sizeof(int));

	fprintf(stdout, "%sA total of %d queries were executed, client is terminating.\n", get_timestamp(), counter);

	fclose(filep);
}

char *get_timestamp(){
	time_t curr_time;
	struct tm *s_time;
	curr_time = time(NULL);
	s_time = localtime(&curr_time);
	sprintf(curr_timestamp, "%02d-%02d-%02d -:", s_time->tm_hour, s_time->tm_min, s_time->tm_sec);
	return curr_timestamp;
}
