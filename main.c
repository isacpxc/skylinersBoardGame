#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "sk0.h"

int main()
{

    int letra=65,peca,contAte5=1,jogador_count=0,position_true=0,peca_true=0,jogada_true=0,fim=0;
    Pilha *tabuleiro;
    Pilha *tabuleiro_central;
    char position[3];
    setlocale(LC_ALL,"portuguese");

    //PREPARAÇÃO
    tabuleiro = criar_tab();
    tabuleiro_central = criar_tab_central();

    for (int i=1;i<26;i++)  {
        //criação de nomes das posições, ex:A1,A2,B1,B2...
        char local_name[3];
        strcpy(local_name,posicaoMaker(letra,contAte5));
        //fim criação de nomes das posições
        criar_casas(tabuleiro,local_name,i,tabuleiro_central);
        contAte5++;
        if (i==5 ||i==10 ||i==15 ||i==20 || i == 25){
            letra++;
            contAte5=1;
        }
    }
    letra=65;
    //FIM PREPARAÇÃO

    //ALTURAS ALEATÓRIAS
    for (int i=0;i<7;i++) {
        random_tabuleiro_central(rand()%8,tabuleiro_central);
    }
    //FIM ALTURAS ALEATÓRIAS

    //CRIAÇÃO DE JOGADORES
    ListaJ* jogadores = criar_Lista_jogadores();
    for (int i=0;i<4;i++) insere_jogador(jogadores);
    for (int i=0;i<4;i++) cria_jogador(jogadores, i);
    //FIM CRIAÇÃO JOGADORES
    //******************INÍCIO DE JOGO****************************8
    do{

        //CRIAÇÃO MATRIZ_VISAO DE CADA JOGADOR
        create_matriz_visao(jogadores,tabuleiro);
        //CRIAÇÃO MATRIZ_VISAO DE CADA JOGADOR


        //DESENHO DO TABULEIRO
        do{
        system("cls");
        printf("                      Norte\n\n\n");
        for (int i=0;i<26;i++) {
            if (i==5 ||i==10 ||i==15 ||i==20 || i == 25){
                printf("+");
                printf("\n");
                if (i==15) printf("   Oeste   ");
                else printf("           ");
                for (int j=0;j<5;j++){
                    int alt=acessa_altura(tabuleiro,i,j), trava=acessa_trava(tabuleiro,i,j);
                    if (alt>9) {
                        if (trava==-1){
                            printf("|[%i]",alt);
                        } else {
                            printf("| %i ",alt);
                        }
                    }
                    else {
                        if (alt == 0) printf("|    ");
                        else {
                            if (trava==-1){
                                printf("| [%i]",alt);
                            } else {
                                printf("|  %i ",alt);
                            }
                        }
                    }
                }
                if (i==15) printf("| %c   Leste",letra);
                else printf("| %c",letra);
                letra++;
                printf("\n");
            }

            if (i!=25) {
                if (i%5==0)printf("           ");
                printf("+----");
            }
        }
        printf("           ");
        for (int i=0;i<5;i++) {
            printf("+----");
            if (i==4){
                printf("+");
            }
        }
        printf("\n");
        printf("           ");
        for (int i=0;i<5;i++) {
            printf("  %i  ",i+1);

        }
        printf("\n\n\n");
        printf("                       Sul\n\n\n");
        //FIM DESENHO TABULEIRO
        letra=65;
        //QUANTAS PEÇAS DE CADA TIPO TEM CADA JOGADOR
        int andar = acessa_pecas(0,jogador_count,jogadores);
        int teto = acessa_pecas(1,jogador_count,jogadores);
        int parque = acessa_pecas(2,jogador_count,jogadores);
        char nome_j[6];
        strcpy(nome_j,check_name(jogador_count,jogadores));
        //QUANTAS PEÇAS DE CADA TIPO TEM CADA JOGADOR

            printf("\n\n");
            //ESCOLHA PEÇA JOGADOR
            printf("Vez do Jogador com Vista do %s!\n",nome_j);
            printf("Escolha qual peça deseja jogar (1 = Andar [%i], 2 = Parque [%i], 3 = Teto [%i], 0 = Sua Vista, -1 = Finalize manualmente)\n",andar,parque,teto);
            printf("\n- > ");
            scanf("%i",&peca);
            while (getchar() != '\n');
            if (peca == -1 || peca ==0){
                if (peca ==-1){ //FINALIZA JOGO AUTOMATICAMENTE
                    jogada_true=1;
                    fim = 4;
                } else {
                    minha_visao(jogadores,jogador_count,1);  //MOSTRA VISÃO DO JOGADOR
                }

            } else {
            //VERIFICAÇÃO EXISTÊNCIA DA PEÇA
            while (peca_true == 0){
                while (peca > 3 || peca < 0){
                    printf("\n- > ");
                    scanf("%i",&peca);
                    while (getchar() != '\n');
                }
                peca_true = verify_peca(peca,jogadores,jogador_count);
                if (peca_true==1) break;
                printf("Não Há Mais Peças do tipo Selecionado!!!\n");
                printf("\n- > ");
                scanf("%i",&peca);
                while (getchar() != '\n');
            }
            peca_true=0;
            //FIM VERIFICAÇÃO EXISTÊNCIA DA PEÇA

            //FIM ESCOLHA PEÇA JOGADOR

                //ESCOLHA LOCAL JOGADOR
                printf("\nEscolha agora onde jogar.\n");
                printf("\n- > ");
                scanf("%s",&position);
                position_true = verify_position(position,tabuleiro);
                //VERIFICAÇÃO EXISTÊNCIA DA POSIÇÃO
                while (position_true == 0){
                    printf("Posição inválida!");
                    printf("\n\n- > ");
                    scanf("%s",&position);
                    position_true = verify_position(position,tabuleiro);
                }
                //FIM VERIFICAÇÃO EXISTÊNCIA DA POSIÇÃO
                position_true=0;

                //FIM ESCOLHA LOCAL JOGADOR

            //CONFERE VERACIDADE DA JOGADA
            jogada_true = verify_jogada_total(peca,jogador_count,jogadores,tabuleiro,position);
            if (jogada_true == 0) {
                system("pause");
            } else {
                if (jogador_count == 3) {
                    jogador_count=0;
                }
                else jogador_count++;
                if (conta_fim(jogadores) == 1) fim++;
                }
            }

        //SE AJOGADA NÃO FOI VERDADEIRA, REPETE JOGADA DO ATUAL
        } while(jogada_true == 0);
        jogada_true = 0;
    //QUANDO PEÇAS DO JOGADOR ACABAR O JOGO É FINALIZADO AO VOLTAR PARA ELE
    }while(fim != 4);
    //CRIA A ÚLTIMA MATRIZ DA VISÃO
    create_matriz_visao(jogadores,tabuleiro);
    //CRIA A VISÃO EM PLATAFORMA DO JOGADORES
    for (int i=0;i<4;i++) minha_visao(jogadores,i,0);
    //MOSTRA VENCEDOR COM MAIS PONTUAÇÕES
    winner(jogadores);
    //FINALIZA O JOGO "GUARDA O TABULEIRO"
    clean_tabuleiro(tabuleiro,tabuleiro_central);
    clean_jogadores(jogadores);
    printf("\n\nAdiós!!!");
    //FIM DE JOGO




}

