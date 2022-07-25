#include <stdio.h>
#define DIM 4

void muovi(int gioco[DIM][DIM], int mossa){
        
        int temp;
        int posriga, poscol;
        int rigavuota, colonnavuota;
        int rmossa, cmossa;
        int libero = 1;
        for(posriga = 0; posriga < DIM && libero == 1; posriga++)
            for(poscol = 0; poscol < DIM && libero == 1; poscol++){
                if(gioco[posriga][poscol] == mossa){
                    rmossa = posriga;
                    cmossa = poscol;
                    libero = 0;
                }
            }
        
        libero = 1;
        //trova posizione 0
        for(int i = 0; i < DIM && libero == 1; i++)
            for(int j = 0; j < DIM && libero == 1; j++){
            
                if(gioco[i][j] == 0){
                    rigavuota = i;
                    colonnavuota = j;
                    libero = 0;
                }
            }

        gioco[rigavuota][colonnavuota] = mossa;
        gioco[rmossa][cmossa] = 0;
}

void stampa(int gioco[DIM][DIM]){

    for(int i = 0; i < DIM; i++){
            for(int j = 0; j < DIM; j++){
                if(gioco[i][j] == 0 )
                    printf("%2c ", ' ');
                else    
                    printf("%2i ", gioco[i][j]);
            }
        printf("\n");
    }
}


int valida(int gioco[DIM][DIM], int mossa){
    
    int colmossa, rigamossa;
    int posriga, poscol;
    int libero = 1;
    //troviamo la posizione della casella vuota
    for(int i = 0; i < DIM && libero == 1; i++)
        for(int j = 0; j < DIM && libero == 1; j++){
            
            if(gioco[i][j] == 0){
                posriga = i;
                poscol = j;
                libero = 0;
            }
        }

    libero = 1;
    for(int i = 0; i < DIM && libero == 1; i++)
        for(int j = 0; j < DIM && libero == 1; j++){
            
            if(gioco[i][j] == mossa ){
                rigamossa = i;
                colmossa = j;
                libero = 0;
            }
        }
    
    if(rigamossa == posriga && (colmossa == poscol - 1 || colmossa == poscol + 1))
        return 1;
    else if((rigamossa == posriga - 1 || rigamossa == posriga + 1) && colmossa == poscol)
        return 1;
    else 
        return 0;
}




int risolto(int gioco[DIM][DIM]){

    int supp[DIM * DIM];
    int control = 1;
    int z = 0;
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            supp[z++] = gioco[i][j];
            
            
        }
}
    for(int i = 0; i < (DIM * DIM) - 2 && control == 1; i++){
        if(supp[i + 1] != supp[i] + 1 )
            control = 0;
    }

    return control;
}


int risolto2(int gioco[DIM][DIM]){

    int *pgioco = *gioco;
 
    for(unsigned int i = 0; i < (DIM * DIM) - 1; i++){
        if(*(pgioco + i) != i + 1)
            return 0;
    }

    return 1;




}

//provaprova