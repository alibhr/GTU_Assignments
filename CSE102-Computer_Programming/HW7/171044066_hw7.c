#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define clear_screen() printf("\e[1;1H\e[2J");//this function clear the screen.
typedef enum player_type{
	noone,
	cap,
	car
}player_type;
typedef enum block_type{
	start,
	property,
	tax,
	punish
}block_type;
typedef struct player{
	player_type type;/*Holds type of  the player.*/
	int current_block_ids;/*Holds player locatin as block id*/
	int owned_block_ids[11];/*Holds property blocks ids that are owned by the user.*/
	int account;/*Holds amount of the current money of the player.*/
	int turn_to_wait;/*Holdsd number of turns to wait if the player got a punishment.*/
	char *name;/*Holds the name of the player.*/
}player;
typedef struct block{
	int block_id;/*Holds id of the blocks.*/
	char *name;/*Holds text of the block that is shown on the top of the  block.*/
	int price;/*if the block is property,holds the price ,if the block is a tax block than holds the tax fee
	and if the block punishment block,then holds the number of turns to wait.*/
	int rent;
	int rent1;/*Holds the rent of a property with one house*/
	int rent2;/*Holds the rent of a property with two house*/
	int rent3;/*Holds the rent of a property with three house*/
	int house_price;/*Holds price of building a house on the block.*/
	int house_count;/*Holds the number of the houses on the block that are already built.*/
	player_type owner;/*Holds the owner of the block*/
	block_type type;/*Holds type of the block*/
}block;

void init_the_board(block board[20]);
void show_board(block board[20],player player1,player player2);
void show_properties(block board[20]);
void buy_property(block *current_block,player *current_player);
void sell_property(block board[20],player *current_player);
void gameplay(block board[20],player player_one,player player_two);
void show_my_properties(block board[20],player current_player);
void pay(block board[20],player *current_player,player *opponent_player);
void buy_house(block *current_block,player *current_player);
int check_the_game(block board[20],player *current_player);

