#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STR_SIZE 15

typedef enum pokemon {
	charmander, pikachu, squirtle, bulnasaur, pidgeotto ,ratata, mug, caterpie, zubat, krabby, empty, MAX_POKEMON
}pokemon;

typedef enum attack_type{
	none, linear, quadratic
}attack_type;

int length(char *str);
int strCompare(char *str1, char *str2);
void pokedex(char *pokemon_name[MAX_POKEMON], int range[], attack_type type[], int attack_power[], int stamina[]);
int findPokemon(char *pokemon_name[MAX_POKEMON], char nameToSearch[]);
void printAttackType(attack_type type);
void oaks_laboratory(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pokemons, int ownerOfPokemon[MAX_POKEMON]);
void show_pokemons(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], int ownerOfPokemon[MAX_POKEMON]);
void catch_a_pokemon(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pocket, int ownerOfPokemon[MAX_POKEMON]);
void release_a_pokemon(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pocket, int ownerOfPokemon[MAX_POKEMON]);
void show_my_pokemons(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pocket);
int isMyPocketEmpty(pokemon *my_pocket);
void battle(char *pokemon_name[MAX_POKEMON], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_pokemons[], int ownerOfPokemon[MAX_POKEMON]);
void set_ai_pokemons(int ai_pokemons[4], int ownerOfPokemon[MAX_POKEMON]);
void initMap(int map[8][8], char *pokemon_name[MAX_POKEMON], pokemon user_pokemons[], int ai_pokemons[4], int my_coor[4][2], int ai_coor[4][2]);
void initStamina(int stamina[], int map_stamina[8][8], int my_coor[4][2], int ai_coor[4][2], pokemon user_pokemons[], int ai_pokemons[4]);
void show_area(char *pokemon_name[MAX_POKEMON], int map[8][8], int map_stamina[8][8]);
int linear_search(int arr[], int size, int element);
int my_move(int map[8][8], pokemon user_pokemons[], char *pokemon_name[MAX_POKEMON], int map_stamina[8][8], int my_coor[4][2]);
int make_selection(int map[8][8], pokemon user_pokemons[], int *x, int *y);
void move_to(int map[8][8], int map_stamina[8][8], int x, int y, int newX, int newY);
int ai_move(int map[8][8], int ai_pokemons[4], char *pokemon_name[MAX_POKEMON], int map_stamina[8][8], int ai_coor[4][2]);
void attack(int map[8][8], int map_stamina[8][8], int x, int y, int attack_power, attack_type type, int range, int compare(int,int));
int check_game(int map[8][8]);
int greater_equal(int a, int b);
int less(int a, int b);

int main(){

	char *pokemon_name[] = { "Charmander", "PIkachu", "Squirtle", "Bulbasaur", "Pidgeotto", "Ratata", "Mug", "Caterpie", "Zubat", "Krabby", "empty" };
	int range[MAX_POKEMON] = { 1, 3, 4, 3, 2 ,2, 1, 2, 3, 2, 0 };
	attack_type type[MAX_POKEMON] = { quadratic, linear ,linear, linear, quadratic, linear, quadratic, quadratic, linear, linear, none };
	int attack_power[MAX_POKEMON] = { 500, 350, 300, 400, 250, 250, 350, 200, 350, 300, 0 };
	int stamina[MAX_POKEMON] = { 2200, 1500, 1700, 2500, 1900, 2500, 3000, 1200, 1250, 2600, 0 };
	int ownerOfPokemon[MAX_POKEMON] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	pokemon pokemons[15] = { charmander, pikachu, squirtle, bulnasaur, pidgeotto ,ratata, mug, caterpie, zubat, krabby, empty };
	pokemon my_pokemons[4] = {empty,empty,empty,empty};
	srand(time(NULL));

	int quit = 0, selection;
	while( !quit ){
		printf("%s%s%s%s%s",
			"Please select an option to continue:\n",
			"1)	Open Pokedex\n",
			"2)	Go to Oaks Laboratory\n",
			"3)	Enter the tournament\n",
			"4)	Exit :( \n" 
		);

		scanf("%d",&selection);

		switch (selection){
			case 1:
				pokedex(pokemon_name, range, type, attack_power, stamina);
				break;

			case 2:
				oaks_laboratory(pokemon_name, pokemons, my_pokemons, ownerOfPokemon);
				break;

			case 3:
				battle(pokemon_name, range, type, attack_power, stamina, my_pokemons, ownerOfPokemon);
				break;

			case 4:
				quit = 1;
				break;
			
			default:
				printf("invalid selection,try again!!\n");
				break;
		}
	}

	return 0;
}

