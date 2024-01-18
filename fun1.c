#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include<string.h>

#include "fun1.h"

// LINE_VERTICAL:│
// LINE_HORIZONTAL:─
// LINE_DOWN_RIGHT:┌
// LINE_DOWN_LEFT:┐
// LINE_UP_RIGHT:└
// LINE_UP_LEFT:┘
// SQUARE_WHITE: 
// SQUARE_BLACK:█
// ARROW_NORTH_WHITE:△
// ARROW_NORTH_BLACK:▲
// ARROW_EAST_WHITE:▷
// ARROW_EAST_BLACK:▶
// ARROW_SOUTH_WHITE:▽
// ARROW_SOUTH_BLACK:▼
// ARROW_WEST_WHITE:◁
// ARROW_WEST_BLACK:◀

mrowka gen_mrowka(int m, int n, char kier_wej) {
	mrowka ant;
	ant.m = m/2;
	ant.n = n/2;
	ant.kier = kier_wej;
	printf("%d, %d, %c\n", ant.m, ant.n, ant.kier);
	
	return ant;
}

void wyjscie( FILE *plik, int m, int n, int i) {
	 fprintf(plik, "iter = %d, m = %d, n = %d\n", i, m, n);
}
void rys_plansza(FILE *plik, int m, int n, char **plansza, mrowka ant) {
    setlocale(LC_ALL, "C.UTF-8");

	//printf("Plik %p\n", (void *)plik);
	plik = stdout;
    fprintf(plik, "┌");
    for (int kol = 0; kol < n; kol++) {
        fprintf(plik, "─");
    }
    fprintf(plik, "┐\n");

    for (int wier = 0; wier < m; wier++) {
        fprintf(plik, "│");
        for (int kol = 0; kol < n; kol++) {
            if (wier == ant.m && kol == ant.n) {
                if (ant.kier == 'G') {
                    fprintf(plik, "▲");
                } else if (ant.kier == 'D') {
                    fprintf(plik, "▼");
                } else if (ant.kier == 'L') {
                    fprintf(plik, "◀");
                } else if (ant.kier == 'P') {
                    fprintf(plik, "▶");
                }
            } else {
                if (plansza[wier][kol] == ' ') {
                    fprintf(plik, " ");
                } else {
                    fprintf(plik, "█");
                }
            }
        }
        fprintf(plik, "│\n");
    }

    fprintf(plik, "└");
    for (int kol = 0; kol < n; kol++) {
        fprintf(plik, "─");
    }
    fprintf(plik, "┘\n");

	if (plik != stdout )
			fclose(plik);	
}


void rys_plansza_stdout( int m, int n, char **plansza, mrowka ant) {
	setlocale(LC_ALL, "C.UTF-8");
/*
	if( plik_wyj == NULL ) {
		plik = stdout;
	} else {s
		plik = fopen(plik_wyj, "w");
	}
*/
	//printf("Plik %p\n", (void *)plik);

	printf( "┌");
	for(int kol = 0; kol < n; kol++) {
		printf("─");
	}
	printf("┐\n");

	for(int wier = 0; wier < m; wier++) {
		printf( "│");
		for( int kol = 0; kol < n; kol++) {
	  		if (wier == ant.m && kol == ant.n) {
				if (ant.kier == 'G'){	
					printf( "▲");
				} else if (ant.kier == 'D') {
					printf( "▼");
				} else if (ant.kier == 'L') {
					printf( "◀");
				} else if (ant.kier == 'P') {
					printf( "▶");
				}
			} else {
				if (plansza[wier][kol] == ' ') {
					printf( " "); 
				} else {
					printf( "█");
				}
			}
		}
		printf ("│\n");
	}

	printf("└");
        for(int kol = 0; kol < n; kol++) {
                printf( "─");
        }
	printf("┘\n");
}

int czy_litery(const char *str) {
	int i = 0;
	if( ( str[i] > 'Z' && str[i] > 'A' ) || ( str[i] < 'z' && str[i] > 'a') ) {
		return 0;
	}
	return 1;
}

int czy_proc( char *parametr ) {
	for( int i = 0; i < 2; i++ ) {
		if(!( parametr[i] <= '9' && parametr[i] >= '0')	) {
			return 0;
		}
	}
	return 1;
}

