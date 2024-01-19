#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

#include "fun1.h"

#include "funkcje2.h"

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
    
    for(int i=0; i<m*n; i++){
        czy_czarne[i]='0';
    }
    
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

char** czytaj_mape_z_pliku(int m, int n, FILE* plik, mrowka* ant){
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
            //△
            if(znak == L'\u25B3'){
                l++;
                ant->m = i;
                ant->n = j;
                ant->kier = 'G';
                mapa[i][j] = ' ';
            }
            if(znak == L'\u25B2'){
                l++;
                ant->m = i;
                ant->n = j;
                ant->kier = 'G';
                mapa[i][j] = 'B';
            }
            //▷
            if(znak == L'\u25B7'){
                l++;
                ant->m = i;
                ant->n = j;
                ant->kier = 'P';
                mapa[i][j] = ' ';
            }
            if(znak == L'\u25B6'){
                l++;
                ant->m = i;
                ant->n = j;
                ant->kier = 'P';
                mapa[i][j] = 'B';
            }
            //▽
            if(znak == L'\u25BD'){
                l++;
                ant->m = i;
                ant->n = j;
                ant->kier = 'D';
                mapa[i][j] = ' ';
            }
            if(znak == L'\u25BC'){
                l++;
                ant->m =  i;
                ant->n = j;
                ant->kier = 'D';
                mapa[i][j] = 'B';
            }
            //◁
            if(znak == L'\u25C1'){
                l++;
                ant->m = i;
                ant->n = j;
                ant->kier = 'L';
                mapa[i][j] = ' ';
            }
            if(znak == L'\u25C0'){
                l++;
                ant->m = i;
                ant->n = j;
                ant->kier = 'L';
                mapa[i][j] = 'B';
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