int length(char *str){

	int l=0;

	while(*str != '\0' && *str != '\n'){
		l++;
		str++;
	}

	return l;
}

int strCompare(char *str1, char *str2){

	if(str1 == NULL || str2 == NULL){
		return -101; //ERROR
	}

	while(*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
		++str1, ++str2;

	return *str1 - *str2;
}

void pokedex(char *pokemon_name[MAX_POKEMON], int range[], attack_type type[], int attack_power[], int stamina[]){
	int quit = 0, index;
	char nameToSearch[STR_SIZE];


	while( !quit ){
		printf("Please type name of the Pokemon (type exit to close Pokedex):");
		scanf("%s",nameToSearch);

		if(strCompare("exit", nameToSearch) == 0 ) return;

		index = findPokemon(pokemon_name,nameToSearch);

		if(index != -1){
			printf("%-6s: %s\n","Name",nameToSearch);
			printf("%-13s: ","A.Type ");
			printAttackType(type[index]);
			printf("%-13s: %d\n","Range ",range[index]);
			printf("%-13s: %d\n","A. Power",attack_power[index]);
			printf("%-13s: %d\n","Stamina",stamina[index]);
		}
		else{
			printf("couldn't be found ! \n");
		}
	}
}

int findPokemon(char *pokemon_name[MAX_POKEMON], char nameToSearch[]){
	for(int i=0; i < MAX_POKEMON ; ++i){
		if(strCompare(pokemon_name[i],nameToSearch) == 0){
			return i;
		}
	}

	return -1;
}

void printAttackType(attack_type type){
	switch (type){
		case linear :
			printf("linear\n");
			break;
		case quadratic :
			printf("quadratic\n");
			break;
		case none :
			printf("none\n");
			break;
	}
}

void oaks_laboratory(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pokemons, int ownerOfPokemon[MAX_POKEMON]){
	int quit = 0, selection;
	while( !quit ){
		printf("%s%s%s%s%s%s",
			"Welcome to Laboratory of professor oak,How can I help you ?\n",
			"1) Show Pokomons\n",
			"2) Catch a Pokemon\n",
			"3) Release a Pokemon\n",
			"4) Show my pocket\n",
			"5) Back\n"
		);
	
		scanf("%d",&selection);

		switch (selection){
			case 1:
				show_pokemons(pokemon_name, pokemons, ownerOfPokemon);
				break;

			case 2:
				catch_a_pokemon(pokemon_name, pokemons, my_pokemons, ownerOfPokemon);
				break;

			case 3:
				release_a_pokemon(pokemon_name, pokemons, my_pokemons, ownerOfPokemon);
				break;

			case 4:
				show_my_pokemons(pokemon_name, pokemons, my_pokemons);
				break;

			case 5:
				quit = 1;
				break;

			default:
				printf("invalid selection,try again!!\n");
				break;
		}
	}
}

void show_pokemons(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], int ownerOfPokemon[MAX_POKEMON]){
	for(int i=0 ; i < MAX_POKEMON - 1 ; ++i){
		if(ownerOfPokemon[i] == 0)
			printf("%d - %s\n", i, pokemon_name[i]);
	}
}

void catch_a_pokemon(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pocket, int ownerOfPokemon[MAX_POKEMON]){
	int index = -1;
	int pokemonID ;

	for(int i=0 ; i<4 ; ++i){
		if(my_pocket[i] == empty){
			index = i;
			i = 5; //break;
		}
	}
	if(index == -1){
		printf("your packet is full !\n");
		return;
	}
	show_pokemons(pokemon_name, pokemons, ownerOfPokemon);

	printf("Enter pokemon ID : ");
	scanf("%d",&pokemonID);

	if( pokemonID < MAX_POKEMON-1 && pokemonID >= 0){
		if(ownerOfPokemon[pokemonID] == 0){
			ownerOfPokemon[pokemonID] = 1;
			my_pocket[index] = pokemons[pokemonID];
			printf("%s is catched\n",pokemon_name[pokemonID]);
		}
		else{
			printf("pokemon couldn't be catched (already catched pokemon)\n");
		}
	}
	else{
		printf("pokemon couldn't be catched (invalid ID)\n");
	}
}

