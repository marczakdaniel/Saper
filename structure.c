#include "structure.h"

Pole Board[13][13];
bool KONIEC = 0;
bool PIERW = 0;

int W, P; // wygrane przegrane

int N = 9;
int ILE_MIN = 10;
int ILE_FLAG = 0;
time_t poc;

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
    while (count != ILE_MIN) {
        int i = rand()%N + 1, j = rand() % N + 1;
        if (Board[i][j].mina != MINA &&
            Board[i-1][j-1].widoczne == 0&& Board[i-1][j].widoczne == 0&& Board[i-1][j+1].widoczne == 0&&
            Board[i][j-1].widoczne == 0&& Board[i][j].widoczne == 0&& Board[i][j+1].widoczne == 0&&
            Board[i+1][j-1].widoczne == 0&& Board[i+1][j].widoczne == 0&& Board[i+1][j+1].widoczne == 0) {
            Board[i][j].mina = MINA;
            count++;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (Board[i][j].mina != MINA)
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
    printf("   ");
    for (int i = 'A'; i < 'A' + N; i++) {
        printf("| %c ", i);
    }
    printf("|\n");
    for (int i = 1; i <= N; i++) {
        printf("%2d ", i);
        for (int j = 1; j <= N; j++) {
            char znak = ' ';
            if (Board[i][j].widoczne == 1) {
                if (Board[i][j].mina == 0) {
                    znak = ' ';
                }
                else {
                    znak = Board[i][j].mina + '0';
                }
            }
            else {
                znak = '-';
            }
            if (Board[i][j].flaga == 1)
                znak = 'F';
            printf("| %c ", znak);
        }
        printf("|\n");
    }
}

void wybor(void) {
    printf("Postawiono %d flag!\nNa planszy jest %d min!\n", ILE_FLAG, ILE_MIN);
    printf("Grasz juz %ld sekund!\n", time(NULL) - poc);
    printf("Wybierz opcje:\nO - odkrycie pola\nF - postawienie flagi\nU - usuniecie flagi\n");
    char opcja = getchar();
    while (opcja != 'O' && opcja != 'F' && opcja != 'U') {
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
    if (opcja == 'O') {
        zaznacz(wiersz - '1' + 1, kolumna - 'A' + 1);
    }
    if (opcja == 'F') {
        if (Board[wiersz - '1' + 1][kolumna - 'A' + 1].flaga == 0)
            ILE_FLAG++;
        Board[wiersz - '1' + 1][kolumna - 'A' + 1].flaga = 1;
    }
    if (opcja == 'U') {
        if (Board[wiersz - '1' + 1][kolumna - 'A' + 1].flaga == 1)
            ILE_FLAG--;
        Board[wiersz - '1' + 1][kolumna - 'A' + 1].flaga = 0;
    }
}

void zaznacz_DFS(int i, int j) {
    Board[i][j].widoczne = 1;
    if (Board[i][j].mina == 0) {
        if (i < 9 && Board[i + 1][j].widoczne == 0) zaznacz_DFS(i + 1, j);
        if (i > 1 && Board[i - 1][j].widoczne == 0) zaznacz_DFS(i - 1, j);
        if (j < 9 && Board[i][j + 1].widoczne == 0) zaznacz_DFS(i, j + 1);
        if (j > 1 && Board[i][j - 1].widoczne == 0) zaznacz_DFS(i, j - 1);
        if (i < 9 && j < 9 && Board[i + 1][j + 1].widoczne == 0) zaznacz_DFS(i + 1, j + 1);
        if (i < 9 && j > 1 && Board[i + 1][j - 1].widoczne == 0) zaznacz_DFS(i + 1, j - 1);
        if (i > 1 && j < 9 && Board[i - 1][j + 1].widoczne == 0) zaznacz_DFS(i - 1, j + 1);
        if (i > 1 && j > 1 && Board[i - 1][j - 1].widoczne == 0) zaznacz_DFS(i - 1, j - 1);
    }
}
void zaznacz(int i, int j) {
    if (Board[i][j].widoczne == 1) {

        return;
    }
    if (Board[i][j].flaga == 1) {
        printf("JEST FLAGA!");
        return;
    }
    if (Board[i][j].mina == 0) {
        zaznacz_DFS(i, j);
    }
    if (Board[i][j].mina == MINA) {
        koniec();
    }
    else {
        Board[i][j].widoczne = 1;
    }
}

void koniec(void) {
    printf("PRZEGRALES!\n :(((((((");
    P++;
    KONIEC = 1;
}

void zaznacz_pierw(void) {
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
    Board[wiersz - '1' + 1][kolumna - 'A' + 1].widoczne = 1;
    randMine();
    zaznacz_DFS(wiersz - '1' + 1, kolumna - 'A' + 1);
}

bool czy_wygrana() {
    int count = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (Board[i][j].flaga == 1) {
                if (Board[i][j].mina != -1) {
                    return false;
                }
                else {
                    count++;
                }
            }
        }
    }
    if (count == ILE_MIN)
        return true;
    return false;
}

void rozmiar_pola() {
    printf("Wybierz trudnosc:\n 1 - Podstawowy\n2 - Sredni\n3 - Zaawansowany\n");
    char trud = getchar();
    while (trud != '1' && trud != '2' && trud != '3') {
        getchar();
    }
    getchar();
    if (trud == '1') {
        N = 9;
        ILE_MIN = 10;
    }
    else if (trud == '2') {
        N = 16;
        ILE_MIN = 40;
    }
    else if (trud == '3') {
        N = 24;
        ILE_MIN = 99;
    }
}

void statystyki(void) {
    printf("\nProcent wygranych gier: %.2f %% \n", (double)W / (double)(W + P));
    FILE * plik;
    plik = fopen("stat.txt", "w");
    fprintf(plik, "%d %d", W, P);
    fclose(plik);
}

void init(void) {
    //rozmiar_pola();
    FILE * plik;
    plik = fopen("stat.txt", "r");
    fscanf(plik, "%d %d", &W, &P);
    fclose(plik);
    printBoard();
    zaznacz_pierw();
    time(&poc);
    while (!KONIEC) {
        system("clear");
        printBoard();
        if (czy_wygrana()) {
            printf("Wygrales!!!\n:))))))\n");
            printf("Zajelo ci to %ld sekund!\n", time(NULL) - poc);
            KONIEC = 1;
            W++;
            return;
        }
        wybor();
    }
}

