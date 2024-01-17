#ifndef FUN1_H
#define FUN1_H	

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int m;	//wiersz
	int n;	//kolumna
	char kier; 
}mrowka;

mrowka gen_mrowka(int m, int n, char kier_wej);

void rys_plansza( FILE *plik, int m, int n, char **plansza, mrowka ant);

#endif
