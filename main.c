#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "fun1.h"
#include "funkcje2.h"

#define MAX_NAZWA 1000

int main(int argc, char **argv) {

	int parametry;

	int m, n, iter;
	double proc;
	char *prefix;
	char  *plik;
	char kier;

	while( ( parametry = getopt(argc, argv, "m:n:k:i:p:r:f:" ) ) != -1 ) {
		switch (parametry) {
			case 'm':
				m = atoi(optarg);
				break;
			case 'n': 
				n = atoi(optarg);
				break;
			case 'k':
				kier = optarg[0];
				break;
			case 'i':
				iter = atoi(optarg);
				break;
			case 'p':
				prefix = optarg;
				break;
			case 'r':
				proc = atof(optarg);
				break;
			case 'f':
				plik = optarg;
				break;
			case '?':
				fprintf(stderr, "Brak możlwiości wprowadzenia podanego parametru.\n");
				break;
		}
	}

	 if (m == -1 || n == -1 || iter == -1 || kier == '\0') { 
		fprintf(stderr, "Brak obowiązkowych parametrów do uruchomienia programu");
		return 1;
	 }

	char **plansza = malloc(m);
	for(int i = 0; i < m; i++) {
		plansza[i] = malloc(n);
	}

	mrowka ant = gen_mrowka(m, n, kier);

	FILE *plik_wej = fopen(plik, "r");

	if (plik_wej != NULL) { 
		plansza = czytaj_mape_z_pliku(m, n, plik_wej);
		fclose(plik_wej);
	} else if ( proc > 0 && proc < 101) {
		plansza = gen_mapa(m, n, proc);
	} else {
		srand(time(NULL));
        proc = (double)rand() / RAND_MAX * 100.0;
        plansza = gen_mapa( m, n, proc );
	}

	printf("Parametry startowe:\n");
	printf("wiersze: %d\n", m);
	printf("kolumny: %d	\n", n);
	printf("kierunek: %c\n", kier);
	printf("iteracje: %d\n", iter);
	printf("plik: %s\n", plik);
	printf("prefix: %s\n", prefix);
	printf("proc: %f\n", proc);

	char nazwa_pliku[MAX_NAZWA];
	
	FILE *plik_wyj = NULL;


	for(int i = 0; i < iter; i++) {		
	
		if (prefix != NULL ) {		
			sprintf( nazwa_pliku, "%s_%diteracji", prefix, i);
			plik_wyj = fopen(nazwa_pliku, "w");
//			printf("Nazwa pliku:%s\n", nazwa_pliku);
			rys_plansza(plik_wyj, m, n, plansza, ant);
		} else {
			rys_plansza_stdout( m, n, plansza, ant);
		}	
		ant = ruch(plansza, ant, iter, m, n);
	}

	for(int i = 0; i < m; i++) {	
		free(plansza[i]);
	}
	free(plansza);
	return 0;
	
} 
