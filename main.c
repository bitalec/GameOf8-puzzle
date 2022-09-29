#include <stdlib.h>
#include "fun.h"
#include "fun.c"
#include <ncurses.h>

#define DIM 3


int main (void){
    int c;
    int mossa;
    WINDOW * new_win;
    
    //int table[DIM][DIM] = {{1,2,3,4}, {6,5,7,8},{9,10,11,12}, {13,14,15,0}};
    
    //crea una matrice di dimensione 3x3
    int **table = random_game3(3);
    
    int fine = 0;
    
    //inizio di ncurses
    initscr();
    raw();
    cbreak(); //wgetch prende un solo carattere con questa funzione attiva
    echo(); //non stampa il carattere preso con getch
    
    new_win = newwin(10,50,7,10);   //creo una nuova finestra
    
    wprintw(new_win,"\n BENVENUTO NEL GIOCO DEL 8\n\n"); 
    stampa(table,DIM,new_win);
   
    
    
    //finchè fine è uguale a zero il gioco non è finito quindi cicla
    while(!fine){
        
        mvwprintw(new_win,7,1,"Quale numero vuoi spostare?: ");
        
        //crea un box
        box(new_win,0,0);
        
        //wgetch cattura il carattere ascii e restituisce il suo valore intero
        // -48 per ricavare i numeri dall' 1 al 9
        mossa = wgetch(new_win) - 48; 

        if(valida(table,mossa)){
            
            wclear(new_win); //pulisce la finestra
            muovi(table,mossa);
            wprintw(new_win,"\n\n\n");
            stampa(table,DIM,new_win);
            wrefresh(new_win);
            
            //controlla se il gioco è finito
            fine = risolto2(table,DIM);
        }
        else{
            
            //wclear(new_win);
            mvwprintw(new_win, 1, 1,"La mossa inserita non è valida\n\n");
            
            stampa(table,3,new_win);
            wrefresh(new_win); // non ho capito bene a che serve refresh
        }

        
        
    }
    box(new_win,0,0);
    mvwprintw(new_win,7,1," Complimenti Hai completato il gioco");
    wgetch(new_win);
    endwin();
return 0;
}

//provaprova