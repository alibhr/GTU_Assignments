#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int get_line_size(char *line);
void fill_board_random(char *board[32]);
void fill_from_array(char *board[32], char *dict[DICT_SIZE], int coord[DICT_SIZE][4]);
void show_board(char *board[32]);
void read_and_search(char *board[32], char *dict[DICT_SIZE], int coord[DICT_SIZE][4]);
int lenght_of(char word[WORD_LEN]);
int compare(char word_1[WORD_LEN], char word_2[WORD_LEN]);
void copy_string(char *source, char *destination);
void remove_newline(char *line);
void print_dictionary(char *dict[]);
void print_coord(int coord[DICT_SIZE][4]);

int main(){
	char *dict[DICT_SIZE];
	int coord[DICT_SIZE][4];    
	char line[LINE_LEN];
	char *board[32];
	int i;
	FILE *fp = fopen("word_hunter.dat", "r");
	if(fp==NULL){
		printf("word_hunter.dat doesn't exist!\n" );
	}
	for(i=0;i<32;i++){
		board[i]=(char*)malloc(sizeof(char)*32);
	}
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
	//print_dictionary(dict);
	//print_coord(coord);
	
	fill_board_random(board);
	fill_from_array(board, dict, coord);
	show_board(board);
	read_and_search(board, dict, coord);
	
	return 0;
}

int get_line_size(char *line){
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination){
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
	}
	// terminate string
	*dst_iter = '\0';
}

