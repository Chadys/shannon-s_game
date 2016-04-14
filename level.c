#include "shannon.h"


tab create(int n){
	int i;
	tab level;
	point* y;
	level.n=n;
	for(i=0;i<n;i++){
		y=(point*) malloc((size_t) sizeof(point));
		y->num=i+1;
		y->link.n=0;
		y->locked.n=0;
		level.t[i]=y;
	}
	return level;
}
// Create a level (aka an array of points) of n points (without any links between points yet)


tab link(tab level, int a, int b){
	int i,j,n,x;
	point* temp;
	point* temp2;
	for (i=0;i<level.n;i++){
		if (level.t[i]->num==a)
			for (j=0;j<level.n;j++){
				if (level.t[j]->num==b){
					n=++level.t[i]->link.n;
					temp=level.t[j];
					for(x=0;x<n;x++){
						temp2=level.t[i]->link.t[x];
						level.t[i]->link.t[x]=temp;
						temp=temp2;
					}
					n=++level.t[j]->link.n;
					temp=level.t[i];
					for(x=0;x<n;x++){
						temp2=level.t[j]->link.t[x];
						level.t[j]->link.t[x]=temp;
						temp=temp2;
					}
				}
			};
	}
	return level;
}
// Add a possible link betxeen two points
// Add the link in the first position instead of simply at the end to prevent a loop in aitest


tab level1(){
	tab level;
	level=create(5);
	level=link(level,4,5);
	level=link(level,3,5);
	level=link(level,3,4);
	level=link(level,2,5);
	level=link(level,2,3);
	level=link(level,1,4);
	level=link(level,1,3);
	level=link(level,1,2);
	return level;
}
// Creation of Level 1

tab level2(){
	tab level;
	level=create(11);
	level=link(level,10,11);
	level=link(level,9,11);
	level=link(level,8,10);
	level=link(level,7,10);
	level=link(level,6,8);
	level=link(level,6,7);
	level=link(level,5,9);
	level=link(level,5,6);
	level=link(level,4,9);
	level=link(level,4,6);
	level=link(level,3,8);
	level=link(level,3,7);
	level=link(level,2,5);
	level=link(level,2,4);
	level=link(level,1,3);
	level=link(level,1,2);
	return level;
}
// Creation of Level 2

tab level3(){
	tab level;
	level=create(11);
	level=link(level,9,11);
	level=link(level,8,11);
	level=link(level,8,10);
	level=link(level,7,11);
	level=link(level,6,9);
	level=link(level,5,10);
	level=link(level,5,6);
	level=link(level,4,10);
	level=link(level,3,7);
	level=link(level,3,4);
	level=link(level,2,8);
	level=link(level,2,5);
	level=link(level,2,4);
	level=link(level,1,6);
	level=link(level,1,3);
	return level;
}
// Creation of Level 3

tab levelrandom(){
	tab level;
	int n,i,x;
	n=rand()%10+5;
	level=create(n);
	for(i=0;i<n;i++){
		x=rand()%4;
		level=randomlink(level,i+1);
		if(x==1)
			level=randomlink(level,i+1);
	}
	if(numberlinks(level,1)<2)level=randomlink(level,1);
	if(numberlinks(level,n)<2)level=randomlink(level,n);
	return level;
}
// Random level generator, between 5 and 15 points, a point always has at least one link.

tab randomlink(tab level, int a){
	int b;
	b=(rand()%(level.n-1))+1;
	if(numberlinks(level,a)==level.n-1)
		return randomlink(level,b);
	if(a==b || arelinked(level,a,b))
		return randomlink(level,a);
	level=link(level,a,b);
	return level;
}
// Make a link in the level between point a and another point choosen at random to which point a isn't already linked.

int numberlinks(tab level, int a){
	int i;
	for(i=0;i<level.n;i++){
		if(level.t[i]->num==a)
			return level.t[i]->link.n;
	}
	return -1;
}