#include "shannon.h"


tab join(tab level){
	int a,b,n;
	printf("\n\nPlease enter the numbers of the two points you wish to lock together : ");
	n=scanf("%2d %2d",&a,&b);
	if(n!=2 || a>level.n || b>level.n){
		printf("Invalid entry, please try again.\n");
    	emptybuffer;
		return join(level);
	}
	if(arelocked(level,a,b)){
		printf("These points are already locked together, please try again.\n");
    	emptybuffer;
		return join(level);
	}
	if(!arelinked(level,a,b)){
		printf("These points don't have any connection, you can't lock them, please try again.\n");
    	emptybuffer;
		return join(level);
	}
	level=lock(level,a,b);
    emptybuffer;
	return level;
}
// Do the join move with the player's input from the keyboard, function restart if there are errors in the input.

tab cut(tab level){
	int a,b,n;
	printf("\n\nPlease enter the numbers of the two points between which you want to erase the connection : ");
	n=scanf("%2d %2d",&a,&b);
	if(n!=2){
		printf("Invalid entry, please try again.\n");
    	emptybuffer;
		return cut(level);
	}
	if(arelocked(level,a,b)){
		printf("These points are already locked together, you can't erase their connection, please try again.\n");
    	emptybuffer;
		return cut(level);
	}
	if(!arelinked(level,a,b)){
		printf("These points already don't have any connection, please try again.\n");
    	emptybuffer;
		return cut(level);
	}
	level=erase(level,a,b);
    emptybuffer;
	return level;
}
// Do the cut move with the player's input from the keyboard, function restart if there are errors in the input.