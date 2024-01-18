#include <stdio.h>
#include <time.h>

#include "funkcje2.h"


int main(int argc, char** argv){
    int m, n, iter, procent;
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    iter = atoi(argv[3]);
    FILE* plik = fopen(argv[4], "r");
    procent = atoi(argv[5]);

    if(procent>100){
        procent = 100;
    }
    
    
    mrowka ant;
    ant.m = m/2;
    ant.n = n/2;
    ant.kier = 'G';
    
    
    char** mapa = gen_mapa(m, n, procent);
    //char** mapa = czytaj_mape_z_pliku(m, n, plik);
    drukuj_mape(m, n, mapa);
    //printf("%d %d %c\n", ant.m, ant.n, ant.kier);
    printf("---------------------------\n");
    
    for(int i=0; i<iter; i++){
        ant = ruch(mapa, ant, iter, m, n);
        drukuj_mape(m, n, mapa);
        //printf("%d %d %c\n", ant.m, ant.n, ant.kier);
        printf("---------------------------\n");
    }
    
    zwolnij_mape(m, n, mapa);

    
    return 0;
}
