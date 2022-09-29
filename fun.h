#include <ncurses.h>

void muovi(int **gioco, int mossa);
void stampa(int **gioco, int size, WINDOW * new_win);
int valida(int **gioco, int mossa);
int risolto(int **gioco, int size);
void swap(int **gioco, int size);
void checkmalloc(int **gioco);