void release_a_pokemon(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pocket, int ownerOfPokemon[MAX_POKEMON]){
	int pokemonID ;
	int index = -1;

	if( isMyPocketEmpty(my_pocket) ){
		printf("your pocket is empty !\n");
		return;
	}

	show_my_pokemons(pokemon_name, pokemons, my_pocket);

	printf("pokemon Id : ");
	scanf("%d", &pokemonID);

	if(pokemonID >= MAX_POKEMON-1 || pokemonID < 0){
		printf("invalid pokemon Id !\n");
		return;
	}

	for(int i=0 ; i<4 ; ++i){
		if(pokemons[pokemonID] == my_pocket[i]){
			index = i;
			i = 5; // break
		}
	}

	if(index != -1){
		printf("%s is released\n", pokemon_name[my_pocket[index]]);
		ownerOfPokemon[my_pocket[index]] = 0;
		my_pocket[index] = empty;
	}
	else{
		printf("This pokemon is not in your packet !\n");
	}
}

void show_my_pokemons(char *pokemon_name[MAX_POKEMON], pokemon pokemons[], pokemon *my_pocket){

	if( isMyPocketEmpty(my_pocket) ){
		printf("your pocket is empty !\n");
	}

	for(int i=0 ; i<4 ; ++i){
		if(my_pocket[i] != empty){
			printf("%d - %s\n",my_pocket[i],pokemon_name[my_pocket[i]]);
		}
	}
}

int isMyPocketEmpty(pokemon *my_pocket){
	int n=0;
	for(int i=0 ; i<4;++i){
		if(my_pocket[i] == empty){
			++n;
		}
	}

	return n == 4 ;
}

void battle(char *pokemon_name[MAX_POKEMON], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_pokemons[], int ownerOfPokemon[MAX_POKEMON]){

	int map[8][8];
	int ai_pokemons[4];

	int ai_coor[4][2];
	int my_coor[4][2];

	int map_stamina[8][8];

	int user_turn = 1;

	for(int i=0 ; i<4 ; ++i){
		if(user_pokemons[i] == empty){
			printf("you have to have at least 4 pokemon to join this tournament !\n");
			return;
		}
	}

	set_ai_pokemons(ai_pokemons, ownerOfPokemon);
	initMap(map, pokemon_name, user_pokemons, ai_pokemons, my_coor, ai_coor);
	initStamina(stamina, map_stamina, my_coor, ai_coor, user_pokemons, ai_pokemons);
	show_area(pokemon_name, map, map_stamina);

	while(check_game(map)){
		if(user_turn){
			int p = my_move(map, user_pokemons, pokemon_name, map_stamina, my_coor);
			attack(map, map_stamina, my_coor[p][0], my_coor[p][1], attack_power[user_pokemons[p]], type[user_pokemons[p]], range[user_pokemons[p]], greater_equal);
		}
		else{
			int a = ai_move(map, ai_pokemons, pokemon_name, map_stamina, ai_coor);
			attack(map, map_stamina, ai_coor[a][0], ai_coor[a][1], attack_power[ai_pokemons[a]], type[ai_pokemons[a]], range[ai_pokemons[a]], less);
		}
		user_turn = !user_turn;
		show_area(pokemon_name, map, map_stamina);
	}
}

void set_ai_pokemons(int ai_pokemons[4], int ownerOfPokemon[MAX_POKEMON]){
	
	int pool[MAX_POKEMON-5];
	int j = 0;
	int randNum;

	for(int i=0 ; i<MAX_POKEMON-1 ; ++i){
		if(!ownerOfPokemon[i]){
			pool[j++] = i;
		}
	}

	j = MAX_POKEMON-5;
	for(int i=0 ; i<4 ; ++i){
		randNum = rand()%(j-i);
		ai_pokemons[i] = pool[randNum];
		pool[randNum] = pool[j-i-1];
	}
}

