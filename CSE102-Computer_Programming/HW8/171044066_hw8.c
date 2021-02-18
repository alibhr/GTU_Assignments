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
	punish,
	fortune
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
	struct block *next;
}block;
typedef struct fortune_card{
	int card_no;
	char *name;
	int price;
}fortune_card;
void init_the_board(block **board);
void gameplay(block *board,player player_one,player player_two);
player* turn(player *current_player,player *player_one,player *player_two);
void show_board(block *board,player player1,player player2);
void fill(block *ll,int block_id,char *name,int price,int rent,int rent1,int rent2,int rent3,int house_price,int house_count,player_type owner,block_type type);
void show_properties(block *board);
void buy_property(block *current_block,player *current_player);
void buy_house(block *current_block,player *current_player);
void sell_property(block *board,player *current_player);
void show_my_properties(block *board,player current_player);
void pay(block *board,player *current_player,player *opponent_player,int dice_n);
int check_the_game(block *board,player *current_player);
void fortune_card_deck(block *board,player *current_player,player *opponent_player,int dice_n);
int roll_the_dice();
int main(){
	clear_screen();
	srand(time(NULL));
	int i=0;
	block *board;
	block *head;
	block *temp;
/*				{	type	,current_block_ids	,owned_block_ids,account	,turn_to_wait	,name}*/
	player player_one={cap	,0					,{}				,100000		,0				,"cap"};
	player player_two={car	,0					,{}				,100000		,0				,"car"};
	for(i=0;i<11;i++){//-1 means is gonna be emty area in the array.
		player_one.owned_block_ids[i]=-1;
		player_two.owned_block_ids[i]=-1;
	}
	init_the_board(&board);
	head=board;
	show_board(board,player_one,player_two);
	gameplay(board,player_one,player_two);
//Free linked list
	while(board!=NULL){
		temp=board;
		board=board->next;
		free(temp);
	}
	return 0;
}
void gameplay(block *board,player player_one,player player_two){
	block *head;
	player *current_player;
	current_player=&player_one;
	head=board;
	int flag=1,i=0;
	int selection,buy;
	int dice,dice_t,avarage=0,counter=0,counter1=0;
	int distance_one=0,distance_two=0;
	for(i=0;i<24;i++){
		if(board->type==property){
			avarage+=board->price;
			counter++;
		}
		board=board->next;
	}
	avarage=avarage/counter;
	board=head;
	while(flag){
		if(distance_one>=24){
			player_one.account+=10000;
			distance_one=distance_one/24;
		}
		if(distance_two>=24){
			player_two.account+=10000;
			distance_two=distance_two/24;
		}
		dice=0;
		printf("%s:%d$ %s:%d$\n",player_one.name,player_one.account,player_two.name,player_two.account);
		printf(
			"1-Roll the dice		\n"
			"2-Show my account		\n"
			"3-Show my properties	\n"
			"4-Show property deeds	\n"
			"5-Buy property			\n"
			"6-Buy house			\n"
			"7-Sell property		\n"
			"Please select an option to continue (%s)\n",current_player->name
		);
		if(current_player->type==player_two.type){
			scanf("%d",&selection);
		}
		else{
			selection=1;
		}
		switch(selection){
			case 1:
				clear_screen();
				if(current_player->type==player_one.type){
					dice=roll_the_dice();
					printf("Computer (%s) rolled the dice %d\n",current_player->name,dice);
					current_player->current_block_ids=(current_player->current_block_ids+dice)%24;
					board=head;
					pay(board,current_player,&player_two,dice);
					if(check_the_game(board,current_player)==0){
						printf("WİNNER:%s\n",player_two.name);
						flag=0;
					}
					board=head;
					for(i=0;i<current_player->current_block_ids;i++){
						board=board->next;
					}
					if(board->type==property && board->owner==noone && flag){
						if(board->price < avarage){
							buy_property(board,current_player);
							printf("Computer (%s) rolled the dice %d\n",current_player->name,dice);
							current_player=turn(current_player,&player_one,&player_two);
						}
						else{
							dice_t=roll_the_dice();
							if(dice_t>=1 && dice_t<=3){
								buy_property(board,current_player);
								printf("Computer (%s) rolled the dice %d\n",current_player->name,dice);
								current_player=turn(current_player,&player_one,&player_two);
							}
							else if(dice>3 && dice <=6){
								current_player=turn(current_player,&player_one,&player_two);
							}
						}
					}
					else if(board->owner==current_player->type && flag){
						board=head;
						for(i=0;i<24;i++){
							if(board->owner==current_player->type){
								counter1++;
							}
							board=board->next;
						}
						board=head;
						if(counter1>=4){
							dice=roll_the_dice();
							if(dice>0 && dice<=3){
								board=head;
								for(i=0;i<current_player->current_block_ids;i++){
									board=board->next;
								}
								if(board->house_count<3){
									current_player->account=current_player->account-board->house_price;
									board->house_count=board->house_count+1;
									current_player=turn(current_player,&player_one,&player_two);
								}
								else{
									current_player=turn(current_player,&player_one,&player_two);
								}
							}
							else{
								current_player=turn(current_player,&player_one,&player_two);
							} 
						}
						else{
							current_player=turn(current_player,&player_one,&player_two);
						}
					}
					else{
						current_player=turn(current_player,&player_one,&player_two);	
					}
					board=head;
					show_board(board,player_one,player_two);
				}
				else if(current_player->type==player_two.type){
					dice=roll_the_dice();
					current_player->current_block_ids=(current_player->current_block_ids+dice)%24;
					board=head;
					pay(board,current_player,&player_one,dice);
					board=head;
					if(check_the_game(board,current_player)==0){
						printf("WİNNER:%s\n",player_one.name);
						flag=0;
					}
					board=head;
					show_board(board,player_one,player_two);
					board=head;
					for(i=0;i<current_player->current_block_ids;i++){
						board=board->next;
					}
					if(board->type==property && board->owner==noone && flag){
						printf("Do you want to buy %s (1-yes  0-no) ?\n",board->name);
						buy=-1;
						while(buy<0 || buy >1){
							scanf("%d",&buy);
							if(buy<0 || buy >1){
								printf("%s\n","(1-yes  0-no)");
							}
						}
						if(buy){
							buy_property(board,current_player);
						}
					}
					current_player=turn(current_player,&player_one,&player_two);
				}
			break;
			case 2:
				clear_screen();
				printf("Account of %s :%d$\n",current_player->name,current_player->account);
				board=head;
				show_board(board,player_one,player_two);
			break;
			case 3:
				clear_screen();
				show_my_properties(board,*current_player);
				board=head;
				show_board(board,player_one,player_two);
			break;
			case 4:
				show_properties(board);
				board=head;
				show_board(board,player_one,player_two);
			break;
			case 5:
				board=head;
				for(i=0;i<current_player->current_block_ids;i++){
					board=board->next;
				}
				buy_property(board,current_player);
				board=head;
				show_board(board,player_one,player_two);
			break;
			case 6:
				board=head;
				for(i=0;i<current_player->current_block_ids;i++){
					board=board->next;
				}
				buy_house(board,current_player);
				board=head;
				show_board(board,player_one,player_two);
			break;
			case 7:
				clear_screen();
				sell_property(board,current_player);
				board=head;
				show_board(board,player_one,player_two);
			break;
			default:
				clear_screen();
				printf("invalid choice!,try again!\n");
				board=head;
				show_board(board,player_one,player_two);
			break;
		}

	}
}
player* turn(player *current_player,player *player_one,player *player_two){
	if(current_player->type==player_one->type){
		current_player=player_two;
	}
	else if(current_player->type==player_two->type){
		current_player=player_one;
	}
	return current_player;
}
void init_the_board(block **board){
	block *head;
	block *go;
	int i;
/**/
	//0
	head=(block*)malloc(sizeof(block));
	go=head;
	go->next=NULL;
	fill(go	,0	,"Start"		,0		,0		,0		,0		,0		,0			,0			,noone	,start);

	/*
	//index
	memory allocation for the next node
	pointing the null for the last node
	passing to next node
	filling the current node with a function
	fill{node,id,"name			,price	,rent	,rent1	,rent2	,rent3	,house_price,house_count,owner	,type"}
	*/
	//1
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,1	,"Esenyurt"		,16000	,800	,4000	,9000	,25000	,10000		,0			,noone	,property);

	//2
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,2	,"Car Park"		,1500	,1500	,0		,0		,0		,0			,0			,noone	,tax);

	//3
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,3	,"Fortune Card"	,0		,0		,0		,0		,0		,0			,0			,noone	,fortune);

	//4
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,4	,"Tuzla"		,16500	,850	,4250	,9500	,26000	,12000		,0			,noone	,property);

	//5	
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,5	,"Arnavutkoy"	,17000	,875	,4500	,10000	,28000	,12000		,0			,noone	,property);

	//6
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,6	,"Wait 2 Turn"	,0		,2		,0		,0		,0		,0			,0			,noone	,punish);

	//7
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,7	,"Catalca"		,20000	,1000	,5000	,12000	,30000	,13000		,0			,noone	,property);

	//8
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,8	,"Beykoz"		,23000	,1100	,5500	,12500	,33000	,13000		,0			,noone	,property);

	//9
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,9	,"Fortune Card"	,0		,0		,0		,0		,0		,0			,0			,noone	,fortune);

	//10
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,10	,"Car Fix"		,1750	,1750	,0		,0		,0		,0			,0			,noone	,tax);

	//11
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,11	,"Maltepe"		,30000	,1350	,7000	,15000	,40000	,15000		,0			,noone	,property);

	//12
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,12	,"Bills"		,2000	,2000	,0		,0		,0		,0			,0			,noone	,tax);

	//13
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,13	,"sisli"		,33000	,1500	,8000	,16000	,42000	,16000		,0			,noone	,property);

	//14
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,14	,"Oil"			,2250	,2250	,0		,0		,0		,0			,0			,noone	,tax);

	//15
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,15	,"Fortune Card"	,0		,0		,0		,0		,0		,0			,0			,noone	,fortune);

	//16
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,16	,"Atasehir"		,35000	,1600	,8500	,17000	,45000	,17000		,0			,noone	,property);

	//17
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,17	,"Sariyer"		,40000	,1750	,9500	,19000	,48000	,19000		,0			,noone	,property);


	//18
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,18	,"Wait 1 Turn"	,0		,1		,0		,0		,0		,0			,0			,noone	,punish);

	//19
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,19	,"Kadikoy"		,43000	,1900	,1100	,21500	,55000	,23000		,0			,noone	,property);

	//20
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,20	,"Besiktas"		,60000	,2500	,15000	,28000	,60000	,30000		,0			,noone	,property);

	//21
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,21	,"Fortune Card"	,0		,0		,0		,0		,0		,0			,0			,noone	,fortune);

	//22
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,22	,"vocation"		,5000	,5000	,0		,0		,0		,0			,0			,noone	,tax);

	//23
	go->next=(block*)malloc(sizeof(block));
	go->next->next=NULL;
	go=go->next;
	fill(go	,23	,"Bebek"		,70000	,3500	,20000	,35500	,65000	,35000		,0			,noone	,property);

	*board=head;
}
void fill(block *ll,int block_id,char *name,int price,int rent,int rent1,int rent2,int rent3,int house_price,int house_count,player_type owner,block_type type){
	ll->block_id=block_id;
	ll->name=name;
	ll->price=price;
	ll->rent=rent;
	ll->rent1=rent1;
	ll->rent2=rent2;
	ll->rent3=rent3;
	ll->house_price=house_price;
	ll->house_count=house_count;
	ll->owner=owner;
	ll->type=type;
}
void show_board(block *board,player player1,player player2){
	block *board_j;
	block *head;
	head=board;
	board_j=board;
	int i=0,j=0,k=0,ll=0;
	for(i=0;i<169;i++){//lıne on top
		printf("-");
	}
	printf("\n|");
	for(i=0;i<7;i++){
		printf("\t%-16s%s",board->name,"|");
		board=board->next;
	}
	board=head;
	printf("\n|");
	for(i=0;i<7;i++){
		if(board->type==punish || board->type==start || board->type==fortune){
			printf("\t%-16s%s","","|");
			board=board->next;
		}
		else{
			printf("\t%-5d$%11s",board->price,"|");
			board=board->next;
		}
	}
	board=head;
	printf("\n|");
	for(i=0;i<7;i++){
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
	for(i=0;i<169;i++){
		printf("-");
	}	
	printf("\n");
	//first line is up to here.
	i=23;//when i decreasing j will increase in same time.
	j=7;
	while(i>18 && j<12){//this while loop draw the middle of the map.
		board=head;
		board_j=head;
		for(k=0;k<i;k++){
			board=board->next;
		}
		for(k=0;k<j;k++){
			board_j=board_j->next;
		}
		printf("|");
		printf("\t%-16s%s",board->name,"|");//board[i].name
		for(k=0;k<15;k++){
			printf("\t");
		}
		printf("|");
		printf("\t%-16s%s",board_j->name,"|");//board[j].name
		printf("\n|");
						
		if(board->type==punish || board->type==start || board->type==fortune){
			printf("\t%-16s%s","","|");
		}
		else{
			printf("\t%-6d%-10s%s",board->price,"$","|");
		}
		for(k=0;k<15;k++){
			printf("\t");
		}
		printf("|");
		if(board_j->type==punish || board_j->type==start || board_j->type==fortune){
			printf("\t%-16s%s","","|");
		}
		else{
			printf("\t%-6d%-10s%s",board_j->price,"$","|");
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
		for(k=0;k<15;k++){
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
		if(!(i==19 && j==11)){		
			for(k=0;k<25;k++){
				printf("-");
			}
			for(k=0;k<15;k++){
				printf("\t");
			}		
			for(k=0;k<25;k++){
				printf("-");
			}
			printf("\n");
		}
		else{
			for(k=0;k<169;k++){
				printf("-");
			}
			printf("\n");
		}
		i--; j++;
	}
	//starting of bottom line.
	printf("|");	
	for(i=18;i>11;i--){
		board=head;
		for(k=0;k<i;k++){
			board=board->next;
		}
		printf("\t%-16s%s",board->name,"|");
	}
	printf("\n|");
	for(i=18;i>11;i--){
		board=head;
		for(k=0;k<i;k++){
			board=board->next;
		}		
		if(board->type==punish || board->type==start || board->type==fortune){
			printf("\t%-16s%s","","|");
		}
		else{
			printf("\t%-6d%s%10s",board->price,"$","|");
		}
	}
	printf("\n|");
	for(i=18;i>11;i--){
		board=head;
		for(k=0;k<i;k++){
			board=board->next;
		}
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
	for(i=0;i<169;i++){
		printf("-");
	}
	printf("\n");
}
void show_properties(block *board){
	block *head;
	head=board;
	clear_screen();
	int selection=2,i=0,j=0,flag=1;
	while(flag){
		printf("Please seleckt a property to see details:\n");
		board=head;
		while(board!=NULL){
			if(board->type==property){
				printf("%d-%s\n",board->block_id,board->name);
			}
			board=board->next;
		}
		printf("(0-go back)\n");
		selection=2;
		board=head;
		for(i=0;i<selection;i++){
			board=board->next;
		}
		while(board->type!=property && selection!=0){//this loop is continue untill user enter the valid value.
			scanf("%d",&selection);
			board=head;
			for(i=0;i<selection;i++){
				board=board->next;
			}
			if(board->type!=property && selection!=0){
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
			printf("\n|\t\t%-20s|\n",board->name);
			for(i=0;i<37;i++){
				printf("-");
			}
			printf("\n");

			printf("|\tRent  \t\t%-5d%-7s|\n",board->rent,"$");
			printf("|\tRent 1\t\t%-5d%-7s|\n",board->rent1,"$");
			printf("|\tRent 2\t\t%-5d%-7s|\n",board->rent2,"$");
			printf("|\tRent 3\t\t%-5d%-7s|\n",board->rent3,"$");
			for(i=0;i<37;i++){
				printf("-");
			}
			printf("\n");
			printf("|\tHouse Price\t%-5d%-7s|\n",board->house_price,"$");
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
		printf("property is bought by %s!\n",current_player->name);
	}
	else if(current_block->owner!=noone){
		printf("The block has already sold!\n");
	}
	else if(current_block->type!=property){
		printf("you can't buy this block!(this block not a property)!!\n");
	}
	else if(current_player->account < current_block->price){
		printf("insufficient account!\n");
	}
	else{
		printf("There is something wrong!\n");
	}
	if(yes && current_player->type==car){
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
void buy_house(block *current_block,player *current_player){
	clear_screen();
	int total=-1;
	if(current_block->house_count==3 && current_block->owner==current_player->type){
		printf("There are already three house so you can't buy any more!\n");
	}
	else if(current_block->owner==current_player->type){
		printf("You (%s) have %d house in this property(you can buy up to 3 house in a property.)\n",current_player->name,current_block->house_count);
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
			if(total!=0){
				printf("%s bought %d house in this property (successful)\n",current_player->name,total);		
			}
		}
		else{
			printf("you couldn't buy(insufficient account)!\n");
		}
	}
	else{
		printf("you are not on your property!\n");
	}
}
void sell_property(block *board,player *current_player){
	block *head;
	head=board;
	int max=0;
	int i=0,j=0,counter=0,selection,flag=1;
	printf("Your properties:\n");
	for(i=0;i<23;i++){
		board=head;
		for(j=0;j<i;j++){
			board=board->next;
		}
		if(board->owner==current_player->type){
			printf("%d:%s\n",i,board->name);
			counter++;
		}
	}
	if(counter>0){
		while(flag){
			printf("select one of them (-1 to quit):\n");
			board=head;
			selection=0;
			if(current_player->type==car){
				scanf("%d",&selection);
			}
			else{
				for(j=0;j<24;j++){
					if(board->type==current_player->type && board->owner==current_player->type){
						if(board->price > max){
							max=board->price;
							selection=board->block_id;
						}
					}
					board=board->next;
				}
			}
			board=head;
			for(j=0;j<selection;j++){
				board=board->next;
			}
			if(selection==-1){
				flag=0;
			}
			else if(board->owner==current_player->type){
				board->owner=noone;
				current_player->owned_block_ids[selection]=-1;
				current_player->account+=board->price/2+board->house_count*board->house_price/2;
				flag=0;
				printf("%s was sold by %s\n",board->name,current_player->name);
			}
			else{
				printf("Try again!\n");
			}
		}
	}
	else{
		printf("You don't have any properties\n");
	}
}
void show_my_properties(block *board,player current_player){
	int i=0,j=0,counter=0;
	block *head;
	head=board;
	printf("Your properties(%s):\n",current_player.name);
	for(i=0;i<23;i++){
		board=head;
		for(j=0;j<i;j++){
			board=board->next;
		}
		if(current_player.type==board->owner){
			printf("%d:%s\n",i,board->name);
			counter++;
		}
	}
	if(counter==0){
		printf("Empty\n");
	}
}
void pay(block *board,player *current_player,player *opponent_player,int dice_n){
	block *head;
	int i;
	head=board;
	for(i=0;i<current_player->current_block_ids;i++){
		board=board->next;
	}
	if(board->owner!=current_player->type && board->owner!=noone){
		if(board->house_count==0){
			current_player->account=current_player->account - board->rent;
			opponent_player->account=opponent_player->account + board->rent;
			printf("%s lost %d$ & %s earn %d$ \n",current_player->name,board->rent,opponent_player->name,board->rent);
		}
		else if(board->house_count==1){
			current_player->account=current_player->account - board->rent1;
			opponent_player->account=opponent_player->account + board->rent1;
			printf("%s lost %d$ & %s earn %d$ \n",current_player->name,board->rent1,opponent_player->name,board->rent1);
		}
		else if(board->house_count==2){
			current_player->account=current_player->account - board->rent2;
			opponent_player->account=opponent_player->account + board->rent2;
			printf("%s lost %d$ & %s earn %d$ \n",current_player->name,board->rent2,opponent_player->name,board->rent2);
		}
		else if(board->house_count==3){
			current_player->account=current_player->account - board->rent3;
			opponent_player->account=opponent_player->account + board->rent3;
			printf("%s lost %d$ & %s earn %d$ \n",current_player->name,board->rent3,opponent_player->name,board->rent3);
		}
	}
	else if(board->type==tax){
		current_player->account=current_player->account - board->rent;	
		printf("%s lost %d$\n",current_player->name,board->rent);
	}
	else if(board->type==punish){
		printf("%s is on the punish block\n",current_player->name );
		current_player->account=current_player->account - board->rent;
		if(current_player->current_block_ids==6){
			current_player->turn_to_wait=2;
		}
		else if(current_player->current_block_ids==18){
			current_player->turn_to_wait=1;
		}
	}
	else if(board->type==fortune){
		printf("%s is on the fortune block!\n",current_player->name);
		board=head;
		fortune_card_deck(board,current_player,opponent_player,dice_n);
	}
}
int check_the_game(block *board,player *current_player){//checking whether there is a winner.
	block *head;
	head=board;
	int i=0,j=0,account_t=0;
	while(current_player->account<0){
		for(i=0;i<23;i++){
			board=head;
			for(j=0;j<i;j++){
				board=board->next;
			}
			if(board->owner==current_player->type){
				if(board->house_count==0){
					account_t+=(board->price)/2;
				}
				else{
					account_t+=(board->house_count*board->house_price)/2+(board->price)/2;
				}
			}
		}
		if(account_t>=(-1)*current_player->account){
			printf("Your account(%s) have stayed under 0,you have to sell some properties!\n",current_player->name);
			board=head;
			sell_property(board,current_player);
		}
		else{
			printf("The game over!\n");
			return 0;
		}
	}
}
void fortune_card_deck(block *board,player *current_player,player *opponent_player,int dice_n){
	char ch;
	int card_number_r,i,j;
	int selection=0,counter=0;
	int my_properties[11];
	block *head;
	head=board;
	if(current_player->type==car){
		printf("press any key to take card.\n");
		scanf(" %c",&ch);
	}

	card_number_r=(rand()%5)+1;
	fortune_card card_deck[5]={
		{1	,"Free House"		,0		},
		{2	,"Time Travel"		,2		},
		{3	,"Garnishment"		,5000	},
		{4	,"Generosity"		,10000	},
		{5	,"Treasure Hunter"	,20000	}
	};
	if(card_deck[0].card_no==card_number_r){
		printf("Your card:%s\n",card_deck[0].name);
		printf("You (%s) can build a house on one of your properties for free.\n",current_player->name);
		printf("Your properties(which don't have more than three house):\n");
		for(i=0;i<24;i++){
			board=head;
			for(j=0;j<i;j++){
				board=board->next;
			}
			if(current_player->type==board->owner && board->house_count<3){
				my_properties[counter]=board->block_id;
				counter++;
			}
		}
		if(counter==0){
			printf("Empty\n");
		}
		else{
			for(i=0;i<counter;i++){
				board=head;
				for(j=0;j<my_properties[i];j++){
					board=board->next;
				}
				printf("%d)%s\n",board->block_id,board->name);
			}
			board=head;
			printf("Select one of them(%s):\n",current_player->name);
			while(board->owner!=current_player->type || board->house_count>=3){
				if(current_player->type==car){
					scanf("%d",&selection);
				}
				else{
					selection=my_properties[counter-1];
				}
				board=head;
				for(j=0;j<selection;j++){
					board=board->next;
				}
				if(board->owner!=current_player->type){
					printf("Try again!\n");
				}
				if(board->house_count>=3){
					printf("There are three house in this property!!!\n");
				}
			}
			board->house_count++;
			printf("successful\n");
		}
	}
	else if(card_deck[1].card_no==card_number_r){
		printf("Your card(%s):%s\n",current_player->name,card_deck[1].name);
		if(dice_n>=1 && dice_n<=3){
			printf("%s moved forward 2 blocks(dice=%d)\n",current_player->name,dice_n);
			current_player->current_block_ids=(current_player->current_block_ids+card_deck[1].price)%24;
		}
		else if(dice_n>3 && dice_n<=6){
			printf("%s moved backward 2 blocks(dice=%d)\n",current_player->name,dice_n);
			current_player->current_block_ids=(current_player->current_block_ids-card_deck[1].price)%24;
		}
	}
	else if(card_deck[2].card_no==card_number_r){
		printf("Your card(%s):%s\n",current_player->name,card_deck[2].name);
		printf("You lost %d$\n",card_deck[2].price);
		current_player->account-=card_deck[2].price;
	}
	else if(card_deck[3].card_no==card_number_r){
		printf("Your card(%s):%s\n",current_player->name,card_deck[3].name);
		printf("You lost %d$\n", card_deck[3].price);
		printf("%s earn %d$\n",opponent_player->name,card_deck[3].price );
		current_player->account-=card_deck[3].price;
		opponent_player->account+=card_deck[3].price;
	}
	else if(card_deck[4].card_no==card_number_r){
		printf("Your card(%s):%s\n",current_player->name,card_deck[4].name);
		printf("You earn %d$\n",card_deck[4].price);
		current_player->account+=card_deck[4].price;
	}
}
int roll_the_dice(){
	return (rand()%6)+1;
}