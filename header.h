#define imax 25
#define jmax 25

short M[imax + 1][jmax + 1], MAUX[imax + 1][jmax + 1]; // matrizes principal e auxiliar
int i, j, auxi, auxj, aux, ciclos = 0, lim = -1, alea = 0, alean;
char input[128];

void limpartela();
void inictabela();
void copiar();
void imprimir();
void lerentr();
int interpretar();
void alterar(short z, short y);
int letra(char caractere);
void atualizar();
void randomizar();
