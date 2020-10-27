// 1.0: 23/11/2019
// 2.0: 31/08/2020: modularizacao, suporte a Linux, uso de cores para indicar casas fixas e comando !RAND

#include <stdio.h>
#include <stdlib.h>

#include "func.c"

int main() {
	srand(time(0));
	
	inictabela();
		
	for(;;) {
		copiar();		
		imprimir();
		
		lerentr();
		if(interpretar() == 1) {
			atualizar();
		}
	}
}
