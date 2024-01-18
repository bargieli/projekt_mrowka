#ifndef FUNKCJE2_H
#define FUNKCJE2_H

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int m; //wiersz
    int n; //kol
    char kier; //GDPL
} mrowka;

//obrot, zmiana koloru komorki, krok do przodu
mrowka ruch (char** mapa, mrowka mr, int iteracje, int m, int n);

//generuje mape zaleznie od podanego procentu zapelnienia
char** gen_mapa(int m, int n, int procent);

//po prostu printuje zawartosc tablicy
void drukuj_mape (int m, int n, char** map);

//free
void zwolnij_mape (int m, int n, char** map);

//wczytuje mape z podanego pliku
char** czytaj_mape_z_pliku(int m, int n, FILE* plik);


#endif
