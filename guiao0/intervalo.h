#ifndef __INTERVALO_H__
#define __INTERVALO_H__ 

typedef struct intv
{
	int inicio;
	int fim;
	struct intv* next;
	
} INTV;


INTV* reserva(struct intv* livres, int n, int* reservado);

INTV* liberta(struct intv* livres, int lugar, int n);

#endif
