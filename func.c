#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "header.h"

#ifdef _WIN64
void limpartela() {
	system("cls");
}
#endif

#ifdef __unix__
void limpartela() {
	system("clear");
}
#endif

void inictabela() {
	for(i = 0; i <= imax; ++i) {
		for(j = 0; j <= jmax; ++j) {
			MAUX[i][j] = 0;
			M[i][j] = 0;
		}
	}
}

void copiar() {
	for(i = 0; i <= imax; ++i) {
		for(j = 0; j <= jmax; ++j) {
			MAUX[i][j] = M[i][j];
		}
	}
}

void imprimir() {
	limpartela();
	printf("   ");
	for(i = 0; i <= imax; ++i){
		printf("\e[90m" "%c " "\e[0m", 'A' + i);
	}
	
	printf("\n");
	
	for(i = 0; i <= imax; ++i) {
		printf("\e[90m" " %c" "\e[0m", 'A' + i);
		for(j = 0; j <= jmax; ++j) {
			switch(M[i][j]) {
				case 0:
					printf("  ");
					break;
					
				case 1:
					if(j == 0 || j == jmax || i == 0 || i == imax) {
						printf("\e[90m" " #" "\e[0m");
					}
					else {
						printf(" #");
					}
					break;
					
				default:
					printf("erro");
			}
		}
		
		printf("\e[90m" " %c\n" "\e[0m", 'A' + i);
	}
	
	printf("   ");
	for(i = 0; i <= imax; ++i){
		printf("\e[90m" "%c " "\e[0m", 'A' + i);
	}
}

void lerentr() {
	for(aux = 0; aux <= 100; ++aux) {
		input[aux] = '\0';
	}
	
	printf("\n\n %i >>> ", ciclos);
	
	if (ciclos > lim) {
		alea = 0;
		fgets(input, 128, stdin);
	}
	else {
		if(alea == 1) {
			randomizar();
		}
		
		printf("%i\n", lim);
		usleep(50000);
		return;
	}
	
	for(aux = 0; input[aux + 1] != '\0'; ++aux) { // transforma as letras minusculas em maiusculas
		if(input[aux] >= 97 && input[aux] <= 122) {
			input[aux] -= 32;
		}
	}
}

int interpretar() {
	if(input[0] == '\n' || input[0] == '\0') {
		return(1);
	}
	
	int valido = 0, inicionum;
	
	if(input[0] == '!') {
		if(input[1] == 'A' && input[2] == 'U' && input[3] == 'T' && input[4] == 'O') {
			valido = 1;
			inicionum = 6;
		}
		else if(input[1] == 'R' && input[2] == 'A' && input[3] == 'N' && input[4] == 'D') {
			valido = 1;
			alea = 1;
			
			if(input[7] == ' ' && input[8] != ' ') {
				inicionum = 8;
				alean = input[6] - 48;
			}
			else {
				inicionum = 6;
				alean = 3;
			}
		}
		else {
			return(0);
		}
		
		lim = 0;
		for(aux = inicionum; input[aux + 1] != '\0'; aux++) {
			lim = lim*10;
			lim = lim + (int)(input[aux]) - 48;
		}
		lim += ciclos;
		
		if(lim == 0) {
			lim = 1;
		}
	}
	else {
		for(aux = 0; input[aux] != '\0';) {
			if(letra(input[aux]) && letra(input[aux + 1]) && (input[aux + 2] == '\n' || input[aux + 2] == ' ')) {
				valido = 1;
				alterar(input[aux + 1] - 65, input[aux] - 65);
				aux += 3;
			}
			else {
				break;
			}
		}
	}
	
	return(valido);
}

void alterar(short z, short y) {
	if(M[z][y] == 0) {
		M[z][y] = 1;
	}
	else {
		M[z][y] = 0;
	}
}

int letra(char caractere) {
	if(caractere >= 65 && caractere <= 90) {
		return(1);
	}
	else {
		return(0);
	}
}

void atualizar() {
	for(i = 1; i <= imax - 1; ++i) {
		for(j = 1; j <= jmax - 1; ++j) {
			aux = 0;
			
			for(auxi = i - 1; auxi <= i + 1; auxi++) {
				for(auxj = j - 1; auxj <= j + 1; auxj++) { // avalia as casas adjacentes a casa sendo checada
					if(auxi == i && auxj == j){
						continue; // pula a casa sendo checada
					}
					
					if(MAUX[auxi][auxj] == 1) {
						aux++; // adiciona uma unidade ao contador de casas adjacentes ativas
					}
				}
			}
			
			if(MAUX[i][j] == 1) {
				if(aux != 2 && aux != 3) {
					M[i][j] = 0;
				}
			}
			else if(MAUX[i][j] == 0) {
				if(aux == 3) {
					M[i][j] = 1;
				}
			}
		}
	}
	
	ciclos++;
}

void randomizar() {
	aux = rand() % alean;
	for(i = 0; i <= aux; i++) {
		alterar(rand() % imax + 1, rand() % jmax + 1);
	}
}
