#include "shannon.h"


void display1(point a){
	int i;
	printf("Point %d is linked to :",a.num);
	for (i=0;i<a.link.n;i++)
		printf("%4d",a.link.t[i]->num);
	printf("		and has a locked link with :");
	for (i=0;i<a.locked.n;i++)
		printf("%4d",a.locked.t[i]->num);
	printf("\n");
}
// Display, for a singular point, with which other points it is linked and with which is has an undestructible link.

void display(tab level){
	int i;
	for (i=0;i<level.n;i++)
		display1(*level.t[i]);
}
// Display all the points in an array of points


bool arelinked(tab level,int a, int b){
	int i,j;
	for (i=0;i<level.n;i++)
		if (level.t[i]->num==a){
			for(j=0;j<level.t[i]->link.n;j++){
				if(level.t[i]->link.t[j]->num==b) return true;
			}
		};
	return false;
}
// Boolean function that tell us if two points have a link together.

point erase1(point a, point b){
  int i,n;
  n=a.link.n;
  for (i=0;i<n;i++){
  	if (a.link.t[i]->num==b.num){
  		for(;i<n-1;i++)
  			a.link.t[i]=a.link.t[i+1];
  		a.link.n=n-1;
  		return a;
  	}
  }
  return a;
}
// Enable to erase the connection from point A to point B (one-sided), and return the resulting point.

tab erase(tab level,int a, int b){
	int i,j;
	for (i=0;i<level.n;i++){
		if (level.t[i]->num==a)
			for (j=0;j<level.n;j++){
				if (level.t[j]->num==b){
					*level.t[i]=erase1(*level.t[i],*level.t[j]);
					*level.t[j]=erase1(*level.t[j],*level.t[i]);
				}
			};
	}
	return level;
}
// Erase bilaterally the connexion between point number a and point number b in an array of points.


bool arelocked(tab level,int a, int b){
	int i,j;
	for (i=0;i<level.n;i++)
		if (level.t[i]->num==a){
			for(j=0;j<level.t[i]->locked.n;j++){
				if(level.t[i]->locked.t[j]->num==b) return true;
			}
		};
	return false;
}
// Boolean function that tell us if two points have an undestructible link together.

tab lock(tab level,int a, int b){
	int i,j,n;
	for (i=0;i<level.n;i++){
		if (level.t[i]->num==a)
			for (j=0;j<level.n;j++){
				if (level.t[j]->num==b){
					*level.t[i]=erase1(*level.t[i],*level.t[j]);
					*level.t[j]=erase1(*level.t[j],*level.t[i]);
					n=++level.t[i]->locked.n;
					level.t[i]->locked.t[n-1]=level.t[j];
					n=++level.t[j]->locked.n;
					level.t[j]->locked.t[n-1]=level.t[i];
				}
			};
	}
	return level;
}
// lock the connexion between point number a and point number b in an array of points.