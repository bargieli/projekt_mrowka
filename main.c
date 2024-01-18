#include <stdio.h>
#include <time.h>

#include "fun1.h"
#include "funkcje2.h"

#define MAX_NAZWA 1000

int main(int argc, char **argv) {

	printf("argc: %d\n", argc);
	if(argc < 4 || argc > 7) {
		fprintf(stderr, "Brak potrzebncyh danych wejściowych do uruchomienia progrmau.\n");
		return 1;
	}

	for( int i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
		printf("czy procent %d\n", czy_proc(argv[i]) );
	}

	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int iter = atoi(argv[3]);
//	char *prefix = argv[4];
	char kier = argv[4][0];

	char *prefix;
	char *plik;

	char **plansza = malloc(m);
	for(int i = 0; i < m; i++) {
		plansza[i] = malloc(n);
	}

	mrowka ant = gen_mrowka(m, n, kier);

	int proc;

	
	if(argc == 7) {
		printf("Wejście do pętli z warunkiem (argc == 7)\n");
		if( !(czy_proc(argv[5]) && !(czy_proc(argv[6]) ) ) ) {
			printf("Wejście do pętli z warunkiem, że obydwa nie są proc\n");
			FILE *plik_wej1, *plik_wej2;		
			plik_wej1 = fopen(argv[5], "r");
			plik_wej2 = fopen(argv[6], "r");

// sprawdza czy podany plik istnieje, jeżeli tak to wczytuje mape z pliku - wczyt_plasza, jeżel nie to sprawdza czy pierwszy znak argv[6] jest cyfrą, jeżeli tak to uruchamia funkcje generującą mapę
//jeżeli plik_wej1 istnieje lub obydwa istnieją do plik_wej1 jest plikiem do wczytania, a nazwę plik_wej2 traktuje jako prefix

			if(plik_wej1 != NULL ) {
				// wczyt_plansza( ! DO UZUPEŁNIENIA ! );
				fclose(plik_wej1);
				prefix = argv[6];
				plik = argv[5];
				printf("plik: %s        prefix: %s\n", plik, prefix);
				
			} else if(plik_wej2 != NULL ) {

				// wczyt_plansza( ! DO UZUPEŁNIENIA ! );
                       		fclose(plik_wej2);
				prefix = argv[5];
				plik = argv[6];
				printf("plik: %s	prefix: %s\n", plik, prefix);
			} 			

		        srand(time(NULL));
              		proc = rand() % 101;
              		// gen_mapa( ! DO UZUPEŁNIENIA ! );
		
		} else {
			FILE *plik_wej;
			if( czy_proc(argv[6]) ) {
				proc = atoi(argv[6]);
                        	// genruje mape na podstawie podanego proc
                        	//gen_mapa( ! DO UZUPEŁNIENIA ! );
			} else {
				srand(time(NULL));
                      		proc = rand() % 101;
                       		// gen_mapa( ! DO UZUPEŁNIENIA ! );
			}
			
			plik_wej = fopen(argv[5], "r");
			if( plik_wej != NULL ) {
				// wczyt_plansza( ! DO UZUPEŁNIENIA ! );
                                fclose(plik_wej);
				plik = argv[5];
			} else {
				prefix = argv[5];
			}
		}
	} else if (argc == 6) {
		if( !(czy_proc(argv[5]) ) ) {
			 FILE *plik_wej1;    
                 	plik_wej1 = fopen(argv[5], "r");
			if( plik_wej1 != NULL ) {
				 // wczyt_plansza( ! DO UZUPEŁNIENIA ! );
                                fclose(plik_wej1);
				plik = argv[5];
			} else {
                                prefix = argv[5];
                        }
			srand(time(NULL));
                        proc = rand() % 101;
                        // gen_mapa( ! DO UZUPEŁNIENIA ! )

		} else if ( czy_proc(argv[5] ) ) {
			proc = atoi(argv[5]);
		} else { 
			fprintf(stderr, "Błąd podanych parametrów.\n");
		}
	}	
			 
	if (prefix != NULL ) {		
		char nazwa_pliku[MAX_NAZWA];

		sprintf( nazwa_pliku, "%s_", prefix);
		printf("nazwa pliku: %s\n", nazwa_pliku);
	}
 
	printf("kolumny: %d	wiersze: %d\n", n, m);
	printf("kierunek: %c\n", kier);
	printf("iteracje: %d\n", iter);
	printf("plik: %s\n", plik);
	printf("prefix: %s\n", prefix);
	printf("proc: %d\n", proc);

/*  tu samo działanie programu, obecnie dostępne zmienne z których można korzystać
		m - wiersza
		n-kolumny
		iter - liczba iteracji
		kier - kierunek poczatkowy 
		plik_wyj - nazwa pliku wyjściowego
		
		w zależności od podaanej danej wejściowej:
		proc - procent zapełnienia planszy
		plik_wej - plik wejściowy	
		prefix			*/
	

	for(int i = 0; i < m; i++) {	
		free(plansza[i]);
	}
	free(plansza);
//	fclose(plik_wyj);
	
	return 0;
	
} 
