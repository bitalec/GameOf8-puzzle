#include <stdio.h>
#include "fun.h"
#include "fun.c"
#include <ncurses.h>


int main (void){
    int c;
    int mossa;
    
    //int table[DIM][DIM] = {{1,2,3,4}, {6,5,7,8},{9,10,11,12}, {13,14,15,0}};
    
    int **table = random_game3(3);
    
    int fine;
    
    initscr();
    raw();
    cbreak();

    printw("*******BENVENUTO NEL GIOCO DEL 15*********\n\n\n");
    fine = risolto2(table,3);
    stampa(table,3);
    
    //finchè fine è diverso da 0 il gioco non è finito quindi cicla
    while(!fine){
        printw("\nQuale numero vuoi spostare?: ");
        refresh();
        scanw("%i", &mossa);

        if(valida(table,mossa)){
            muovi(table,mossa);
            
            clear();
            printw("\n");
            
            stampa(table,3);
            fine = risolto2(table,3);
            
        }
        else{
            
            clear();
            printw("La mossa inserita non è valida, riprova\n");
            stampa(table,3);
        }

        
        
    }
    printw("Complimenti Hai completato il gioco");

    endwin();
return 0;
}

//provaprova