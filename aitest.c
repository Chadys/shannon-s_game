#include "shannon.h"


bool advantagejoin1(tab level, int n, int list[100]){
	int i,j,x,y;
	point a,b;
	tab leveltest;
	a=*level.t[0];
	b=*level.t[level.n-1];
	if(winjoin(a,b)) return true;
	if(wincut(a,b)) return false;
	for(i=0;i<level.n;i++){
		for(j=0;j<level.t[i]->link.n;j++){
			x=level.t[i]->num;
			y=level.t[i]->link.t[j]->num;
			if(!belong(y,n,list)){
				leveltest=erase(level,x,y);
				if(!neutral(leveltest)){
					leveltest=link(level,x,y);
					return false;
				}
				leveltest=link(level,x,y);
			}
		}
		n++;
		list[n-1]=x;
	}
	return true;
}
bool advantagejoin(tab level){
	int list[100];
	return advantagejoin1(level,0,list);
}
// If true it means the player Join can win weither or not they start first.

bool neutral1(tab level, int n, int list[100]){
	int i,j,x,y;
	tab leveltest;
	for(i=0;i<level.n;i++){
		for(j=0;j<level.t[i]->link.n;j++){
			x=level.t[i]->num;
			y=level.t[i]->link.t[j]->num;
			if(!belong(y,n,list)){
				leveltest=lock(level,x,y);
				if(advantagejoin(leveltest)){
					leveltest=unlock(level,x,y);
					return true;
				}
				leveltest=unlock(level,x,y);
			}
		}
		n++;
		list[n-1]=x;
	}
	return false;
}
bool neutral(tab level){
	int list[100];
	return neutral1(level,0,list);
}
// If true it means the starting player can win. Needed for advantagejoin

bool advantagecut(tab level){
	return !(advantagejoin(level) || neutral(level));
}
// If true it means the player Cut can win weither or not they start first.


point unlock1(point a, point b){
  int i,j,n;
  point temp=a;
  n=a.locked.n;
  for (i=0;i<n;i++){
  	if (a.locked.t[i]->num==b.num){
  		temp.locked.n=n-1;
  		for(j=0;j<i;j++)
  			temp.locked.t[j]=a.locked.t[j];
  		for(;i<n-1;i++)
  			temp.locked.t[i]=a.locked.t[i+1];
  		return temp;
  	}
  }
  return a;
}
// Enable to erase the locked connection from point A to point B (one-sided), and return the resulting point.

tab unlock(tab level,int a, int b){
	int i,j;
	for (i=0;i<level.n;i++){
		if (level.t[i]->num==a)
			for (j=0;j<level.n;j++){
				if (level.t[j]->num==b){
					*level.t[i]=unlock1(*level.t[i],*level.t[j]);
					*level.t[j]=unlock1(*level.t[j],*level.t[i]);
				}
			};
	}
	level=link(level,a,b);
	return level;
}
// Erase bilaterally the connexion between point number a and point number b in an array of points.
// Useful for the AI because it changes the level when doing its tests, so enable to put back things together.