#include "shannon.h"


void choice(){
	int a,n;
	tab level;
	printf("\n					Welcome to Shannon switching game !");
	printf("\n				To try one of the four levels, please type 1, 2, 3 or 4.");
	printf("\n				       	The fourth level is randomly generated.");
	printf("\n						To view the rules, type 0.");
	printf("\n				     To quit the game, type anything else you want.\n");
	n=scanf("%1d",&a);
	if(n==1){
		if (a==0){
			emptybuffer;
			rules();
			choice();
			return;
		}
		if(a==1){
			emptybuffer;
			level=level1();
			choice2(level);
			return;
		}
		if(a==2){
			emptybuffer;
			level=level2();
			choice2(level);
			return;
		}
		if(a==3){
			emptybuffer;
			level=level3();
			choice2(level);
			return;
		}
		if(a==4){
			emptybuffer;
			level=levelrandom();
			choice2(level);
			return;
		}
	}
	emptybuffer;
	printf("Goodbye !\n");
}
// Ask the player to choose between the levels, or reading the rules or quitting,

void choice2(tab level){
  int x,y,a,n;
	x=rand()%2;
	y=rand()%2;
	printf("Would you like to play against another player or against the machine ?\nFor PvsP enter 1, for PvsAI enter 2.\nYou can also see two AI battle each other if you type 3 : ");
	n=scanf("%1d",&a);
	if(n==1){
		if (a==1){
			emptybuffer;
			printf("\n\n");
			display(level);
			pvp(level,level.t[0],level.t[level.n-1],x);
			return;
		}
		if (a==2){
			emptybuffer;
			printf("Would you like to play as playet Join or Cut ?\nFor Join enter 1, for Cut enter 2 : ");
			n=scanf("%1d",&a);
			emptybuffer;
			choice3(level,level.t[0],level.t[level.n-1],x,a);
			return;
		}
		if (a==3){
			emptybuffer;
			printf("\n\n");
			display(level);
			aivai(level,level.t[0],level.t[level.n-1],x,y);
			return;
		}
	}
	printf("Invalid entry, please try again.\n");
    emptybuffer;
	choice2(level);
}
// Ask the player to choose between PlayerversusPlayer or PlayerversusAI. If second option, ask if player want to be Join or Cut. Random number 0 or 1 to decide who start 

void choice3(tab level,point* start, point* finish, int x,int y){
	int a,n;
	printf("Would you like to play against the basic AI ? (type 0)\nOr would you like to play against the cleverer one (warning: really slow) (type 1) : ");
	n=scanf("%1d",&a);
	if(n==1){
		if (a==1){
			emptybuffer;
			printf("\n\n");
			display(level);
			pvai(level,start,finish,x,y);
			return;
		}
		if (a==0){
			emptybuffer;
			printf("\n\n");
			display(level);
			pvai2(level,start,finish,x,y);
			return;
		}
	}
	printf("Invalid entry, please try again.\n");
    emptybuffer;
	choice3(level,start,finish,x,y);
}
// Ask the player to choose between the first or the second AI

void pvp(tab level,point* start, point* finish,int x){
	if (x==0){
		printf("\n\nIt's player Join's turn !\n");
		level=join(level);
		display(level);
		if(winjoin(*start,*finish)){
			announce(0);
			return;
		}
		pvp(level,start,finish,1);
	}
	if (x==1){
		printf("\n\nIt's player Cut's turn !\n");
		level=cut(level);
		display(level);
		if(wincut(*start,*finish)){
			announce(1);
			return;
		}
		pvp(level,start,finish,0);
	}
}
// Launch one by one the join move and the cut move, with first start decided by x.

void pvai(tab level,point* start, point* finish, int x,int y){
	if(y!=1 && y!=2){
		printf("\nInvalid entry, please try again.\n\n\n");
		choice2(level);
	}
	if(!x){
		if(y==1){
			printf("\n\nIt's your turn to join !\n");
			level=join(level);
			display(level);
			if(winjoin(*start,*finish)){
				announce(2);
				return;
			}
			pvai(level,start,finish,1,y);
		}
		if(y==2){
			printf("\n\nIt's your turn to cut !\n");
			level=cut(level);
			display(level);
			if(wincut(*start,*finish)){
				announce(2);
				return;
			}
			pvai(level,start,finish,1,y);
		}
	}
	if(x){
		if(y==1){
			printf("\n\nIt's the machine's turn to cut ! Please be patient while it's thinking.\n");
			level=aicut(level);
			display(level);
			if(wincut(*start,*finish)){
				announce(3);
				return;
			}
			pvai(level,start,finish,0,y);
		}
		if(y==2){
			printf("\n\nIt's the machine's turn to join ! Please be patient while it's thinking.\n");
			level=aijoin(level);
			display(level);
			if(winjoin(*start,*finish)){
				announce(3);
				return;
			}
			pvai(level,start,finish,0,y);
		}	
	}	
}
// Launch one by one the ai move and the player move, with first start decided by x and roles (Join or Cut) decided by y.

