#include "shannon.h"


tab aijoin(tab level){
	int i,j,x,y;
	tab leveltest;
	if(advantagecut(level)) return aijoin2(level);
	for(i=0;i<level.n;i++){
		for(j=0;j<level.t[i]->link.n;j++){
			x=level.t[i]->num;
			y=level.t[i]->link.t[j]->num;
			leveltest=lock(level,x,y);
			if(advantagejoin(leveltest)){
				level=leveltest;
				return level;
			}
			leveltest=unlock(level,x,y);
		}
	}
	return aijoin2(level);
}
// Test to see if there is a move that either put the AI at an advantage or make it win, if there is not, play at random.

tab aicut(tab level){
	int i,j,x,y;
	tab leveltest;
	if(advantagejoin(level)) return aicut2(level);
	for(i=0;i<level.n;i++){
		for(j=0;j<level.t[i]->link.n;j++){
			x=level.t[i]->num;
			y=level.t[i]->link.t[j]->num;
			leveltest=erase(level,x,y);
			if(advantagecut(leveltest)){
				level=leveltest;
				return level;
			}
			leveltest=link(level,x,y);
		}
	}
	return aijoin2(level);
}
// Same thing but for the Cut move.


tab aijoin2(tab level){
	lien* r;
	r=bestlink(level);
	level=lock(level,r->p1->num,r->p2->num);
	return level;
}

tab aicut2(tab level){
	lien* r;
	r=bestlink(level);
	level=erase(level,r->p1->num,r->p2->num);
	return level;
}
