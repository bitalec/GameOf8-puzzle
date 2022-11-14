#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "fun.h"
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
    
    
    wclear(new_win);
    nocbreak(); //enable line buffering,
    echo(); //return char on the screen with wgetch()
    struct player_t *newplayer = malloc(sizeof(struct player_t));
    struct player_t *allplayer = NULL;
    char name[10];
    int point = count;
    FILE *fp = fopen("Score.txt", "a+");
    
    wprintw(new_win,"%s","INSERISCI NOME GIOCATORE:");
    wscanw(new_win,"%9s", newplayer->name); //nome del giocatore
    newplayer->point = count;   //punteggio del giocatore
    newplayer ->nextplayer = NULL;
    
    //new list with points and names of player
    allplayer = new_list(fp,allplayer,newplayer);

    if(allplayer != newplayer)
        allplayer = insert_player(allplayer,newplayer);

    fclose(fp);

    fp = fopen("Score.txt","w");
    
    while(allplayer != NULL){
        
        fprintf(fp,"%s   mosse:%i\n", allplayer->name, allplayer -> point);
        wprintw(new_win,"%s   mosse:%i\n", allplayer -> name, allplayer -> point);
        
        allplayer = allplayer -> nextplayer;
    
    }
  /*  while(allplayer != NULL){
        wprintw(new_win,"%s", allplayer -> name);
        allplayer = allplayer -> nextplayer;
    }*/
    fclose(fp);
    wgetch(new_win);

};

struct player_t *new_list(FILE *fp,struct player_t *allplayer,struct player_t *newplayer){


    
    char fs_s[30];
    char name[10];
    struct player_t *node;
    //Se il file è vuoto ritorna l'unico giocatore;
    if(fgets(fs_s,28,fp) == NULL){
       return newplayer;
    }
    else{
        int i;
        int n;
        int points = 0;
        
        struct player_t *cursor = allplayer; //cursore della lista
        
        do{
            node = malloc(sizeof(struct player_t)); //inizializzo un nuovo nodo
            node -> nextplayer = NULL;
            n = 1;
            
            //prendo il nome dell'utente, si ferma al primo spazio
            for(i=0; *(fs_s + i) != ' '; i++)
                node -> name[i] = *(fs_s+i); 
            
            //salto tutti i caratteri fino ad arrivare al punteggio
            while(*(fs_s + i) < '0' || *(fs_s + i) > '9')
                i++;

            //inizializzo il punteggio
            //numero in base 10, n mi indica la posizione della cifra che andrò a salvare
            while(*(fs_s + i) != '\n'){
                if(*(fs_s + i) != '0')
                    node -> point += (*(fs_s + i) - '0') * n;
                else
                    node -> point *= 10;
                
                n *= 10;
                i++;
            }    
            
            //se la lista è vuota salvo la lista punta al primo e unico giocatore
            if(allplayer == NULL){
                allplayer = node;
            }
            else{
                cursor = allplayer;
                //altrimenti vado alla fine della lista e salvo l'ultimo giocatore
                while(cursor -> nextplayer != NULL){
                    cursor = cursor -> nextplayer;
                }
                cursor -> nextplayer = node;
            }


        }while(fgets(fs_s,28,fp) != NULL); //continua fino a che ci sono giocatori

        
    }
        
        return allplayer;


};

struct player_t *insert_player(struct player_t *allplayer,struct player_t *newplayer){

    bool flag = 0;
    struct player_t *copy = allplayer;
    struct player_t *prec;
    
        if(newplayer-> point < allplayer -> point){
            
            newplayer -> nextplayer = allplayer;
            allplayer = newplayer;
            
            return allplayer;
        
        }
        else{
            
            while(!flag){
                
                flag = (allplayer == NULL) ? 1 : 0;
                
                if(!flag)
                    if(newplayer -> point > allplayer -> point){
                    
                        prec = allplayer;
                        allplayer = allplayer -> nextplayer;
                    
                    }else flag = 1;
            }

            prec -> nextplayer = newplayer;
            newplayer -> nextplayer = allplayer;

            return copy;
        }
            
        
}

//test
/*int ** test_game(void){

    int size = 3;

    int **gioco = (int **)malloc(sizeof(int*) * size);
    checkmalloc(gioco);
    
    for(int i = 0; i < size; i++){
        gioco[i] = (int*)malloc(sizeof(int) * size); 
        if(gioco[i]==NULL){
            printf("memoria non allocata");
            exit(1);
        }
    }

    int k = 1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            gioco[i][j] = k;
            k++; 
        }
    }

    gioco[2][2] = 0;

    return gioco;


}*/