void pvai2(tab level,point* start, point* finish, int x,int y){
	if(y!=1 && y!=2){
		printf("\nInvalid entry, please try again.\n\n\n");
		choice2(level);
	}
	if(!x){
		if(y==1){
			printf("\n\nIt's your turn to join !\n");
			level=join(level);
			display(level);
			if(winjoin(*start,*finish)){
				announce(2);
				return;
			}
			pvai2(level,start,finish,1,y);
		}
		if(y==2){
			printf("\n\nIt's your turn to cut !\n");
			level=cut(level);
			display(level);
			if(wincut(*start,*finish)){
				announce(2);
				return;
			}
			pvai2(level,start,finish,1,y);
		}
	}
	if(x){
		if(y==1){
			printf("\n\nIt's the machine's turn to cut !\n");
			level=aicut2(level);
			display(level);
			if(wincut(*start,*finish)){
				announce(3);
				return;
			}
			pvai2(level,start,finish,0,y);
		}
		if(y==2){
			printf("\n\nIt's the machine's turn to join !\n");
			level=aijoin2(level);
			display(level);
			if(winjoin(*start,*finish)){
				announce(3);
				return;
			}
			pvai2(level,start,finish,0,y);
		}	
	}	
}

void aivai(tab level,point* start, point* finish, int x,int y){
	if(!x){
		if(y){
			printf("\n\nIt's the second AI's turn to join !\n");
			level=aijoin(level);
			display(level);
			if(winjoin(*start,*finish)){
			  	printf("\n\n	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\nAi 2 has won ! Try to play against it next time !\n\n\n");
				return;
			}
			printf("Please press enter to continue...");
			scanf("%*[*]");
			emptybuffer;
			aivai(level,start,finish,1,y);
		}
		else{
			printf("\n\nIt's the second AI's turn to cut !\n");
			level=aicut(level);
			display(level);
			if(wincut(*start,*finish)){
			  	printf("\n\n	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\nAi 2 has won ! Try to play against it next time !\n\n\n");
				return;
			}
			printf("Please press enter to continue...");
			scanf("%*[*]");
			emptybuffer;
			aivai(level,start,finish,1,y);
		}
	}
	if(x){
		if(y){
			printf("\n\nIt's the first AI's turn to cut !\n");
			level=aicut2(level);
			display(level);
			if(wincut(*start,*finish)){
			  	printf("\n\n	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\nAi 1 has won ! Try to play against it next time !\n\n\n");
				return;
			}
			printf("Please press enter to continue...");
			scanf("%*[*]");
			emptybuffer;
			aivai(level,start,finish,0,y);
		}
		else{
			printf("\n\nIt's the first AI's turn to join !\n");
			level=aijoin2(level);
			display(level);
			if(winjoin(*start,*finish)){
			  	printf("\n\n	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				printf("\n\nAi 1 has won ! Try to play against it next time !\n\n\n");
				return;
			}
			printf("Please press enter to continue...");
			scanf("%*[*]");
			emptybuffer;
			aivai(level,start,finish,0,y);
		}	
	}	
}

void rules(){
	printf("\033[H\033[2J");
	printf("\n\n			In the Shannon Switching Game, you play with a board containing several points,\n");
	printf("					each point is linked to several others.\n");
	printf("				There are two players, player Join and player Cut.\n\n");
	printf("	The goal of player Join is to have an undestructible path that goes from the first point to the last.\n");
	printf("	   For that they will, at each turn, lock a connection between two points, so it can't be destroyed.\n\n");
	printf("	    The goal of player Cut is that there is no longer any path that link the first point to the last.\n");
	printf("     For that they will, at each turn, destroy a connection between two points, except if the connection is locked.\n\n");
	printf("			If you understand better the principle of the game, you can now try to play !\n\n");
}
// Display the rules of the game
