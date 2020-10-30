#include <stdlib.h>
#include "Boolean.h"


/* Estrutura do tipo boolean */

struct bln{
	bool b;
};

/** Função que inicializa a estrutura do tipo boolean */

Boolean initBool(){
	Boolean b=malloc(sizeof(struct bln));
	b->b=False;
	return b;
} 

/* Função que altera o valor booleano no Boolean b para o valor de bl, sendo b e bl passados à função como argumentos */

Boolean setBool(Boolean b,bool bl){
	b->b=bl;
	return b;
}

/* Função que retorna o valor booleano do Boolean b que lhe é passado como argumento */

bool getBool(Boolean b){
	return b->b;
}

/* Função que liberta o espaço de memória reservado pela estrutura do tipo Boolean */

void removeBoolean(Boolean b){
	free(b);
}
