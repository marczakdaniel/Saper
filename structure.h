#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*
    Dane:
        mina:
            -1 - na tym polu znajduje sie mina
             0
             1
             2
             3
             4 - liczba min w okolicy
             5
             6
             7
             8
        flaga:
             0 - gracz nie ustawil na ty polu flagi
             1 - gracz ustawil na tym polu flage
        ukryte:
             0 - pole ukryte przed graczem
             1 - pole widoczne
*/

#define MINA -1

typedef struct p {
    int mina;
    bool flaga;
    bool widoczne;
} Pole;


void randMine(void);

void printBoard(void);

void wybor(void);

int min(int a, int b);

void zaznacz_DFS(int i, int j);

void zaznacz(int i, int j);

void koniec(void);

void init(void);

void zaznacz_pierw(void);

bool czy_wygrana(void);

void rozmiar_pola(void);

void statystyki(void);

