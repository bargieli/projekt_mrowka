#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>


typedef struct {
    int m; //wiersz
    int n; //kol
    char kier; //GDPL
} mrowka;



char skret_w_prawo(char akt){
    if(akt=='G'){
        return 'P';
    }
    if(akt=='P'){
        return 'D';
    }
    if(akt=='D'){
        return 'L';
    }
    if(akt=='L'){
        return 'G';
    }
}


char skret_w_lewo(char akt){
    if(akt=='G'){
        return 'L';
    }
    if(akt=='P'){
        return 'G';
    }
    if(akt=='D'){
        return 'P';
    }
    if(akt=='L'){
        return 'D';
    }
}

mrowka przesun_do_przodu(mrowka mr, int m, int n){
    if(mr.kier=='G'){
        if(mr.m>0){
            mr.m--;
        }
    }
    if(mr.kier=='P'){
        if(mr.n<n-1){
            mr.n++;
        }
    }
    if(mr.kier=='D'){
        if(mr.m<m-1){
            mr.m++;
        }
    }
    if(mr.kier=='L'){
        if(mr.n>0){
            mr.n--;
        }
    }
    return mr;
}




// funkcja odpalona w petli for(int i=0; i<iter; i++)
mrowka ruch (char** mapa, mrowka mr, int iteracje, int m, int n){
    if(mapa[mr.m][mr.n]==' '){
        mr.kier = skret_w_prawo(mr.kier);
        mapa[mr.m][mr.n]='B';
        mr = przesun_do_przodu(mr, m, n);
    } else if(mapa[mr.m][mr.n]=='B'){
        mr.kier = skret_w_lewo(mr.kier);
        mapa[mr.m][mr.n]=' ';
        mr = przesun_do_przodu(mr, m, n);
    }
    return mr;
}

char** gen_mapa(int m, int n, int procent){
    //uwaga: zaokraglenie ilosci komorek zawsze do dolu
    int ile_kom = (m*n*procent)/100;
    char** mapa = (char **)calloc(m, sizeof(char *));
    char czy_czarne[m*n];
    
    //generowanie pomocniczej mapy czy_czarne
    srand(time(NULL));
    int losowa = rand() % (m*n);
    for(int i=0; i<ile_kom; i++){
        while(czy_czarne[losowa]=='1'){
            losowa = rand() % (m*n);
        }
        czy_czarne[losowa]='1';
    }
    
    //zapis faktycznej mapy
    int x=0;
    for (int i = 0; i < m; i++) {
        mapa[i] = (char *)calloc(n, sizeof(char));
        for(int j=0; j<n; j++) {
            if(czy_czarne[x]=='1'){
                mapa[i][j]='B';
            } else {
                mapa[i][j]=' ';
            }
            x++;
        }
    }
    return mapa;
}


void drukuj_mape (int m, int n, char** map){
    for (int i = 0; i < m; i++) {
        for(int j=0; j<n; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}


void zwolnij_mape (int m, int n, char** map){
    for (int i = 0; i < m; i++) {
        free(map[i]);
    }
    free(map);
}

char** czytaj_mape_z_pliku(int m, int n, FILE* plik){
    setlocale(LC_ALL, "en_US.UTF-8");

    char** mapa = (char**)calloc(m, sizeof(char*));
    wchar_t znak;
    
    for(int i=0; i<m; i++){
        mapa[i] = (char*)calloc(n, sizeof(char));
    }
    
    int l=0;
    for(int i=0; i<m; i++){
        for (int j = 0; j < n; j++) {
            l=0;
            fwscanf(plik, L"%lc", &znak);
            
            //"█"
            if(znak == L'\u2588'){
                l++;
            }
            if(znak == L' '){
                l++;
            }
            
            if(l==0){
                j--;
            } else {
                if (znak == L'\u2588') {
                    mapa[i][j] = 'B';
                } else if (znak == L' '){
                    mapa[i][j] = ' ';
                }
            }
        }
    }
    return mapa;
}





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
    printf("%d %d %c\n", ant.m, ant.n, ant.kier);
    printf("---------------------------\n");
    
    for(int i=0; i<iter; i++){
        ant = ruch(mapa, ant, iter, m, n);
        drukuj_mape(m, n, mapa);
        printf("%d %d %c\n", ant.m, ant.n, ant.kier);
        printf("---------------------------\n");
    }
    
    //drukuj_mape(m, n, mapa);
    zwolnij_mape(m, n, mapa);

    
    return 0;
}
