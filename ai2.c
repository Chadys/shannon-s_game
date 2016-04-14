#include "shannon.h"

	
arrayLien* nouveaupal(arrayLien* pal){
	int i;
	arrayLien* newpal =(arrayLien *) malloc(sizeof(arrayLien));
	newpal->n=pal->n ;
	for(i=0;i<newpal->n;i++){
		newpal->t[i]=pal->t[i] ;
	}
	return newpal;
}
//creation of new pal from pal containing the same elements

arrayParcours * bestpath1(tab level, point* ps, int tailleParcours, arrayParcours * pap, arrayLien* pal, int n, int parcours[100]){
		int i;
		arrayLien* newpal;
		lien* pl;
		parcours[n]=ps->num;
		n++;
		if(tailleParcours==0 && ps==level.t[level.n-1]){
			newpal = nouveaupal(pal);
			pap->t[pap->n]=newpal;
			pap->n++;
		}
		else if(tailleParcours !=0 && ps!=level.t[level.n-1]){
			for(i=0; i<ps->link.n;i++){
				if(!belong(ps->link.t[i]->num,n,parcours)){
					pl = (lien *) malloc (sizeof(lien));
					pl->p1=ps; pl->p2=ps->link.t[i]; pl->importance=0;
					pal->t[pal->n] = pl ;
					pal->n++;
					pap=bestpath1(level, ps->link.t[i], tailleParcours-1, pap, pal, n, parcours);
					pal->n--;
				}
			}
			for(i=0; i<ps->locked.n;i++){
				if(!belong(ps->locked.t[i]->num,n,parcours)){
					pap=bestpath1(level,ps->locked.t[i], tailleParcours, pap, pal,n,parcours);
				}
			}
		}
		return pap;
}
arrayParcours * bestpath(tab level,int tailleParcours){
	int parcours[100];
	int n=0;
	arrayParcours * pap;
	arrayLien* pal;
	pap=(arrayParcours *) malloc(sizeof(arrayParcours));
	pap->n=0;
	pal=(arrayLien *) malloc(sizeof(arrayLien));
	pal->n=0;
	return bestpath1(level, level.t[0], tailleParcours, pap, pal,n, parcours);
}
//return an array of all the paths of size tailleparcours
	
arrayLien* addlien(lien* pl, arrayLien* pal){
	int i;
	for(i=0;i<pal->n;i++){
		if(pl->p1==pal->t[i]->p1){
			if(pl->p2==pal->t[i]->p2){
				pal->t[i]->importance++;
				return pal;
			}
		}
		else if(pl->p1==pal->t[i]->p2){
			if(pl->p2==pal->t[i]->p1){
				pal->t[i]->importance++;
				return pal;
			}
		}
	}
	pal->t[pal->n]=pl;
	pal->n++;
	return pal;
}
// ajoute le lien pointé par lien* au tableau de de lien pal, ou incrémente l'importance du lien si il y est déjà

	
arrayLien* incrementlien(lien* pl, arrayLien* pal){
	int i;
	for(i=0;i<pal->n;i++){
		if(pl->p1==pal->t[i]->p1){
			if(pl->p2==pal->t[i]->p2){
				pal->t[i]->importance++;
				return pal;
			}
		}
		else if(pl->p1==pal->t[i]->p2){
			if(pl->p2==pal->t[i]->p1){
				pal->t[i]->importance++;
				return pal;
			}
		}
	}
	return pal;
}
//incrémente l'importance du lien pointé par lien* si celui-ci est dans pal

arrayLien* veriflien(arrayLien* pal){
	int max=0;
	int i;
	for(i=0;i<pal->n;i++){
		if(pal->t[i]->importance>max){
			max=pal->t[i]->importance;
		}
	}
	arrayLien* resultat = (arrayLien *) malloc(sizeof(arrayLien));
	resultat->n=0;
	for(i=0;i<pal->n;i++){
		if(pal->t[i]->importance==max){
			resultat->t[resultat->n]=pal->t[i];
			resultat->n++;
		}
	}
	return resultat;
}
//cherche dans le tableau de lien pal le(s) lien(s) avec l'importance la plus grande et le(s) renvoie

lien* bestlink2(tab level, arrayParcours * pap, arrayLien* pal, int tailleParcours){
	int i,j;
	while(tailleParcours<15){
		tailleParcours++;
		pap=bestpath(level, tailleParcours);
		for(i=0;i<pap->n;i++){
			for(j=0;j<pap->t[i]->n;j++){
				pal=incrementlien(pap->t[i]->t[j],pal);
			}
		}
		pal=veriflien(pal);
		if(pal->n==1){
			return pal->t[0];
		}
	}
	return pal->t[0];
}

lien* bestlink(tab level){
	int i,j,k;
	arrayParcours* pap;
	arrayLien* resultat;
	pap=(arrayParcours*) malloc ((size_t) sizeof(arrayParcours));
	pap->n =0;
	resultat=(arrayLien*) malloc ((size_t) sizeof(arrayLien));
	resultat->n=0;
	for(i=1;i<15;i++){
		pap=bestpath(level,i);
		if(pap->n>0){
			for(j=0;j<pap->n;j++){
				for(k=0;k<pap->t[j]->n;k++){
					resultat=addlien(pap->t[j]->t[k],resultat);
				}
			}
			resultat=veriflien(resultat);
			if(resultat->n==1){
				return resultat->t[0];
			}
			return bestlink2(level, pap, resultat,i);
		}		
	}
	return resultat->t[0];
}
//renvoie le pointeur du meilleur lien possible du graphe donné en entrée