#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
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

    int x,y; //position of numbers
    int maxcol; //number of space we need to print numbers and space(one space for one number)
    int i = 0, j = 0; //counter for array
    
    //start BOLD
    wattron(new_win,A_BOLD);
    y = 3; //I want it start to print of the third row
    while(y != size + 3){
            x = 25 - ((size * 2) - 1); 
            maxcol = ((size * 2) - 1) + x;
            while(x != maxcol){
                //if we're in a even position print a value of table 
                if(x % 2 == 0){
                    if(gioco[i][j] != 0)
                        mvwprintw(new_win,y,x,"%i",gioco[i][j]);
                    else    
                        mvwprintw(new_win,y,x,"%c",' ');
                }//else print a space
                else{    
                    mvwprintw(new_win,y,x,"%c",' ');
                    j++;
                }
                wrefresh(new_win);
                x++;
            }
            j = 0;
        
        i++;
        y++;
    }
    wrefresh(new_win);
    //stop BOLD
    wattroff(new_win,A_BOLD);
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

    //initialize finish to zero
    gioco[2][2] = 0;

    //shake the table
    swap(gioco, size);

    return gioco;
    
}

void swap(int **gioco, int size){

    srand(time(NULL));

    int *support = malloc(sizeof(int) * (size * size));
    int count;
    struct pos_t first_casual_num, second_casual_num; //numeri causali che andrò a generare
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

void print_score(WINDOW *new_win,int count){
    
    nocbreak(); //enable line buffering,
    echo(); //return char on the screen with wgetch()
    
    const int tot_space = 15;
    
    char player[10];
    char *filename = "score.txt";
    FILE *fp;

    fp = fopen(filename,"a");
    
    wprintw(new_win,"Inserisci nome giocatore:");
    wgetnstr(new_win,player,9);
    int num_space = tot_space - strlen(player);
    fprintf(fp,"%s",player);
    
    for(int i = 0; i < num_space; i++){
        fprintf(fp," ");
    }
    
    fprintf(fp,"mosse:%i\n",count);

    fclose(fp);


}