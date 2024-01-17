#include <stdio.h>
#include <time.h>

#include "fun1.h"

#define MAX_NAZWA 1000

int main(int argc, char **argv) {
	if(argc != 5 && argc != 6) {
		fprintf(stderr, "Brak potrzebncyh danych wejściowych do uruchomienia progrmau.\n");
		return 1;
	}

	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int iter = atoi(argv[3]);
	char *prefix = argv[4];
	char kier = argv[5][0];
	
	char **plansza = malloc(m);
	for(int i = 0; i < m; i++) {
		plansza[i] = malloc(n);
	}

	mrowka ant = gen_mrowka(m, n, kier);

	if(argc == 6) {

		FILE *plik_wej;		
		plik_wej = fopen(argv[6], "r");

// sprawdza czy podany plik istnieje, jeżeli tak to wczytuje mape z pliku - wczyt_plasza, jeżel nie to sprawdza czy pierwszy znak argv[6] jest cyfrą, jeżeli tak to uruchamia funkcje generującą mapę
		if(plik_wej != NULL) {
			// wczyt_plansza( ! DO UZUPEŁNIENIA ! );
			fclose(plik_wej);
		} else {
			if( argv[6][0] <= '9' && argv[6][0] >= '0') {
				int proc = atoi(argv[6]);

				// genruje mape na podstawie podanego proc 
				// gen_mapa( ! DO UZUPEŁNIENIA ! );
			}
		}
	} else {

// losowo generuje int od 0 do 100 i generuje na tej podstawie plansze
		srand(time(NULL));
		int proc = rand() % 101;
		// gen_mapa( ! DO UZUPEŁNIENIA ! );    
	}			

	char nazwa_pliku[MAX_NAZWA];

	sprintf( nazwa_pliku, "%s_%diteracji.txt", prefix, iter);

	FILE *plik_wyj = fopen( nazwa_pliku, "w");
	
	if( plik_wyj == NULL) {
		fprintf(stderr, "Błąd przy otwieraniu pliku wyjściowego.\n");
		return 1;
	}


/*  tu samo działanie programu, obecnie dostępne zmienne z których można korzystać
		m - wiersza
		n-kolumny
		iter - liczba iteracji
		kier - kierunek poczatkowy 
		plik_wyj - nazwa pliku wyjściowego
		
		w zależności od podaanej danej wejściowej:
		proc - procent zapełnienia planszy
		plik_wej - plik wejściowy				*/


	for(int i = 0; i < m; i++) {	
		free(plansza[i]);
	}
	free(plansza);
	fclose(plik_wyj);
	
	return 0;
	
} 
