# Skyliners - Projeto Final de Algoritmo e Estruturas de Dados

## Descrição do Projeto

Este projeto consiste na implementação de uma versão digital do jogo de tabuleiro **Skyliners**. O objetivo do jogo é que cada jogador construa prédios em um tabuleiro compartilhado, visando maximizar a quantidade de prédios visíveis a partir da sua perspectiva. O jogo é jogado por 4 jogadores, cada um representando um dos cantos do tabuleiro (Norte, Sul, Leste, Oeste). O jogador que tiver mais prédios visíveis ao final da partida vence.

O projeto foi desenvolvido na linguagem C, utilizando conceitos de **algoritmos** e **estruturas de dados**, como **listas dinâmicas** e **pilhas dinâmicas**, para gerenciar as peças dos jogadores e a construção dos prédios no tabuleiro.

## Como Executar o Jogo

Para rodar o jogo **Skyliners**, siga os passos abaixo:

### Pré-requisitos
- Certifique-se de ter um compilador C instalado (ex: `gcc`).
- O código do jogo deve estar organizado nos arquivos `main.c`, `sk0.c` e `sk0.h`.

### Passos para Compilar e Executar

1. Abra o terminal no diretório onde os arquivos do jogo estão localizados.

2. Compile o código usando o comando abaixo:
   ```bash
   gcc main.c sk0.c -o skyliners
   ```
   Isso gerará um arquivo executável chamado `skyliners`. no windows apenas execute `skyliners.exe`, no Linux:

3. Execute o jogo com o comando:
   ```bash
   ./skyliners
   ```

4. Siga as instruções exibidas no terminal para jogar:
   - Escolha as peças (andar, telhado ou parque) e posicione-as no tabuleiro.
   - Acompanhe a visão do tabuleiro e a perspectiva de cada jogador.
   - O jogo termina quando um jogador coloca seu último andar, e o vencedor é declarado com base nos prédios visíveis.

### Exemplo de Uso
```bash
$ gcc main.c sk0.c -o skyliners
$ ./skyliners
```

## Regras do Jogo

### Componentes do Jogo
- **Tabuleiro**: Uma grade 5x5 com um parque central fixo.
- **Peças**:
  - **Andares**: Cada jogador tem 12 andares para construir prédios.
  - **Telhados**: Cada jogador tem 3 telhados para finalizar prédios.
  - **Parques**: Cada jogador tem 1 parque para bloquear áreas do tabuleiro.

### Preparação do Jogo
1. O tabuleiro é inicializado com um parque central.
2. São colocadas 6 peças neutras (andares) em posições aleatórias no tabuleiro, exceto no parque central.
3. Cada jogador recebe suas peças iniciais: 12 andares, 3 telhados e 1 parque.

### Dinâmica do Jogo
1. Os jogadores jogam em turnos, no sentido horário.
2. Em cada turno, o jogador escolhe uma peça (andar, telhado ou parque) e a posiciona no tabuleiro, respeitando as seguintes regras:
   - **Andares**: Podem ser colocados no chão ou em cima de outros andares. Não podem ser colocados em cima de telhados ou parques.
   - **Telhados**: Só podem ser colocados em cima de andares.
   - **Parques**: Só podem ser colocados no chão.
3. O objetivo é maximizar a quantidade de prédios visíveis a partir da perspectiva do jogador. Um prédio é visível se não estiver totalmente bloqueado por outro prédio mais alto ou mais próximo.
4. O jogo termina quando um jogador coloca seu último andar. Todos os jogadores jogam o mesmo número de turnos para garantir justiça.
5. Ao final, os pontos são contados com base na quantidade de prédios visíveis para cada jogador. O jogador com mais pontos vence.

## Exemplo de Funcionamento

### Inicialização
- O tabuleiro é exibido com o parque central e as 6 peças neutras posicionadas aleatoriamente.
- Cada jogador recebe suas peças iniciais.

### Durante o Jogo
- O jogador atual escolhe uma peça e a posiciona no tabuleiro.
- O tabuleiro é atualizado e exibido, mostrando as alturas das pilhas e as áreas disponíveis para jogar.
- O próximo jogador faz sua jogada.

### Final do Jogo
- Quando um jogador coloca seu último andar, o jogo entra na fase final.
- Após todos os jogadores terminarem seus turnos, os pontos são contados.
- O vencedor é declarado com base na quantidade de prédios visíveis.

## Pontuação

A pontuação do projeto será baseada nos seguintes critérios:
- **Preparação do Jogo**: 1 ponto
- **Turnos dos Jogadores**: 2 pontos
- **Visualização do Tabuleiro**: 2 pontos
- **Finalização do Jogo**: 0.5 ponto
- **Vista da Cidade (Perspectiva dos Jogadores)**: 2 pontos
- **Vitória (Contagem de Pontos)**: 1.5 ponto
- **Boas Práticas**: 1.5 ponto

Total: 10 pontos.

**Divirta-se construindo sua cidade!** 🏙️
