#include <stdio.h>
#include "fun.h"
#include "fun.c"
#define DIM 4

int main (void){
    int c;
    int mossa;
    int table[DIM][DIM] = {{1,2,3,4}, {5,6,7,8},{9,10,11,12}, {13,14,15,0}};
    int fine;

    printf("*******BENVENUTO NEL GIOCO DEL 15*********\n\n\n");
    fine = risolto2(table);
    stampa(table);
    
    while(!fine){
        printf("\nQuale numero vuoi spostare?: ");
        scanf("%i", &mossa);

        if(valida(table,mossa)){
            muovi(table,mossa);
            printf("\n");
            stampa(table);
            fine = risolto2(table);
        }
        else{
            printf("La mossa inserita non è valida, riprova\n");
        }

        
        
    }
    printf("Complimenti Hai completato il gioco");


return 0;
}

//provaprova