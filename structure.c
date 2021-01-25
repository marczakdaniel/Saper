#include "structure.h"

Pole Board[13][13];

int min(int a, int b) {
    if (a > b)
        return b;
    return a;
}

void randMine(void) {
    int zarodek;
    time_t tt;
    zarodek = time(&tt);
    srand(zarodek);
    int count = 0;
    while (count != 10) {
        int i = rand()%9 + 1, j = rand() % 9 + 1;
        if (Board[i][j].mina != -1) {
            Board[i][j].mina = -1;
            count++;
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Board[i][j].mina != -1)
                Board[i][j].mina -= min(0,Board[i-1][j-1].mina)+
                                min(0,Board[i-1][j].mina)+
                                min(0,Board[i-1][j+1].mina)+
                                min(0,Board[i][j-1].mina)+
                                min(0,Board[i][j+1].mina)+
                                min(0,Board[i+1][j-1].mina)+
                                min(0,Board[i+1][j].mina)+
                                min(0,Board[i+1][j+1].mina);
        }
    }
}
void printBoard(void) {
    printf("  ");
    for (int i = 'A'; i < 'A' + 9; i++) {
        printf("| %c ", i);
    }
    printf("|\n");
    for (int i = 1; i <= 9; i++) {
        printf("%d ", i);
        for (int j = 1; j <= 9; j++) {
            char znak = ' ';
            if (Board[i][j].ukryte == 1) {
                if (Board[i][j].mina == 0) {
                    znak = ' ';
                }
                else {
                    znak = Board[i][j].mina + '0';
                }
            }
            if (Board[i][j].flaga == 1)
                znak = 'F';
            printf("| %c ", znak);
        }
        printf("|\n");
    }
}

void wybor(void) {
    printf("Wybierz opcje:\nO - odkrycie pola\nF - postawienie flagi\n");
    char opcja = getchar();
    while (opcja != 'O' && opcja != 'F') {
        opcja = getchar();
    }
    printf("Wybierz pole: (np. A2) \n");
    char kolumna = getchar();
    while (kolumna < 'A' || kolumna > 'I') {
        kolumna = getchar();
    }
    char wiersz = getchar();
    while (wiersz < '1' || wiersz > '9') {
        wiersz = getchar();
    }
    getchar();
    printf("%c %c%c", opcja, kolumna, wiersz);
}