void initMap(int map[8][8], char *pokemon_name[MAX_POKEMON], pokemon user_pokemons[], int ai_pokemons[4], int my_coor[4][2], int ai_coor[4][2]){
	
	int pool[16];
	int randNum;
	int coor;
	int j = 16;
	
	for(int i=0 ; i<16 ; ++i){
		pool[i] = i;
	}

	for(int i=0 ; i<4 ; ++i){
		randNum = rand()%(j-i);
		coor = pool[randNum];
		pool[randNum] = pool[j-i-1];

		ai_coor[i][0] = coor % 8;
		ai_coor[i][1] = coor / 8 + 6;
	}
	
	/*
	for(int i=0 ; i<4 ; ++i){
		printf("%s %d %d\n", pokemon_name[ai_pokemons[i]], ai_coor[i][0], ai_coor[i][1]);
	}
	*/

	printf("\n\ncoordinate system is considered as:\n");
	/*
	-------> +x
	|
	|
	|
	v
	+y
	*/
	printf("-------> +x\n");
	printf("|\n|\n|\nv\n+y\n\n\n");

	for(int i=0 ; i<4 ; ++i){
		do{
			printf("x coordinate of %s: ", pokemon_name[user_pokemons[i]]);
			scanf("%d", &my_coor[i][0]);
			if(my_coor[i][0]<0 || my_coor[i][0]>7)
				printf("invalid coordinate!!\n");
		}while(my_coor[i][0]<0 || my_coor[i][0]>7);

		do{
			printf("y coordinate of %s: ", pokemon_name[user_pokemons[i]]);
			scanf("%d", &my_coor[i][1]);
			if(my_coor[i][1]<0 || my_coor[i][1]>1)
				printf("invalid coordinate!!\n");
		}while(my_coor[i][1]<0 || my_coor[i][1]>1);

		for(int j=0 ; j<i ; j++){
			if(my_coor[j][0]==my_coor[i][0] && my_coor[j][1]==my_coor[i][1]){
				printf("invalid coordinate!!!\n");
				--i;
				j=i; // break
			}
		}
	}

	/*
	for(int i=0 ; i<4 ; ++i){
		printf("%s %d %d\n", pokemon_name[user_pokemons[i]], my_coor[i][0], my_coor[i][1]);
	}
	*/

	for(int i=0 ; i<8 ; ++i){
		for(j=0 ; j<8 ; ++ j){
			map[i][j] = empty;
		}
	}

	for(int i=0 ; i<4 ; ++i){
		map[my_coor[i][1]][my_coor[i][0]] = user_pokemons[i];
		map[ai_coor[i][1]][ai_coor[i][0]] = ai_pokemons[i] + MAX_POKEMON; // to be able to detect the opponent pokemons
	}

	/*
	for(int i=0 ; i<8 ; ++i){
		for(j=0 ; j<8 ; ++ j){
			printf("%d\t", map[i][j]);
		}
		printf("\n");
	}
	*/
}

void initStamina(int stamina[], int map_stamina[8][8], int my_coor[4][2], int ai_coor[4][2], pokemon user_pokemons[], int ai_pokemons[4]){
	for(int i=0 ; i<8 ; ++i){
		for(int j=0 ; j<8 ; ++j){
			map_stamina[i][j]=0;
		}
	}

	for(int i=0 ; i<4 ; ++i){
		map_stamina[my_coor[i][1]][my_coor[i][0]] = stamina[user_pokemons[i]];
		map_stamina[ai_coor[i][1]][ai_coor[i][0]] = stamina[ai_pokemons[i]];
	}
}

void show_area(char *pokemon_name[MAX_POKEMON], int map[8][8], int map_stamina[8][8]){
	int i, j;
	for(i=0;i<8;i++){
		printf("-------");
	}
	printf("-\n");
	for(i=0;i<8;i++){	
		for(j=0;j<8;j++){
			if(map[i][j]==empty){
				printf("|      ");
			}
			else if(map[i][j] >= MAX_POKEMON){
				printf("|  %c%c  ", pokemon_name[map[i][j]-MAX_POKEMON][0]+32, pokemon_name[map[i][j]-MAX_POKEMON][1]);
			}
			else{
				printf("|  %c%c  ", pokemon_name[map[i][j]][0], pokemon_name[map[i][j]][1]);
			}
		}
		printf("|\n");
		for(j=0;j<8;j++){
			if(map[i][j]==empty){
				printf("|      ");
			}

			else{
				printf("|(%4d)", map_stamina[i][j]);
			}
		}
		printf("|\n");
		for(j=0;j<8;j++){
			printf("-------");
		}
		printf("-\n");
	}
}

