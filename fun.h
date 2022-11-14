#ifndef FUN_H
#define FUN_H


struct player_t{

    char name[10];
    int point;
    struct player_t *nextplayer;
};





void muovi(int **gioco, int mossa);
void stampa(int **gioco, int size, WINDOW * new_win);
int valida(int **gioco, int mossa, int size);
void swap(int **gioco, int size);
void checkmalloc(int **gioco);
void search_zero(int **gioco,int size);
int convertimossa(int **gioco, int mossa);
int n_permutazione(int **gioco, int *support,int size);
void print_score(WINDOW *new_win,int count);
int ** random_game3(int size);
int risolto2(int **gioco, int size);
struct player_t *new_list(struct player_t *all_player, struct player_t *player);
struct player_t *insert_player(struct player_t *allplayer,struct player_t *newplayer);

int ** test_game(void);


#endif                          