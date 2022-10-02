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
        
        
        convertimossa(gioco,mossa);
        
        gioco[posrigazero][poscolzero] = gioco[rigamossa][colmossa];
        gioco[rigamossa][colmossa] = 0;
        poscolzero = colmossa;
        posrigazero = rigamossa;

}


int convertimossa(int **gioco, int mossa){

    switch(mossa){

        case KEY_UP:
            rigamossa = posrigazero + 1;
            colmossa = poscolzero;
            break;
        case KEY_DOWN:
            rigamossa = posrigazero - 1;
            colmossa = poscolzero;
                break;
        case KEY_RIGHT:
            rigamossa = posrigazero;
            colmossa = poscolzero - 1;
                break;
        case KEY_LEFT:
            rigamossa = posrigazero;
            colmossa = poscolzero + 1;
                break;
        default:
            break;
    
    }

    return mossa;

}

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

void search_zero(int **gioco,int size){

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


}

int valida(int **gioco, int mossa,int size){
    
    switch(mossa){

        case KEY_UP:
            if(posrigazero < DIM - 1)
                return 1;
                break;
        case KEY_DOWN:
            if(posrigazero > 0)
                return 1;
                break;
        case KEY_RIGHT:
            if(poscolzero > 0)
                return 1;
                break;
        case KEY_LEFT:
            if(poscolzero < DIM - 1)
                return 1;
                break;
        default:
            break;
    
    }

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

    //genero dinamicamente un'array bidimensionale
    int **gioco = (int **)malloc(sizeof(int*) * size);
    checkmalloc(gioco);
    
    for(int i = 0; i < size; i++){
        gioco[i] = (int*)malloc(sizeof(int) * size); 
        if(gioco[i]==NULL){
            printf("memoria non allocata");
            exit(1);
        }
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


    int *support = malloc(sizeof(int) * (size * size));
    int count;
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

    
    int k = 0;
    //salvo la matrice in un array a 1D
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            support[k] = gioco[i][j];
            //wprintw("%i", support[k]);
            k++;
        }
    }

    

    count = n_permutazione(gioco,support, size);

    while(count % 2 == 1){

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

            k = 0;
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    support[k] = gioco[i][j];
                    //wprintw("%i", support[k]);
                    k++;
                }
            }



            count = n_permutazione(gioco,support, size);
    }
    
    //controllo che sia valida la scheda
    printf("numero permutazione: %i", count);
    getchar();
    //wprintw("numero permutazioni :%i\n", count);
    free(support);
    
}

void checkmalloc(int **gioco){

    if(gioco != NULL)
        return;
    else{    
        
        printf("memoria non allocata");
        return exit(1);
        
    }
}

int n_permutazione(int **gioco, int *support, int size){

    
    int control1,control2;
    int count = 0;
    //controllo la parità della permutazione e salvo il valore in count
    for(int i = 0; i < size * size; i++){
        control1 = support[i];
        for(int j = i + 1; j < size*size; j++){
            control2 = support[j];
            if(control1 > control2 && control2 != 0 && control1 != 0)
                count++;
        }
    }
    return count;
}