int linear_search(int arr[], int size, int element){
	for(int i=0 ; i<size ; ++i){
		if(arr[i]==element){
			return i;
		}
	}
	return -1;
}

int my_move(int map[8][8], pokemon user_pokemons[], char *pokemon_name[MAX_POKEMON], int map_stamina[8][8], int my_coor[4][2]){

	int x, y, index;
	int direction;
	int step;
	int flag = 1;

	index = make_selection(map, user_pokemons, &x, &y);
	printf("you selected %s.\n", pokemon_name[user_pokemons[index]]);

	while(flag){
		do{
			printf("0) don't move \n1) one block \n2) two block\n");
			printf("how many block do you want to move:");
			scanf("%d",&step);
			if(step<0 || step>2){
				printf("invalid selection,try again!!\n");
			}
		}while(step<0 || step>2);

		if(!step) return index;

		printf("\n%s%s%s%s%s%s%s",
			"       8			\n",
			"       ^			\n",
			"       |			\n",
			"4 <---------> 6	\n",
			"       |			\n",
			"       v			\n",
			"       2			\n"
		);

		printf("select a direction\n");
		scanf("%d", &direction);

		switch(direction){
			case 's':
			case 2:
				if(y+step > 7){
					printf("Please stay in area!!\n");
				}
				else if(map[y+step][x] != empty){
					printf("There is an another pokemon on your destination!!\n");
				}
				else{
					move_to(map, map_stamina, x, y, x, y+step);
					my_coor[index][1] = y+step;
					flag = 0;
				}
				break;

			case 'a':
			case 4:
				if(x-step < 0){
					printf("Please stay in area!!\n");
				}
				else if(map[y][x-step] != empty){
					printf("There is an another pokemon on your destination!!\n");
				}
				else{
					move_to(map, map_stamina, x, y, x-step, y);
					my_coor[index][0] = x-step;
					flag = 0;
				}
				break;

			case 'd':
			case 6:
				if(x+step > 7){
					printf("Please stay in area!!\n");
				}
				else if(map[y][x+step] != empty){
					printf("There is an another pokemon on your destination!!\n");
				}
				else{
					move_to(map, map_stamina, x, y, x+step, y);
					my_coor[index][0] = x+step;
					flag = 0;
				}
				break;

			case 'w':
			case 8:
				if(y-step < 0){
					printf("Please stay in area!!\n");
				}
				else if(map[y-step][x] != empty){
					printf("There is an another pokemon on your destination!!\n");
				}
				else{
					move_to(map, map_stamina, x, y, x, y-step);
					my_coor[index][1] = y-step;
					flag = 0;
				}
				break;
			
			default:
				printf("invalid direction!!\n");
				break;
		}
	}
	return index;
}

int make_selection(int map[8][8], pokemon user_pokemons[], int *x, int *y){
	int index=-1;
	do{
		printf("select a pokemon(Enter the coordinate of pokemon you want to move): ");
		
		do{
			scanf("%d%d", x, y);
			if(*x<0 || *y<0 || *x>7 || *y>7){
				printf("invalid selection try again: ");
			}
		}while(*x<0 || *y<0 || *x>7 || *y>7);

		if(map[*y][*x]==empty){
			printf("invalid selection (empty)!!\n");
		}
		else if(map[*y][*x]>=MAX_POKEMON){
			printf("invalid selection (not your pokemon)!!\n");	
		}

	}while(map[*y][*x]==empty || map[*y][*x]>=MAX_POKEMON);

	for(int i=0 ; i<4 ; ++i){
		if(user_pokemons[i]==map[*y][*x]){
			index = i;
		}
	}
	return index;
}

void move_to(int map[8][8], int map_stamina[8][8], int x, int y, int newX, int newY){
	map[newY][newX] = map[y][x];
	map[y][x] = empty;

	map_stamina[newY][newX] = map_stamina[y][x];
	map_stamina[y][x] = 0;
}

