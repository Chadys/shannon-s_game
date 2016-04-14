#include "shannon.h"


bool belong(int x, int n, int list[100]){
	int i;
	for(i=0;i<n;i++){
		if (x==list[i]) return true;
	}
	return false;
}
// Test if int x belong to the list.


bool winjoin1(point a, point b, int n, int list[100]){
	int i;
	if (a.num==b.num) return true;
	if(belong(a.num,n,list)) return false;
	n++;
	list[n-1]=a.num;
	for (i=0;i<a.locked.n;i++){
			if(winjoin1(*a.locked.t[i], b,n,list))
				return true;
	}
	return false;
}
// Run through all the locked path from point a to see if we can reach point b

bool winjoin(point a,point b){
	int list[100];
	return winjoin1(a,b,0,list);
}
// Return true if player Join has won


bool wincut1(point a, point b, int n, int list[100]){
	int i;
	if (a.num==b.num) return false;
	if(belong(a.num,n,list)) return true;
	n++;
	list[n-1]=a.num;
	for (i=0;i<a.link.n;i++){
			if(!wincut1(*a.link.t[i], b,n,list))
				return false;
	}
	for (i=0;i<a.locked.n;i++){
			if(!wincut1(*a.locked.t[i], b,n,list))
				return false;
	}
	return true;
}
// Go through all the possible paths (linked and locked) of point a to see if there is a way to go to b. Return true if there is none.

bool wincut(point a,point b){
	int list[100];
	return wincut1(a,b,0,list);
}
// Return true if player Cut has won


void announce(int x){
	printf("\n\n	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	switch(x){
		case 0:
			printf("\n\n	Player Join has won ! Congratulations !\n\n\n");
			break;
		case 1:
			printf("\n\n	Player Cut has won ! Congratulations !\n\n\n");
			break;
		case 2:
			printf("\n\n	You have won against the computer ! You're too strong, congratulations !\n\n\n");
			break;
		case 3:
			printf("\n\n	The computer beat you ! That's too bad, maybe you'll win next time !\n\n\n");
			break;
	}
}
// Depending on the argument, announce the winner