void remove_newline(char *line){
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]){
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]){
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

void show_board(char *board[32]){
	int i,j;
	printf("    ");
	for(i=0;i<15;i++){
		printf("%-2d  ", i);
	}
	printf("\n\n");
	for(i=0;i<15;i++){
		printf("%-2d  ",i);
		for(j=0;j<15;j++){
			printf("%c   ", board[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");
}

void fill_board_random(char *board[32]){
	int i=0,j=0;

	srand(time(NULL));
	for(i=0;i<32;i++){
		for(j=0;j<32;j++){
			board[i][j]=(rand()%26)+97;
		}
	}
}

void fill_from_array(char *board[32], char *dict[DICT_SIZE], int coord[DICT_SIZE][4]){
	int i=0,j=0;

	for(i=0;i<DICT_SIZE;i++){
		if(coord[i][1]==coord[i][3] && coord[i][0]<coord[i][2]){/*from top to bottom*/
			for(j=0;j<(coord[i][2]-coord[i][0]+1);j++){
				*(board[coord[i][0]+j]+coord[i][1])=*(dict[i]+j);
			}
		}
		else if(coord[i][1]==coord[i][3] && coord[i][0]>coord[i][2]){/*from bottom to top*/
			for(j=0;j<(coord[i][0]-coord[i][2]+1);j++){
				*(board[coord[i][0]-j]+coord[i][1])=*(dict[i]+j);
			}
		}
		else if(coord[i][0]==coord[i][2] && coord[i][1]<coord[i][3]){/*from left to right*/
			for(j=0;j<(coord[i][3]-coord[i][1]+1);j++){
				*(board[coord[i][0]]+coord[i][1]+j)=*(dict[i]+j);
			}
		}
		else if(coord[i][0]==coord[i][2] && coord[i][1]>coord[i][3]){/*from right ro left*/
			for(j=0;j<(coord[i][1]-coord[i][3]+1);j++){
				*(board[coord[i][0]]+coord[i][1]-j)=*(dict[i]+j);
			}
		}
		else if(coord[i][0]<coord[i][2] && coord[i][1]<coord[i][3]){/*to southeast*/
			for(j=0;j<(coord[i][3]-coord[i][1]+1);j++){
				*(board[coord[i][0]+j]+coord[i][1]+j)=*(dict[i]+j);
			}
		}
		else if(coord[i][0]>coord[i][2] && coord[i][1]<coord[i][3]){/*to northeast*/
			for(j=0;j<(coord[i][3]-coord[i][1]+1);j++){
				*(board[coord[i][0]-j]+coord[i][1]+j)=*(dict[i]+j);
			}	
		}
		else if(coord[i][0]>coord[i][2] && coord[i][1]>coord[i][3]){/*to northwest*/
			for(j=0;j<(coord[i][1]-coord[i][3]+1);j++){
				*(board[coord[i][0]-j]+coord[i][1]-j)=*(dict[i]+j);
			}
		}
		else if(coord[i][0]<coord[i][2] && coord[i][1]>coord[i][3]){/*to northwest*/
			for(j=0;j<(coord[i][1]-coord[i][3]+1);j++){
				*(board[coord[i][0]+j]+coord[i][1]-j)=*(dict[i]+j);
			}
		}
	}
}

void read_and_search(char *board[32], char *dict[DICT_SIZE], int coord[DICT_SIZE][4]){
	int i,counter=0,flag=1,check=0,lenght_of_guess,game=0;
	int guess_x=0,guess_y=0;
	char *guess_word=(char*)malloc(sizeof(char)*WORD_LEN);
	while(flag){
		printf("%d\n", game);
		printf("Enter the word you found(type 'exit' to close the game): ");
		scanf(" %s",guess_word);
		if(compare(guess_word,"exit")==0 || game==DICT_SIZE){
			flag=0;
		}
		else{
			printf("Enter the coordinate of the word you found: ");
			scanf("%d%d",&guess_x,&guess_y);
		}
		lenght_of_guess=lenght_of(guess_word);
		counter=0;
		check=0;
		for(i=0;i<DICT_SIZE;i++){/*controlling that whether the word which is taken there is in dictionary.*/
			if(compare(guess_word,dict[i])==0){
				counter++;
			}
		}
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess;i++){/*controlling from beginning of the word to bottom*/
			if(guess_word[i]==board[guess_x+i][guess_y]){
				check++;	
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x+i][guess_y]=board[guess_x+i][guess_y]-32;//converting the word to upper casae.
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess;i++){/*controlling from beginning of the word to left*/
			if(guess_word[i]==board[guess_x][guess_y+i]){
				check++;	
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x][guess_y+i]=board[guess_x][guess_y+i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && guess_x-lenght_of_guess+1>=0;i++){/*controlling from bottom to top*/
			if(guess_word[i]==board[guess_x+i-lenght_of_guess+1][guess_y]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess && guess_x-lenght_of_guess+1>=0;i++){//index of the array can't be negative so ı have to to this test.
				board[guess_x-lenght_of_guess+1+i][guess_y]=board[guess_x+i-lenght_of_guess+1][guess_y]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && guess_y+i-lenght_of_guess+1>=0;i++){/*controlling from end of the word to right*/
			if(guess_word[i]==board[guess_x][guess_y+i-lenght_of_guess+1]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess && guess_y+i-lenght_of_guess+1>=0;i++){
				board[guess_x][guess_y+i-lenght_of_guess+1]=board[guess_x][guess_y+i-lenght_of_guess+1]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess;i++){/*controlling from beginning of the word to southeast*/
			if(guess_word[i]==board[guess_x+i][guess_y+i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x+i][guess_y+i]=board[guess_x+i][guess_y+i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess&&guess_x-lenght_of_guess+1+i>0&&guess_y-lenght_of_guess+1+i>=0;i++){/*controlling from end of the word to northeast*/
			if(guess_word[i]==board[guess_x-lenght_of_guess+1+i][guess_y-lenght_of_guess+1+i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x-lenght_of_guess+1+i][guess_y-lenght_of_guess+1+i]=board[guess_x-lenght_of_guess+1+i][guess_y-lenght_of_guess+1+i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && lenght_of_guess-1-i>=0;i++){//yatayda ters kelimeyi soldan sağa kontrol
			if(guess_word[lenght_of_guess-1-i]==board[guess_x][guess_y+i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x][guess_y+i]=board[guess_x][guess_y+i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && guess_y-i >= 0;i++){//yatayda ters kelimeyi sağdan sola kontrol
			if(guess_word[i]==board[guess_x][guess_y-i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x][guess_y-i]=board[guess_x][guess_y-i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;		
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && lenght_of_guess-1-i >= 0;i++){//dikeyde ters kelimeyi yukarıdan aşağıya
			if(guess_word[lenght_of_guess-1-i]==board[guess_x+i][guess_y]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x+i][guess_y]=board[guess_x+i][guess_y]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && guess_x-i >= 0;i++){//dikeyde ters kelimeyi aşağıdan yukarıya
			if(guess_word[i]==board[guess_x-i][guess_y]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x-i][guess_y]=board[guess_x-i][guess_y]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && guess_x-i >= 0;i++){/*controlling from beginning to northeast*/
			if(guess_word[i]==board[guess_x-i][guess_y+i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x-i][guess_y+i]=board[guess_x-i][guess_y+i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && lenght_of_guess-1-i >= 0;i++){//sondan güney-batı'ya /*controlling from en of the word to south-west*/
			if(guess_word[lenght_of_guess-1-i]==board[guess_x+i][guess_y-i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x+i][guess_y-i]=board[guess_x+i][guess_y-i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && guess_x-i >= 0 && guess_y-i >= 0;i++){//baştan kuzey-batı'ya /*controlling from beginning to northwest*/
			if(guess_word[i]==board[guess_x-i][guess_y-i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x-i][guess_y-i]=board[guess_x-i][guess_y-i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && lenght_of_guess-1-i >= 0;i++){//sondan güney-doğu'ya /*controlling from end of the word to southeast*/
			if(guess_word[lenght_of_guess-1-i]==board[guess_x+i][guess_y+i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x+i][guess_y+i]=board[guess_x+i][guess_y+i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && guess_y-i >= 0;i++){//baştan güney-batı'ya. /*controlling from beginnig of the word to southwest*/
			if(guess_word[i]==board[guess_x+i][guess_y-i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x+i][guess_y-i]=board[guess_x+i][guess_y-i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;		
/******************************************************************************************************/
		for(i=0;i<lenght_of_guess && lenght_of_guess-1-i >= 0 && guess_x-i >= 0;i++){//sondan kuzey-doğu'ya./*controlling drom end of the word to northeast*/
			if(guess_word[lenght_of_guess-1-i]==board[guess_x-i][guess_y+i]){
				check++;
			}
		}
		if(check==lenght_of_guess && counter==1){
			game++;
			for(i=0;i<lenght_of_guess;i++){
				board[guess_x-i][guess_y+i]=board[guess_x-i][guess_y+i]-32;
			}
			counter=0;
			show_board(board);
		}
		check=0;	
	}
}	


int lenght_of(char word[WORD_LEN]){
	int i=0;
	for(i=0;word[i]!='\0';i++);
	return i;
}

int compare(char word_1[WORD_LEN], char word_2[WORD_LEN]){
	int i=0,counter=0,counter1=0,loop=lenght_of(word_1),loop1=lenght_of(word_2);
	if(loop1<loop){
		loop=loop1;
	}
	for(i=0;i<loop;i++){
		if(word_1[i]!=13 && word_2[i]!=13){
			counter+=word_1[i]-word_2[i];
		}
	}
	for(i=0;i<loop;i++){
		if((word_1[i]==word_2[i] || word_1[i]==word_2[i]-32 || word_1[i]-32==word_2[i]) && word_1[i]!='\r' && word_2[i]!='\r'){/*there is '\r' all of the end of the word in the dict so ı have to do this control*/
			counter1++;
		}
	}
	if(counter1==loop){
		return counter;
	}
	else{
		return 10;
	}
}
