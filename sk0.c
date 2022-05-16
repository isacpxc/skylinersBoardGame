#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "sk0.h"

//ctrl shift c || x
//TIPOS DE TRAVAS
//-1 travado (não pode acrescentar nenhuma peça)
//0 pode andar,parque
//1 apenas teto e andar podem ser colocados em cima

int cont=0;

struct jogador{
    char nome[6];
    int posicao;
    int pecas[3];
    int TotP;
    int matriz_visao[5][5];
    int victory;
};

struct elem_jog{
    struct jogador Dados;
    struct elem_jog *prox;
};

struct dados{
    char position0[3];
    char position1[3];
    int posicao_linear;
    int altura;
    int trava;
};

struct elemento {
    struct dados Dados;
    struct elemento *prox;
};
//MATRIZ DE ALTURAS DA VISTA DE CADA JOGADOR, AINDA NÃO É O DESENHO DA SUA VISTA
int create_matriz_visao(ListaJ* jogadores,Pilha* tabuleiro){
    Elem_jog* aux_j = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux_j == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_j = *jogadores;
    Elemento* aux_t = (Elemento*)malloc(sizeof(Elemento));
    if (aux_t == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_t = *tabuleiro;
    //É UM ERRO E NÃO É, AQUI ESTÁ SENDO CRIADA A MATRIZ INVERTIDA
    Elem_jog* anterior=(Elem_jog*)malloc(sizeof(Elem_jog));
    if (anterior == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}

    for (int i=0,j=0,cont=0;cont<25;cont++,j++){
        aux_j->Dados.matriz_visao[i][j] = aux_t->Dados.altura;
        aux_t = aux_t->prox;
        if (j == 4){
            i++;
            j=-1;
        }
    }

    for (int i=0;i<5;i++){
        for (int j=0;j<3;j++){
            int aux=aux_j->Dados.matriz_visao[i][j];
            aux_j->Dados.matriz_visao[i][j]=aux_j->Dados.matriz_visao[i][4-j];
            aux_j->Dados.matriz_visao[i][4-j]=aux;
        }
    }

    for (int c=0;c<5;c++){
        for (int l=0;l<3;l++){
            int aux=aux_j->Dados.matriz_visao[l][c];
            aux_j->Dados.matriz_visao[l][c]=aux_j->Dados.matriz_visao[4-l][c];
            aux_j->Dados.matriz_visao[4-l][c]=aux;
        }
    }


    for (int x=0;x<3;x++){
        anterior=aux_j;
        aux_j=aux_j->prox;

        for (int i=0,l=4;i<5;i++,l--){
            for (int j=0;j<5;j++){
                aux_j->Dados.matriz_visao[i][j] = anterior->Dados.matriz_visao[j][l];
            }
        }
    }


}





Pilha* criar_tab() {
    Pilha *tabuleiro;
    tabuleiro = (Pilha*)malloc(sizeof(Pilha));
    if (tabuleiro == NULL) {
        printf("ERRO DE ALOCAÇÃO!!!");
        return 0;
    }
    return tabuleiro;

}

Pilha* criar_tab_central() {
    Pilha *tabuleiro;
    tabuleiro = (Pilha*)malloc(sizeof(Pilha)*8);
    if (tabuleiro == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    if (tabuleiro == NULL) {
        printf("ERRO DE ALOCAÇÃO!!!");
        return 0;
    }
    return tabuleiro;

}
//CRIA NOME DOS ELEMENTOS DA PILHA DO TANULEIRO
char* posicaoMaker(int letra,int num){
    char l = letra;
    char n = num+48;
    char *junto;
    junto = (char*)malloc(sizeof(char)*3);
    if (junto == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    junto[0] = l;
    junto[1] = n;
    junto[2] = '\0';

    return junto;
}

//TABULEIRO DE POSIÇÕES ALEATÓRIAS
int criar_e_montar_central(Pilha*tabuleiro_c,int x,Elemento*novo){
    tabuleiro_c[cont] = novo;
    cont++;
}


int criar_casas(Pilha* tabuleiro,char *local, int num,Pilha* tabuleiro_central){
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    if (novo == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    novo->Dados.altura=0;
    novo->Dados.posicao_linear=num;
    char c = local[0];
    char n = local[1]-48;
    strcpy(novo->Dados.position0,local);
    strcpy(novo->Dados.position1,posicaoMaker(c+32,n));
    if (strcmp(local,"C3")==0 ) {
        novo->Dados.trava=-1;
        novo->Dados.altura=1;
    } else novo->Dados.trava=0;
    int teste;
    if (strcmp(local,"C3")==0) teste=1;
    if (c>65 && c<69 && n>1 && n<5 && teste!=1) {
        criar_e_montar_central(tabuleiro_central,cont,novo);
    }
    novo->prox = *tabuleiro;
    *tabuleiro = novo;

}
//PARA DESENHO
int acessa_altura(Pilha* tabuleiro, int i,int pos){
    Elemento *guarda,*aux;
    guarda = (Elemento*)malloc(sizeof(Elemento));
    if (guarda == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    guarda = *tabuleiro;
    aux = (Elemento*)malloc(sizeof(Elemento));
    if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux = guarda->prox;
    i-=5;
    for (int x=i;x<24-pos;x++){
        guarda = aux;
        aux = guarda->prox;

    }

    return guarda->Dados.altura;
}

//PARA DESENHO DE PARÊNTESES
int acessa_trava(Pilha* tabuleiro, int i,int pos){
    Elemento *guarda,*aux;
    guarda = (Elemento*)malloc(sizeof(Elemento));
    if (guarda == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    guarda = *tabuleiro;
    aux = (Elemento*)malloc(sizeof(Elemento));
    if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux = guarda->prox;
    i-=5;
    for (int x=i;x<24-pos;x++){
        guarda = aux;
        aux = guarda->prox;

    }
    return guarda->Dados.trava;
}

//PEÇAS ALEATÓRIAS
int random_tabuleiro_central(int x,Pilha *tabuleiro_c){
    tabuleiro_c[x]->Dados.altura++;
    tabuleiro_c[x]->Dados.trava=1;
}

Elem_jog* criar_Lista_jogadores(){
    ListaJ* jog = (ListaJ*)malloc(sizeof(ListaJ));
    if (jog == NULL) {
        printf("ERRO DE ALOCAÇÃO!!!");
        return 0;
    }
    *jog = NULL;
    return jog;
}

int insere_jogador(ListaJ* jog){
    Elem_jog *novo = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (novo == NULL) {
        printf("ERRO DE ALOCAÇÃO!!!");
        return 0;
    }
    if (*jog==NULL){
        novo->prox = NULL;
        *jog = novo;
    }
    else {
        Elem_jog* aux = (Elem_jog*)malloc(sizeof(Elem_jog));
        if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
        aux = *jog;
        //if == NULL
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->prox = NULL;
    }
    //if == NULL
}

int cria_jogador(ListaJ* jogadores,int e){
    Elem_jog* aux = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux = *jogadores;
    char jogador[5];
    if (e==0) strcpy(jogador,"Sul");
    if (e==1) strcpy(jogador,"Oeste");
    if (e==2) strcpy(jogador,"Norte");
    if (e==3) strcpy(jogador,"Leste");
    struct jogador novo;
    strcpy(novo.nome,jogador);
    novo.posicao = e;
    novo.TotP = 15;
    novo.pecas[0] = 12;
    novo.pecas[1] = 2;
    novo.pecas[2] = 1;
    for (int i=0;i<e;i++){
        aux = aux->prox;
    }
    aux->Dados = novo;

}

//TOTAL DE PEÇAS DAQUELE TIPO
int acessa_pecas(int num,int e,ListaJ* jog){
    Elem_jog* aux = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux = *jog;
    for (int i=0;i<e;i++){
        aux = aux->prox;
    }
    if (num==0){
        return aux->Dados.pecas[num];
    }else if (num==1){
        return aux->Dados.pecas[num];
    }else if (num==2){
        return aux->Dados.pecas[num];
    }
}


//NOME DO JOGADOR
char* check_name(int e,ListaJ* jog){
    Elem_jog* aux = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux = *jog;
    for (int i=0;i<e;i++){
        aux = aux->prox;
    }
    return aux->Dados.nome;
}

//VERIFICA SE POSIÇÃO SELECIONADA EXISTE
int verify_position(char position[],Pilha* tabuleiro){
    if (strlen(position) != 2) return 0;
    Elemento *aux = (Elemento*)malloc(sizeof(Elemento));
    if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux = *tabuleiro;
    for (int i=0;i<25;i++){
        if (strcmp(aux->Dados.position0,position)==0 || strcmp(aux->Dados.position1,position)==0) return 1;
        aux = aux->prox;
    }
    return 0;

}
//VERIFICA SE PEÇA SELECIONADA EXISTE
int verify_peca(int peca,ListaJ* jog,int jog_count){
    Elem_jog* aux_j = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux_j == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_j = *jog;
    for (int i=0;i<jog_count;i++){
        aux_j = aux_j->prox;
    }
    if (peca==2) peca=3;
    else if (peca==3) peca=2;
    if (aux_j->Dados.pecas[peca-1] == 0){
        return 0;
    } else {
        return 1;
    }
}
//PEÇA VÁLIDA E LOCAL VÁLIDO, VERIFICA SE ESTÁ DISPONÍVEL
int verify_jogada_total(int peca,int jog_count,ListaJ* jog,Pilha* tabuleiro,char posicao_name[]){
    Elem_jog* aux_j = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux_j == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_j = *jog;
    Elemento* aux_t = (Elemento*)malloc(sizeof(Elemento));
    if (aux_t == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_t = *tabuleiro;
    for (int i=0;i<jog_count;i++){
        aux_j = aux_j->prox;
    }
    while ( strcmp(posicao_name,aux_t->Dados.position1) != 0 && strcmp(posicao_name,aux_t->Dados.position0) != 0 ){
        aux_t = aux_t->prox;
    }



    if (aux_t->Dados.trava == -1) {
        printf("Esse lugar está travado, refaça sua jogada!\n\n");
        return 0;
    } else if (aux_t->Dados.trava == 0){
        if (peca==1){
            aux_j->Dados.pecas[peca-1]--;
            aux_t->Dados.trava = 1;
        }else if (peca==2){
            aux_j->Dados.pecas[peca]--;
            aux_t->Dados.trava = -1;
        }else if (peca==3){
            printf("Tetos não podem ser Colocados no Chão, refaça sua jogada!\n\n");
            return 0;
        }
        aux_t->Dados.altura++;
        aux_j->Dados.TotP--;
        return 1;

    } else if (aux_t->Dados.trava == 1){
        if (peca == 1 || peca == 3){
            if (peca==1){
                aux_j->Dados.pecas[peca-1]--;
                aux_t->Dados.trava = 1;
                aux_t->Dados.altura++;
                aux_j->Dados.TotP--;
            }else if (peca==3){
                aux_j->Dados.pecas[peca-2]--;
                aux_t->Dados.trava = -1;
                aux_t->Dados.altura++;
                aux_j->Dados.TotP--;
            }
            return 1;
        } else {
            printf("Parques não Podem ser Colocados em Cima de Andares! Tente novamente!\n\n");
            return 0;
        }
    }
}

//COMEÇA A CONTAR QUANDO ACABA PEÇAS DO JOGADOR SUL
int conta_fim(ListaJ* jogadores){
    Elem_jog* aux_j = (Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux_j == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_j = *jogadores;

    if (aux_j->Dados.TotP == 0) return 1;
    return 0;
}



int minha_visao(ListaJ* jogadores, int jog_count,int cond){
    Elem_jog* aux_j=(Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux_j == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_j = *jogadores;
    int tam[5] = {0,0,0,0,0};

    for (int i=0;i<jog_count;i++){
        aux_j = aux_j->prox;
    }

    //MAX
    for (int i=0;i<5;i++) {
        for (int j=4;j>-1;j--){
            if (tam[i] < aux_j->Dados.matriz_visao[j][i]){
                tam[i] = aux_j->Dados.matriz_visao[j][i];
            }
        }
    }
    //FIM MAX

    //int aux_i,aux_f;
    int max=tam[0];
    for (int i=0;i<5;i++) if (max<tam[i]) max=tam[i];
    int matriz_desenho[max][5];
    for(int i=0;i<max;i++){
        for (int j=0;j<5;j++){
            matriz_desenho[i][j]=0;
        }
    }

    int c2[max];
    for (int i=0;i<max;i++) c2[i]=0;
    int pos_f=0,pos_i=0;
    int cc=0,seg=0,total_cc=0;
    /////////////////loop MATRIZ DESENHO
//FOR DEBUG
//    for (int i =0;i<5;i++){
//        for (int j=0;j<5;j++){
//            printf("%i ",aux_j->Dados.matriz_visao[i][j]);
//        }
//        printf("\n");
//    }
    for (int s=0;s<5;s++){




        for (int i=0;i<5;i++){
            if (aux_j->Dados.matriz_visao[4-i][s]==tam[s]){

                pos_f=4-i; //posição onde estava a maior altura na matriz_visao, do 3 ao 0
                break;
            }
        }

        for (int j=0;j<5;j++){
            if (aux_j->Dados.matriz_visao[4-j][s]>0){
                pos_i=4-j;//posição onde estava primeiro número na matriz_visão, do 3 ao 0

                break;
            }
        }
        //CONTADOR PARA SABER QUANTOS SERÃO IMPRESSOS, PARA DEPOIS CRIAR UM ARRAY EXATAMENTE CONTENDO CADA POSIÇÃO DE IMPRESSÃO
        cc=0;
        seg=pos_i;
        for (int i=pos_i;i>=pos_f;i--){
              if (i==pos_f) cc++;
              if (aux_j->Dados.matriz_visao[seg][s]>aux_j->Dados.matriz_visao[pos_i][s]){
                    cc++;
              }
              seg--;

        }


        total_cc+=cc;
        seg=pos_i;
        int posicoes_impressas[cc],vezes_appear[cc];
        for (int i=0;i<cc;i++) posicoes_impressas[i]=0;
        posicoes_impressas[0]=pos_f;
        posicoes_impressas[cc-1]=pos_i;

        for (int i=pos_i,k=cc-2;i>pos_f;i--){
            if (aux_j->Dados.matriz_visao[i][s]>aux_j->Dados.matriz_visao[seg][s]){
                posicoes_impressas[k]=i;
                k--;
                seg--;
            }
        }


        //CC CONTÉM POSIÇÕES QUE SERÃO IMPRESSAS, PRÓXIM0 PASSO É VER QUAL A ALTURA E DIMINUIR PELO PRÓXIMO PARA SABER QUANTAS VEZES SEUS # APARECEM


        for (int i=0;i<cc-1;i++){
            vezes_appear[i] = aux_j->Dados.matriz_visao[posicoes_impressas[i]][s]-aux_j->Dados.matriz_visao[posicoes_impressas[i+1]][s];

        }

        vezes_appear[cc-1]=aux_j->Dados.matriz_visao[posicoes_impressas[cc-1]][s];
        //AGORA EU TENHOS DUAS MATRIZES, A DAS POSIÇÕES DAS QUE SERÃO IMPRESSAS, E DE QUANTAS VEZES CADA UMA VAI IMPRIMIR



        //PASSA COLUNAS DE IMPRIMIDOS PARA MATRIZ_DESENHO
        int z=max;
        for (int i=cc-1;i>-1;i--){
            for (int j=0;j<vezes_appear[i];j++){
                z--;
                matriz_desenho[z][s]=posicoes_impressas[i]+1;
            }
        }

    }//FIM
    if (cond==1){//SE FOR USADO DIGITANDO "0" PELO JOGADOR ENTRA AQUI, SE NÃO O JOGO CHEGOU AO FIM, E MOSTRA VENCEDOR
          printf("\n\nVisão do Jogador %s: \n\n",aux_j->Dados.nome);

            printf("\n");
    //FOR DEBUG
    //    for (int i=0;i<max;i++){
    //        for (int j=0;j<5;j++){
    //            printf("%i ",matriz_desenho[i][j]);
    //        }
    //        printf("\n");
    //    }
    int x=0;
    //DESENHO DA VISÃO
    for (int i=0;i<max;i++){
        for (int j=0;j<5;j++){
            for (x=0;x<matriz_desenho[i][j];x++){
                printf("#");
            }


            if (x==0) printf("      ");
            if (x==1) printf("     ");
            if (x==2) printf("    ");
            if (x==3) printf("   ");
            if (x==4) printf("  ");
            if (x==5) printf(" ");

        }
        printf("\n");
    }
    printf("------------------------------\n\n");
    system("pause");
    } else {
        //FORMA INT VICTORY DE CADA JOGADOR
        aux_j->Dados.victory=0;
        for (int i=0;i<total_cc;i++){
            aux_j->Dados.victory++;
        }
    }


}
//VERIFICA PONTUAÇÃO
int winner(ListaJ* jogadores){
    Elem_jog* aux_j=(Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux_j == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux_j=*jogadores;

    int all_vic[4],higher,empate=-1;
    for (int i=0;i<4;i++) {
        all_vic[i] = aux_j->Dados.victory;
        aux_j = aux_j->prox;
    }
    higher=all_vic[0];
    for (int i=0;i<4;i++){
        if (higher<all_vic[i]) higher = all_vic[i];

    }

    aux_j=*jogadores;
    //VERIFICAÇÃO DE EMPATE
    for (int i=0;i<4;i++){
        if (higher==all_vic[i]){
            empate++;
            if (empate>0) break;
        }
    }
    //VERIFICAÇÃO DE EMPATE
    if (empate==0){
        int hold_w=0;
        printf("*Vencedor:\n");
        for (int i=0;i<4;i++){
            if (aux_j->Dados.victory==higher){
                printf("-Jogador %s!!!\n*Pontuação: %i\n\n",aux_j->Dados.nome,aux_j->Dados.victory);
                break;
            }
            aux_j=aux_j->prox;
        hold_w++;
        }
        minha_visao(jogadores,hold_w,1);
    } else {
        printf("*Empate:\n");
        for (int i=0;i<4;i++){
            if (aux_j->Dados.victory==higher){
                printf("-Jogador %s!!!\nPontuação: %i\n\n",aux_j->Dados.nome,aux_j->Dados.victory);
            }
            aux_j=aux_j->prox;
        }
        minha_visao(jogadores,0,1);
        printf("\n");

    }
}

int clean_tabuleiro(Pilha* tabuleiro,Pilha* tabuleiro_c){
    Elemento* aux_a = (Elemento*)malloc(sizeof(Elemento));
    if (aux_a == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    Elemento* aux_p = (Elemento*)malloc(sizeof(Elemento));
    if (aux_p == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}

    aux_a=*tabuleiro;
    for (int i=0;i<25;i++){
        aux_p=aux_a->prox;
        free(aux_a);
        aux_a=aux_p;
    }

    free(tabuleiro);

    free(tabuleiro_c);
    return 0;

}

int clean_jogadores(ListaJ* jogadores){
    Elem_jog* aux=(Elem_jog*)malloc(sizeof(Elem_jog));
    if (aux == NULL) {printf("ERRO DE ALOCAÇÃO!!!"); return 0;}
    aux=*jogadores;

    while (aux!=NULL){
        *jogadores=aux->prox;
        free(aux);
        aux=*jogadores;
    }

    free(jogadores);

    return 0;
}






