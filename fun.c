#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <ncurses.h>
#define DIM 3



int poscolzero = -1; //colonna dello zero
int posrigazero = -1; //riga dello zero
int colmossa, rigamossa; //posizione della mossa

struct pos_t{

    int r;
    int c;

};


void muovi(int **gioco, int mossa){
        
        gioco[posrigazero][poscolzero] = mossa;
        gioco[rigamossa][colmossa] = 0;
        poscolzero = colmossa;
        posrigazero = rigamossa;

}

//stampa la tabella nella finestra new_win
void stampa(int **gioco, int size, WINDOW * new_win){

    for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(gioco[i][j] == 0 )
                    wprintw(new_win,"%2c ", ' ');
                else    
                    wprintw(new_win,"%2i ", gioco[i][j]);

                
            }
        wprintw(new_win,"\n");

    }
    //wrefresh(new_win);
}


int valida(int **gioco, int mossa){
    
    int libero = 1;
    
    //se posrigazero e poscolzero hanno valore -1 è la prima volta che lanciamo la funzione quindi ricerchiamo la posizione dello zero
    //altrimenti la posizione è gia stata trovata e non serve ricercarla
    if(posrigazero == -1 && poscolzero == -1){
        for(int i = 0; i < DIM && libero == 1; i++){
            for(int j = 0; j < DIM && libero == 1; j++){
            
                if(gioco[i][j] == 0){
                    posrigazero = i;
                    poscolzero = j;
                    libero = 0;
                }
            }
        }
    }
    
    
    libero = 1;
    //cerchiamo la posizione della mossa;
    for(int i = 0; i < DIM && libero == 1; i++)
        for(int j = 0; j < DIM && libero == 1; j++){
            
            if(gioco[i][j] == mossa ){
                rigamossa = i;
                colmossa = j;
                libero = 0;
            }
        }
    
    if(rigamossa == posrigazero && (colmossa == poscolzero - 1 || colmossa == poscolzero + 1))
        return 1;
    else if((rigamossa == posrigazero - 1 || rigamossa == posrigazero + 1) && colmossa == poscolzero)
        return 1;
    else 
        return 0;
}


int risolto2(int **gioco, int size){

    int *pgioco = *gioco;
 
    int check = 1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(gioco[i][j] != check)
                return 0;

                check++;
                if(check == size * size)
                    check = 0;
            
        }
    }

    return 1;




}

int ** random_game3(int size){


    const int possibilità = 9;

    int checknum[] = {1,1,1,1,1,1,1,1,1}; //array di supporto
    int casualnum;
    int flag = 0;
    
    //genero dinamicamente un'array bidimensionale
    int **gioco = (int **)malloc(sizeof(int*) * size);
    checkmalloc(gioco);
    for(int i = 0; i < size; i++){
        gioco[i] = (int*)malloc(sizeof(int) * size); 
        //checkmalloc(gioco[i]);
    }
    
    //inizializzo l'array alla posizione base
    int k = 1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            gioco[i][j] = k;
            k++; 
        }
    }

    gioco[2][2] = 0;


    swap(gioco, size);



    return gioco;
    
}



void swap(int **gioco, int size){

    srand(time(NULL));


    int *support = malloc(sizeof(int) * (size * size));  //array di supporto
    
    struct pos_t first_casual_num, second_casual_num; //posizione dei numeri causali che andrò a generare
    int tmp;

    //caso in cui la tabella sia diaspari
    if(size % 2 != 0){

        //i scelto arbitrariamente
        for(int i = 0; i < 5; i++){
            
            //il ciclo serve per eliminare i casi in cui si swappa un numero con se stesso
            do{
                first_casual_num.c = rand() % size;
                first_casual_num.r = rand() % size;

                second_casual_num.c = rand() % size;
                second_casual_num.r = rand() % size;
            }while(first_casual_num.c == second_casual_num.c && first_casual_num.r  == second_casual_num.r);
            

            //swap 
            tmp = gioco[second_casual_num.r][second_casual_num.c];
            gioco[second_casual_num.r][second_casual_num.c] = gioco[first_casual_num.r][first_casual_num.c];
            gioco[first_casual_num.r][first_casual_num.c] = tmp;
        }

    }

    int count = 0;
    int k = 0;

    //salvo la matrice in un array a 1D
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            support[k] = gioco[i][j];
            //wprintw("%i", support[k]);
            k++;
        }
    }

    

    int control1,control2;

    //controllo la parità della permutazione e salvo il valore in count
    for(int i = 0; i < size * size; i++){
        control1 = support[i];
        for(int j = i + 1; j < size*size; j++){
            control2 = support[j];
            if(control1 > control2 && control2 != 0 && control1 != 0)
                count++;
        }
    }

    //wprintw("numero permutazioni :%i\n", count);

    free(support);
    //se il numero non è pari allora il gioco non è risolvibile, rilancio la funzione
    if(count % 2 != 0 || count == 0)
        swap(gioco,size);
}

void checkmalloc(int **gioco){

    if(gioco != NULL)
        return;
    else{    
        
        printw("memoria non allocata");
        refresh();
        getch();
        return exit(1);
        
    }
}