int main(){
	clear_screen();
	srand(time(NULL));
	int i=0;
	block board[20];
/*				{	type	,current_block_ids	,owned_block_ids,account	,turn_to_wait	,name}*/
	player player1={cap		,0					,{}				,100000		,0				,"cap"};
	player player2={car		,0					,{}				,100000		,0				,"car"};
	for(i=0;i<11;i++){//-1 means is gonna be emty area in the array.
		player1.owned_block_ids[i]=-1;
		player2.owned_block_ids[i]=-1;
	}
	init_the_board(board);
	show_board(board,player1,player2);
	gameplay(board,player1,player2);
	return 0;
}
void init_the_board(block board[20]){
	int i=0;
	block board_t[20]={//firs ı filledd this array by initialising.
/*	{id,"name			,price	rent	,rent1	,rent2	,rent3	,house_price,house_count,owner	,type"}	*/
	{0,	"Start"			,0		,0		,0		,0		,0		,0			,0			,noone	,start},
	{1,	"Esenyurt"		,16000	,800	,4000	,9000	,25000	,10000		,0			,noone	,property},
	{2,	"Car Park"		,1500	,1500	,0		,0		,0		,0			,0			,noone	,tax},
	{3,	"Tuzla"			,16500	,850	,4250	,9500	,26000	,12000		,0			,noone	,property},
	{4,	"Arnavutkoy"	,17000	,875	,4500	,10000	,28000	,12000		,0			,noone	,property},
	{5,	"Wait 2 Turn"	,0		,2		,0		,0		,0		,0			,0			,noone	,punish},
	{6,	"Catalca"		,20000	,1000	,5000	,12000	,30000	,13000		,0			,noone	,property},
	{7,	"Beykoz"		,23000	,1100	,5500	,12500	,33000	,13000		,0			,noone	,property},
	{8,	"Car Fix"		,1750	,1750	,0		,0		,0		,0			,0			,noone	,tax},
	{9,	"Maltepe"		,30000	,1350	,7000	,15000	,40000	,15000		,0			,noone	,property},
	{10,"Bills"			,2000	,2000	,0		,0		,0		,0			,0			,noone	,tax},
	{11,"sisli"			,33000	,1500	,8000	,16000	,42000	,16000		,0			,noone	,property},
	{12,"Oil"			,2250	,2250	,0		,0		,0		,0			,0			,noone	,tax},
	{13,"Atasehir"		,35000	,1600	,8500	,17000	,45000	,17000		,0			,noone	,property},
	{14,"Sariyer"		,40000	,1750	,9500	,19000	,48000	,19000		,0			,noone	,property},
	{15,"Wait 1 Turn"	,0		,1		,0		,0		,0		,0			,0			,noone	,punish},
	{16,"Kadikoy"		,43000	,1900	,1100	,21500	,55000	,23000		,0			,noone	,property},
	{17,"Besiktas"		,60000	,2500	,15000	,28000	,60000	,30000		,0			,noone	,property},
	{18,"vocation"		,5000	,5000	,0		,0		,0		,0			,0			,noone	,tax},
	{19,"Bebek"			,70000	,3500	,20000	,35500	,65000	,35000		,0			,noone	,property}
	};
	for(i=0;i<20;i++){//then ı copy all component of this array to actual array.
		board[i].block_id=board_t[i].block_id;
		board[i].name = board_t[i].name;
		board[i].price=board_t[i].price;
		board[i].rent=board_t[i].rent;
		board[i].rent1=board_t[i].rent1;
		board[i].rent2=board_t[i].rent2;
		board[i].rent3=board_t[i].rent3;
		board[i].house_price=board_t[i].house_price;
		board[i].house_count=board_t[i].house_count;		
		board[i].owner=board_t[i].owner;
		board[i].type=board_t[i].type;				
	}
}
void show_board(block board[20],player player1,player player2){
	int i=0,j=0,k=0;
	for(i=0;i<145;i++){//lıne on top
		printf("-");
	}
	printf("\n|");
	for(i=0;i<6;i++){
		printf("\t%-16s%s",board[i].name,"|");
	}
	printf("\n|");
	for(i=0;i<6;i++){
		if(board[i].type==punish || board[i].type==start){
			printf("\t%-16s%s","","|");
		}
		else{
			printf("\t%-5d$%11s",board[i].price,"|");
		}
	}
	printf("\n|");
	for(i=0;i<6;i++){
		if(player1.current_block_ids==i && player2.current_block_ids!=i){
			printf("\t%-16s%s",player1.name,"|");
		}
		else if(player2.current_block_ids==i && player1.current_block_ids!=i){
			printf("\t%-16s%s",player2.name,"|");
		}
		else if(player1.current_block_ids==i && player2.current_block_ids==i){
			printf("\t%s,%s\t\t%s",player1.name,player2.name,"|");
		}
		else {
			printf("\t%-16s%s","","|");
		}
	}
	printf("\n");
	for(i=0;i<145;i++){
		printf("-");
	}	
	printf("\n");
	//first line is up to here.
	i=19;//when i decreasing j will increase in same time.
	j=6;
	while(i>15 && j<10){//this while loop draw the middle of the map.
		printf("|");
		printf("\t%-16s%s",board[i].name,"|");		
		for(k=0;k<12;k++){
			printf("\t");
		}		
		printf("|");
		printf("\t%-16s%s",board[j].name,"|");
		printf("\n|");
		
		if(board[i].type==punish || board[i].type==start){
			printf("\t%-16s%s","","|");
		}
		else{
			printf("\t%-6d%-10s%s",board[i].price,"$","|");
		}
		for(k=0;k<12;k++){
			printf("\t");
		}
		printf("|");
		if(board[j].type==punish || board[j].type==start){
			printf("\t%-16s%s","","|");
		}
		else{
			printf("\t%-6d%-10s%s",board[j].price,"$","|");
		}
		
		printf("\n|");
		if(player1.current_block_ids==i && player2.current_block_ids!=i){
			printf("\t%-16s%s",player1.name,"|");
		}
		else if(player2.current_block_ids==i && player1.current_block_ids!=i){
			printf("\t%-16s%s",player2.name,"|");
		}
		else if(player1.current_block_ids==i && player2.current_block_ids==i){
			printf("\t%s,%s\t\t%s",player1.name,player2.name,"|");
		}
		else {
			printf("\t%-16s%s","","|");
		}
		for(k=0;k<12;k++){
			printf("\t");
		}
		printf("|");
		if(player1.current_block_ids==j && player2.current_block_ids!=j){
			printf("\t%-16s%s",player1.name,"|");
		}
		else if(player2.current_block_ids==j && player1.current_block_ids!=j){
			printf("\t%-16s%s",player2.name,"|");
		}
		else if(player1.current_block_ids==j && player2.current_block_ids==j){
			printf("\t%s,%s\t\t%s",player1.name,player2.name,"|");
		}
		else {
			printf("\t%-16s%s","","|");
		}
		printf("\n");
		if(!(i==16 && j==9)){		
			for(k=0;k<25;k++){
				printf("-");
			}
			for(k=0;k<12;k++){
				printf("\t");
			}		
			for(k=0;k<25;k++){
				printf("-");
			}
			printf("\n");
		}
		else{
			for(k=0;k<145;k++){
				printf("-");
			}
			printf("\n");
		}
		i--; j++;
	}
	//starting of bottom line.
	printf("|");
	for(i=15;i>9;i--){
		printf("\t%-16s%s",board[i].name,"|");
	}
	printf("\n|");
	for(i=15;i>9;i--){
		if(board[i].type==punish || board[i].type==start){
			printf("\t%-16s%s","","|");
		}
		else{
			printf("\t%-6d%s%10s",board[i].price,"$","|");
		}
	}
	printf("\n|");
	for(i=15;i>9;i--){
		if(player1.current_block_ids==i && player2.current_block_ids!=i){
			printf("\t%-16s%s",player1.name,"|");
		}
		else if(player2.current_block_ids==i && player1.current_block_ids!=i){
			printf("\t%-16s%s",player2.name,"|");
		}
		else if(player1.current_block_ids==i && player2.current_block_ids==i){
			printf("\t%s,%s\t\t%s",player1.name,player2.name,"|");
		}
		else {
			printf("\t%-16s%s","","|");
		}
	}
	printf("\n");
	for(i=0;i<145;i++){
		printf("-");
	}
	printf("\n");
}
void show_properties(block board[20]){
	clear_screen();
	int selection=2,i=0,flag=1;
	while(flag){
		printf("Please seleckt a property to see details:\n");
		printf(
		"1 -	Esenyurt	\n"
		"4 -	Arnavutkoy	\n"
		"6 -	Catalca		\n"
		"7 -	Beykoz		\n"
		"9 -	Maltepe		\n"
		"11-	sisli		\n"
		"13-	Atasehir	\n"
		"14-	Sariyer		\n"
		"16-	Kadikoy		\n"
		"17-	Besiktas	\n"
		"19-	Bebek		\n"
		"0 -	Exit		\n"
		);
		selection=2;
		while(board[selection].type!=property && selection!=0){//this loop is continue untill user enter the valid value.
			scanf("%d",&selection);
			if(board[selection].type!=property && selection!=0){
				printf("Try again!\n");
			}
		}
		if(selection==0){
			flag=0;
			clear_screen();
		}
		else{
			clear_screen();
			for(i=0;i<37;i++){
				printf("-");
			}
			printf("\n|\t\t%-20s|\n",board[selection].name);
			for(i=0;i<37;i++){
				printf("-");
			}
			printf("\n");

			printf("|\tRent  \t\t%-5d%-7s|\n",board[selection].rent,"$");
			printf("|\tRent 1\t\t%-5d%-7s|\n",board[selection].rent1,"$");
			printf("|\tRent 2\t\t%-5d%-7s|\n",board[selection].rent2,"$");
			printf("|\tRent 3\t\t%-5d%-7s|\n",board[selection].rent3,"$");
			for(i=0;i<37;i++){
				printf("-");
			}
			printf("\n");
			printf("|\tHouse Price\t%-5d%-7s|\n",board[selection].house_price,"$");
			for(i=0;i<37;i++){
				printf("-");
			}
			printf("\n");
		}
	}
}
void buy_property(block *current_block,player *current_player){
	clear_screen();
	int i=0,yes=0;
	while(current_player->owned_block_ids[i]!=-1){//finding the emty area in the array.
		i++;//index of empty area.
	}
	if(current_block->owner==noone && current_block->type==property && current_player->account >= current_block->price){
		current_block->owner=current_player->type;
		current_player->owned_block_ids[i]=current_block->block_id;
		current_player->account=current_player->account - current_block->price;	
		yes=1;//checking the whether the property could be bought or not.
		printf("property is bought!\n");
	}
	else if(current_block->owner!=noone){
		printf("The block has already sold!\n");
	}
	else if(current_block->type!=property){
		printf("you can't buy this block!\n");
	}
	else if(current_player->account < current_block->price){
		printf("insufficient account!\n");
	}
	else{
		printf("There is something wrong!\n");
	}
	if(yes){
		yes=-1;
		printf("Do you want to build one or more house on the property.(1-yes,0-no)\n");
		while(yes<0 || yes>1){
			scanf("%d",&yes);
			if(yes<0 || yes>1){
				printf("Try again!\n");
			}
		}
		if(yes==1){
			buy_house(current_block,current_player);
		}
	}
}
void sell_property(block board[20],player *current_player){
	int i=0,counter=0,selection,flag=1;
	printf("Your properties:\n");
	for(i=0;i<20;i++){
		if(board[i].owner==current_player->type){
			printf("%d:%s\n",i,board[i].name);
			counter++;
		}
	}
	if(counter>0){
		while(flag){
			printf("select one of them (-1 to quit):\n");
			scanf("%d",&selection);
			if(selection==-1){
				flag=0;
			}
			else if(board[selection].owner==current_player->type){
				board[selection].owner=noone;
				current_player->owned_block_ids[selection]=-1;
				current_player->account+=board[selection].price/2+board[selection].house_count*board[selection].house_price/2;
				flag=0;
				printf("successful\n");
			}
			else{
				printf("Try again!\n");
			}
		}
	}
	else{
		printf("You don'have any properties\n");
	}
}
void gameplay(block board[20],player player_one,player player_two){
	int selection;
	int dice_n;
	int order=0;
	int control=0,flag=1;
	int distance_one=0,distance_two=0;
	while(flag){
		if(distance_one>=20){
			player_one.account+=10000;
			distance_one=distance_one/20;
		}
		if(distance_two>=20){
			player_two.account+=10000;
			distance_two=distance_two/20;
		}
		if(order%2+1==cap){
			printf("cap:\n");
		}
		else if(order%2+1==car){
			printf("car:\n");
		}
		printf(
			"1-Roll the dice		\n"
			"2-Show my account		\n"
			"3-Show my properties	\n"
			"4-Show property deeds	\n"
			"5-Buy property			\n"
			"6-Buy house			\n"
			"7-Sell property		\n"
			"(cap ikinci kez roll the dice yapinca sira car'a gecer ve car hareket eder sonra car tekrar roll the dice yaparsa sira cap'e gecer ve cap hareket eder.)\n"
			"Please select an option to continue:\n"
		);
		scanf("%d",&selection);
		switch(selection){
			case 1:
				clear_screen();
				if(control){
					order++;
				}
				control=1;				
				dice_n=rand()%(6)+1;
				if(order%2+1==cap){
					if(player_one.turn_to_wait==0){
						player_one.current_block_ids=(player_one.current_block_ids+dice_n)%20;
						pay(board,&player_one,&player_two);
						if(check_the_game(board,&player_one)==0){
							printf("winner is car\n");
							flag=0;
						}
						distance_one+=dice_n;
					}
					else{
						player_one.turn_to_wait--;
					}
				}
				else if(order%2+1==car){
					if(player_two.turn_to_wait==0){
						player_two.current_block_ids=(player_two.current_block_ids+dice_n)%20;
						pay(board,&player_two,&player_one);
						if(check_the_game(board,&player_two)==0){
							printf("The winner is cap\n");
							flag=0;
						}
						distance_two+=dice_n;
					}
					else{
						player_two.turn_to_wait--;
					}
				}
				show_board(board,player_one,player_two);
			break;
			case 2:
				clear_screen();
				if(order%2+1==cap){
					printf("account of player1:%d\n", player_one.account);
				}
				if(order%2+1==car){
					printf("account of player2:%d\n", player_two.account);
				}
				show_board(board,player_one,player_two);
			break;
			case 3:
				clear_screen();
				if(order%2+1==cap){
					show_my_properties(board,player_one);
				}
				else if(order%2+1==car){
					show_my_properties(board,player_two);
				}
				show_board(board,player_one,player_two);
			break;
			case 4:
				show_properties(board);
				show_board(board,player_one,player_two);
			break;
			case 5:
				if(order%2+1==cap){
					buy_property(&board[player_one.current_block_ids],&player_one);
				}
				else if(order%2+1==car){
					buy_property(&board[player_two.current_block_ids],&player_two);
				}
				show_board(board,player_one,player_two);
			break;
			case 6:
				if(order%2+1==cap){
					buy_house(&board[player_one.current_block_ids],&player_one);
				}
				if(order%2+1==car){
					buy_house(&board[player_two.current_block_ids],&player_two);
				}
				show_board(board,player_one,player_two);
			break;
			case 7:
				clear_screen();
				if(order%2+1==cap){
					sell_property(board,&player_one);
				}
				else if(order%2+1==car){
					sell_property(board,&player_two);
				}
				show_board(board,player_one,player_two);
			break;
			default:
				clear_screen();
				printf("invalid choice!,try again!\n");
				show_board(board,player_one,player_two);
			break;
		}
	}
}
void show_my_properties(block board[20],player current_player){
	int i,my_properties[11],counter=0;
	printf("Your properties:\n");
	for(i=0;i<20;i++){
		if(current_player.type==board[i].owner){
			my_properties[counter]=board[i].block_id;
			counter++;
		}
	}
	if(counter==0){
		printf("Empty\n");
	}
	else{
		for(i=0;i<counter;i++){
			printf("%s\n",board[my_properties[i]].name);
		}
	}
}
void pay(block board[20],player *current_player,player *opponent_player){
	
	if(board[current_player->current_block_ids].owner!=current_player->type && board[current_player->current_block_ids].owner!=noone){
		if(board[current_player->current_block_ids].house_count==0){
			current_player->account=current_player->account - board[current_player->current_block_ids].rent;
			opponent_player->account=opponent_player->account + board[current_player->current_block_ids].rent;
		}
		else if(board[current_player->current_block_ids].house_count==1){
			current_player->account=current_player->account - board[current_player->current_block_ids].rent1;
			opponent_player->account=opponent_player->account + board[current_player->current_block_ids].rent1;
		}
		else if(board[current_player->current_block_ids].house_count==2){
			current_player->account=current_player->account - board[current_player->current_block_ids].rent2;
			opponent_player->account=opponent_player->account + board[current_player->current_block_ids].rent2;
		}
		else if(board[current_player->current_block_ids].house_count==3){
			current_player->account=current_player->account - board[current_player->current_block_ids].rent3;
			opponent_player->account=opponent_player->account + board[current_player->current_block_ids].rent3;
		}
	}
	else if(board[current_player->current_block_ids].type==tax){
		current_player->account=current_player->account - board[current_player->current_block_ids].rent;	
	}
	else if(board[current_player->current_block_ids].type==punish){
		current_player->account=current_player->account - board[current_player->current_block_ids].rent;
		if(current_player->current_block_ids==5){
			current_player->turn_to_wait=2;
		}
		else if(current_player->current_block_ids==15){
			current_player->turn_to_wait=1;
		}
	}
}
void buy_house(block *current_block,player *current_player){
	clear_screen();
	int total=-1;
	if(current_block->owner==current_player->type){
		printf("You have %d house in this property(you can buy up to 3 house in a property.)\n",current_block->house_count);
		printf("how many house do you want to buy(0-go back): ");
		while(current_block->house_count + total>3 || total<0){
			scanf("%d",&total);
			if(current_block->house_count + total>3 || total<0){
				printf("Try again!!\n");
			}
		}
		if(current_player->account >= total * (current_block->house_price)){
			current_block->house_count+=total;
			current_player->account=current_player->account-total*(current_block->house_price);
			printf("successful\n");		
		}
		else{
			printf("you couldn't buy\n");
		}
	}
	else{
		printf("you are not on your property!\n");
	}
}
int check_the_game(block board[20],player *current_player){//checking whether ther is a winner.
	int i=0,account_t=0;
	while(current_player->account<0){
		for(i=0;i<20;i++){
			if(board[i].owner==current_player->type){
				if(board[i].house_count==0){
					account_t+=(board[i].price)/2;
				}
				else{
					account_t+=(board[i].house_count*board[i].house_price)/2+(board[i].price)/2;
				}
			}
		}
		if(account_t>=(-1)*current_player->account){
			printf("Your account have stayed under 0,you have to sell some properties!\n");
			sell_property(board,current_player);
		}
		else{
			printf("The game over!\n");
			return 0;
		}
	}
}