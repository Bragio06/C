#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "fogefoge.h"
#include "mapa.h"

MAPA m;
POSICAO heroi;
int temPirula = 0;


int acabou() {
	POSICAO pos;

	int perdeu = !encontramapa(&m, &pos, HEROI);
	int ganhou = !encontramapa(&m, &pos, FANTASMA);

	return ganhou || perdeu;
		
}

int ehdirecao(char direcao) {
	return
		direcao == ESQUERDA || 
		direcao == CIMA ||
		direcao == BAIXO ||
		direcao == DIREITA;
}

void move(char direcao) {

	if(!ehdirecao(direcao))	
		return;

	int proximox = heroi.x;
	int proximoy = heroi.y;

	switch(direcao) {
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
	}

	if(!podeandar(&m, HEROI, proximox, proximoy))
		return;

	if(ehpersonagem(&m, PIRULA, proximox, proximoy)) 
		temPirula = 1;

	andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;
}

int praondefantasmavai(int xatual, int yatual, 
	int* xdestino, int* ydestino) {

	int opcoes[4][2] = { 
		{ xatual   , yatual+1 }, 
		{ xatual+1 , yatual   },  
		{ xatual   , yatual-1 }, 
		{ xatual-1 , yatual   }
	};

	srand(time(0));
	for(int i = 0; i < 10; i++) {
		int posicao = rand() % 4;

		if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
			return 1;
		}
	}

	return 0;
}

void explodepirula() {
	for(int i = 0;i<=3;i++){
		if(ehvalida(&m, heroi.x, heroi.y+i) && 
		   !ehparede(&m, heroi.x, heroi.y+i)) {

			if(ehparede(&m, heroi.x, heroi.y+i)) {
				break;
			}
			m.matriz[heroi.x][heroi.y+i] = VAZIO;
			}
	}
}

void fantasmas() {
	MAPA copia;

	copiamapa(&copia, &m);

	for(int i = 0; i < copia.linhas; i++) {
		for(int j = 0; j < copia.colunas; j++) {
			if(copia.matriz[i][j] == FANTASMA) {

				int xdestino;
				int ydestino;

				int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);

				if(encontrou) {
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}

	liberamapa(&copia);
}

int main() {
	
	lemapa(&m);
	encontramapa(&m, &heroi, HEROI);

	do {
		printf("Tem pirula: %s\n", temPirula ? "sim" : "nao");
		imprimemapa(&m);

		char comando;
		scanf(" %c", &comando);

		move(comando);
		if(comando == BOMBA) explodepirula();
		fantasmas();

	} while (!acabou());

	liberamapa(&m);
}