int ai_move(int map[8][8], int ai_pokemons[4], char *pokemon_name[MAX_POKEMON], int map_stamina[8][8], int ai_coor[4][2]){
	int index, step, direction;
	int flag = 1;
	int pool[4] = {0, 1, 2, 3};
	int j = 4;

	for(int i=0 ; i<4 ; ++i){
		index = pool[rand() % j];
		if(map[ai_coor[index][1]][ai_coor[index][0]] != empty){
			printf("ai selected %s.\n", pokemon_name[ai_pokemons[index]]);
			i=4; // break
		}
		else{
			pool[index] = pool[j-1];
			j--;
		}
	}

	if(!j) printf("SOME ERROR HERE\n");

	int x = ai_coor[index][0];
	int y = ai_coor[index][1];

	flag = 1;
	while(flag){
		step = rand() % 3;
		direction = rand() % 4;

		if(!step){
			printf("0 step\n");
			return index;
		}

		switch(direction){
			case 0:
				if(y+step <= 7 && map[y+step][x] == empty){
					move_to(map, map_stamina, x, y, x, y+step);
					ai_coor[index][1] = y+step;
					flag = 0;
				}
				break;
			
			case 1:
				if(x-step >= 0 && map[y][x-step] == empty){
					move_to(map, map_stamina, x, y, x-step, y);
					ai_coor[index][0] = x-step;
					flag = 0;
				}
				break;
			
			case 2:
				if(x+step <= 7 && map[y][x+step] == empty){
					move_to(map, map_stamina, x, y, x+step, y);
					ai_coor[index][0] = x+step;
					flag = 0;
				}
				break;
			
			case 3:
				if(y-step >= 0 && map[y-step][x] == empty){
					move_to(map, map_stamina, x, y, x, y-step);
					ai_coor[index][1] = y-step;
					flag = 0;
				}
				break;
			
			default:
				break;
		}
	}
	printf("%d step in %d direction\n", step, 2*direction+2);
	return index;
}

void attack(int map[8][8], int map_stamina[8][8], int x, int y, int attack_power, attack_type type, int range, int compare(int,int)){
	int flag = 1;

	if(type == linear){
		for(int i=1 ; i<=range && flag ; ++i){
			if(x+i <= 7 && compare(map[y][x+i], MAX_POKEMON)){
				map_stamina[y][x+i] -= attack_power;
				if(map_stamina[y][x+i]<=0){
					map[y][x+i] = empty;
				}
				flag = 0;
			}
			if(x-i >= 0 && compare(map[y][x-i], MAX_POKEMON)){
				map_stamina[y][x-i] -= attack_power;
				if(map_stamina[y][x-i]<=0){
					map[y][x-i] = empty;
				}
				flag = 0;
			}
			if(y+i <= 7 && compare(map[y+i][x], MAX_POKEMON)){
				map_stamina[y+i][x] -= attack_power;
				if(map_stamina[y+i][x]<=0){
					map[y+i][x] = empty;
				}
				flag = 0;
			}
			if(y-i >= 0 && compare(map[y-i][x], MAX_POKEMON)){
				map_stamina[y-i][x] -= attack_power;
				if(map_stamina[y-i][x]<=0){
					map[y-i][x] = empty;
				}
				flag = 0;
			}
		}
	}
	else if(type == quadratic){
		int l = x-range;
		int r = x+range;
		int u = y-range;
		int d = y+range;

		if(l < 0){
			l = 0;
		}
		if(r > 7){
			r = 7;
		}
		if(u < 0){
			u = 0;
		}
		if(d > 7){
			d = 7;
		}

		for(int i=u ; i<=d ; ++i){
			for(int j=l ; j<=r ; ++j){
				if(compare(map[i][j], MAX_POKEMON)){
					map_stamina[i][j] -= attack_power;
					if(map_stamina[i][j] <= 0){
						map[i][j] = empty;
					}
				}
			}
		}
	}

	else{
		printf("invalid attack type !!!\n");
		exit(-1);
	}
}

int greater_equal(int a, int b){
	return a >= b;
}

int less(int a, int b){
	return a < b;
}

int check_game(int map[8][8]){
	int my = 0;
	int ai = 0;

	for(int i=0 ; i<8 ; ++i){
		for(int j=0 ; j<8 ; ++j){
			if(map[i][j] >= MAX_POKEMON){
				++ai;
			}
			else if(map[i][j] != empty){
				++my;
			}
		}
	}

	if(ai == 0){
		printf("user win !!\n");
		return 0;
	}
	if(my == 0){
		printf("ai win !!\n");
		return 0;
	}

	return 1;
}
