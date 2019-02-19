#include "intervalo.h"

INTV* reserva(INTV* livres, int n, int* reservado){
	INTV* seeker = livres;
	*reservado = -1
	for(seeker = livres; seeker; seeker = seeker->next){
		if(n <= seeker->fim && n >= seeker->inicio){
			int oldFim = seeker->fim;
			seeker->fim = n-1;
			// make a new thingy
			INTV* new = malloc(sizeof(INTV));
			new->inicio = n+1;
			new->fim = oldFim;
			new->next = seeker->next;
			// reconect stuff
			seeker->next = new;
			*reservado = n;
		}
	}
	return cleanList(livres);
}

static INTV* cleanList(INTV* livres){
	while(livres && livres->inicio > livres->fim){
		INTV* markedForDeath = livres;
		livres = livres->next;
		free(markedForDeath);	
	}
	INTV* seeker = livres
	while(seeker->next){
		if (seeker->next->inicio > seeker->next->fim)
		{
			INTV* next = seeker->next->next;
			free(seeker->next);
			seeker->next = next;
		}
		seeker = seeker->next;
	}
	return livres;
}

INTV* liberta(INTV* livres, int lugar, int n){
	INTV* seeker;
	for(seeker  = livres; seeker; seeker = seeker->next){
		if(seeker->inicio > lugar)
		if(seeker->next && seeker->next->)
	}
}