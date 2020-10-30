#include <stdio.h>
#include <string.h>
#include "Boolean.h"
#include <stdlib.h>
#include "avl.h"
#include "Clientes.h"

/* Estrutura do catálogo de clientes */

typedef struct cat{
	int total; /* total de clientes */
	AVL CatLetra[26]; /* 1 AVL para cada letra do alfabeto (26 avls) */
	int tamAvls[26]; /* Indica o tamanho das avls */
}C;

/* Estrutura do cliente */

typedef struct cliente{
	char* cliente; /* código do cliente */
}cl;

/*Gets e Sets da estrutura do catalogo de clientes*/


/* Função que dado um cliente retorna o código desse cliente */

char* getCodCliente(Cliente c){
	return c->cliente;
}

/* Função que dada uma avl retorna o cliente que se encontra na raíz dessa avl */

Cliente getCliente(AVL a){
	return get(a);
}

/* Função que altera o código do cliente, para a string s que lhe é passada como parâmetro */

void setCliente(Cliente str,char* s){
	strcpy(str->cliente,s);
}

/* Função que retorna o tamanho da AVL de clientes na posição n */

int getTamanhoC(Cat_Cliente cl,int n){
	return cl->tamAvls[n];
}

/* Função que retorna a AVL de clientes na posição n */ 

AVL getAVLCliente(Cat_Cliente c,int n){
	return c->CatLetra[n];
}

/* Função que vai permitir fazer as comparações na AVL em função do código de cliente */

int compara_Clientes (void* a,void* b ) {
    return (strcmp(((Cliente)a)->cliente,((Cliente)b)->cliente));}

/* Função responsável por criar uma estrutura com o código do cliente, retornando um apontador para essa estrutura */

Cliente criaCliente(char* str){
	Cliente c=malloc(sizeof(struct cliente));
    c->cliente=malloc(sizeof(strlen(str)));
	strcpy(c->cliente,str);
	return c;
}

/** Função que inicializa a estrutura do catalogo */

Cat_Cliente inicia_CatalogoC(){
	Cat_Cliente new=malloc(sizeof(struct cat));
	int i;
	new->total=0;
	for(i=0;i<26;i++){
		new->CatLetra[i]=NULL;
		new->tamAvls[i]=0;
	} 
    return new;
}


/**Função que insere na estrutura cat. A estrutura cat contém um array de apontadores para avls.*/

Cat_Cliente insereCatC(Cat_Cliente t,Cliente k){
	int c=0;
	int n=k->cliente[0]-65;
	t->total++;
	t->CatLetra[n]=insereAVL(t->CatLetra[n],k,&c,compara_Clientes);
	(t->tamAvls[n])++;
	return t;
}

/** Função que verifica se o cliente existe no catalogo de clientes. */

Boolean existe_ClienteCat(Cat_Cliente ct,Cliente k){
	int n=k->cliente[0]-65;
	Boolean b=initBool();
	if(getBool(existe_String(ct->CatLetra[n],k,compara_Clientes))==True) b=setBool(b,True);
	return b;
	}	

/** Função que retorna o total de clientes existente na estrutura. */

int totalClientes(Cat_Cliente cc){
	return cc->total;
}

/**Função que indica o total de clientes começados por uma certa letra. */

int totalClientesLetra(Cat_Cliente cc, char letra){
	return (cc->tamAvls[letra-65]);
}

/** Função que liberta a memória utilizada pelo catalogo de clientes. */

void removeCatClientes(Cat_Cliente cc){
	if(cc==NULL) ;
	else {
		 int i;
		 for(i=0;i!=26;i++)
		 	removeAVL(cc->CatLetra[i]);
		 free(cc);
	}
}




