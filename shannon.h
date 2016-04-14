#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define emptybuffer scanf ("%*[^\n]"); getchar ();

typedef struct point* array[100];
struct tab{
  int n;
  array t;
};
typedef struct tab tab;
struct point{
  int num;
  tab link;
  tab locked;
};
typedef struct point point;

struct lien{
	point* p1;
	point* p2;
	int importance;
};
typedef struct lien lien;
//lien is composed of two point's adress and an int being used by the AI, represent a link between two point and its worth
typedef lien* tablien[100];

struct arrayLien{
	int n;
	tablien t;
};
typedef struct arrayLien arrayLien;
//array of links = a path
typedef arrayLien* tabarrayLien[100];

struct arrayParcours{
	int n;
	tabarrayLien t;
};
typedef struct arrayParcours arrayParcours;
//array of paths = a list of the different paths we can take


//ai.c
tab aijoin(tab);
tab aicut(tab);
tab aijoin2(tab);
tab aicut2(tab);

//ai2.c
arrayLien* nouveaupal(arrayLien*);
arrayParcours* bestpath1(tab, point*, int, arrayParcours*, arrayLien*, int, int[100]);
arrayParcours* bestpath(tab,int);
arrayLien* addlien(lien*, arrayLien*);
arrayLien* incrementlien(lien*, arrayLien*);
arrayLien* veriflien(arrayLien*);
lien* bestlink(tab);
lien* bestlink2(tab, arrayParcours*, arrayLien*, int);

//aitest.c
bool advantagejoin1(tab, int, int[100]);
bool advantagejoin(tab);
bool neutral1(tab, int, int[100]);
bool neutral(tab);
bool advantagecut(tab);
point unlock1(point a, point b);
tab unlock(tab, int, int);

//ending.c
bool belong(int, int, int[100]);
bool winjoin1(point, point, int, int[100]);
bool winjoin(point, point);
bool wincut1(point, point, int, int[100]);
bool wincut(point, point);
void announce(int);

//level.c
tab create(int);
tab link(tab, int, int);
tab level1();
tab level2();
tab level3();
tab levelrandom();
tab randomlink(tab, int);
int numberlinks(tab, int);

//player.c
tab join(tab);
tab cut(tab);

//point.c
void display1(point);
void display(tab);
bool arelinked (tab,int, int);
point erase1(point, point);
tab erase(tab,int, int);
bool arelocked (tab,int, int);
tab lock(tab,int, int);

//start.c
void choice();
void choice2(tab);
void choice3(tab, point*, point*, int,int);
void pvp(tab, point*, point*, int);
void pvai(tab, point*, point*, int,int);
void pvai2(tab, point*, point*, int,int);
void aivai(tab, point*, point*, int,int);
void rules();
