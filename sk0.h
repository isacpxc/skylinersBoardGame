#ifndef SK0_H_INCLUDED
#define SK0_H_INCLUDED

typedef struct elemento* Pilha;
typedef struct elemento Elemento;
typedef struct elem_jog* ListaJ;
typedef struct elem_jog Elem_jog;

int create_matriz_visao(ListaJ*,Pilha*);
Pilha* criar_tab();
Pilha* criar_tab_central();
char* posicaoMaker(int,int);
int criar_e_montar_central(Pilha*,int,Elemento*);
int criar_casas(Pilha*,char*,int,Pilha*);
int acessa_altura(Pilha*,int,int);
int acessa_trava(Pilha*,int,int);
int random_tabuleiro_central(int,Pilha*);
Elem_jog* criar_Lista_jogadores();
int insere_jogador(ListaJ*);
int cria_jogador(ListaJ*,int);
int acessa_pecas(int,int,ListaJ*);
int verify_position(char[],Pilha*);
int verify_peca(int,ListaJ*,int);
int verify_jogada_total(int,int,ListaJ*,Pilha*,char[]);
int conta_fim(ListaJ*);
int minha_visao(ListaJ*,int,int);
int winner(ListaJ*);
int clean_tabuleiro(Pilha*,Pilha*);
int clean_jogadores(ListaJ*);
char* check_name(int,ListaJ*);
#endif // SK0_H_INCLUDED


