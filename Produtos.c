#include <stdio.h>
#include "Boolean.h"
#include <string.h>
#include <stdlib.h>
#include "avl.h"
#include "Produtos.h"

/*Estrutura do catálogo de produtos*/

typedef struct catP{
	int total; /* total de produtos */
	AVL CatLetra[26]; /* 1 AVL para cada letra do alfabeto (26 avls) */
	int tamAvls[26]; /* Indica o tamanho das avls */
}CatP;


/* Estrutura do produto */

typedef struct produto{
	char* produto; /* código do produto */
}pr;

/*Gets e Sets da estrutura do catalogo de produtos*/

/* Função que dado um produto retorna o código desse produto */

char* getCodProd(Produto a){ 
	return a->produto;
}

/* Função que retorna o tamanho da AVL de produtos na posição n */

int getTamanho(Cat_Produto cp,int n){ 
	return cp->tamAvls[n];
}

/* Função que vai permitir fazer as comparações na AVL, em função do código do Produto */

int compara_Produto (void* a,void* b ) { /* Função que vai permitir fazer as comparações na AVL */
	Produto p1,p2;
	p1=(Produto) a;
	p2=(Produto) b;
    return (strcmp(p1->produto,p2->produto));}

/* Função responsável por criar uma estrutura com o código do produto, retornando um apontador para essa estrutura */

Produto criaProduto(char* s){ 
	Produto p=malloc(sizeof(struct produto));
    p->produto=malloc(sizeof(strlen(s)));
	strcpy(p->produto,s);
	return p;
}

/* Função que inicializa a estrutura do catalogo de produtos */

Cat_Produto initCatalogo(){ 
	Cat_Produto new=malloc(sizeof(struct catP));
	int i;
	new->total=0;
	for(i=0;i<26;i++) {
		new->CatLetra[i]=NULL;
		new->tamAvls[i]=0;}
    return new;
}

/* Função que insere um produto no catálogo de produtos */

Cat_Produto insereCatP(Cat_Produto t,Produto k){ 
	int c=0;
	int n=k->produto[0]-65;
	t->total++;
	t->CatLetra[n]=insereAVL(t->CatLetra[n],k,&c,compara_Produto);
	(t->tamAvls[n])++;
	return t;
}

/* Função que verifica se um determinado produto existe no catalogo de produtos */

Boolean existe_Produto(Cat_Produto ct,Produto k){ 
	int n=k->produto[0]-65;
	Boolean b=initBool();
	if(getBool(existe_String(ct->CatLetra[n],k,compara_Produto))==True) b=setBool(b,True);
	return b;
	}

/* Função que indica o total de produtos existentes no catálogo de produtos */

int totalProdutos(Cat_Produto cp){ 
	return cp->total;
}
 
/* Função que retorna o número total de produtos que começam por uma determinada letra */

int totalProdutosLetra(Cat_Produto cp, char letra){ 
	return (cp->tamAvls[letra-65]);
}

/* Função que liberta o espaço de memória ocupado pela estrutura do catálogo de produtos */

void removeCatProds(Cat_Produto cp){ 
	int i;
	for (i=0;i<26;i++)
		removeAVL(cp->CatLetra[i]);
	free(cp);
}


/*Conjunto de Produtos*/

#define PAGESIZE 20


/* Estrutura do tipo PaginaP */

typedef struct pagP{
	char** pagina;
	int pag_size,index;
}pgp;

/* Estrutura do tipo ConjP */

typedef struct conjProds{
	char** conjP;
	int quantos,pag_atual,pag_size,pag_final;
}cjP;

/* Gets */

/* Função que retorna o tamanho da página */

int getPageSizeP(PaginaP p){
	return p->pag_size;
}

/* Função que retorna o código do Produto que está na posição index da Pagina */

char* getNextProdP(PaginaP p){
	p->index+=1;
	return p->pagina[p->index];
}

/* Função que cria um conjunto de produtos com o tamanho parametrizado e devolve um apontador para essa estrutura. */

ConjP init_ConjP(int tam){
	ConjP novo=malloc(sizeof(struct conjProds));
	novo->conjP=malloc(sizeof(char*)*tam);
	novo->quantos=0;
	novo->pag_atual=0;
	novo->pag_size=PAGESIZE;
	novo->pag_final=0;
	return novo;
}

/**  Função que permite inserir um produto num conjunto de produtos */

ConjP insereConjP(ConjP cjp,Produto p){
	cjp->conjP[cjp->quantos]=malloc(strlen(p->produto)+1);
	strcpy(cjp->conjP[cjp->quantos],p->produto);
	cjp->quantos+=1;
	return cjp;
}

/* Função auxiliar que percorre uma avl de produtos e insere esses mesmos produtos num conjunto de produtos */

ConjP percorreCatalogoP(ConjP cjp,AVL a){
	if(a!=NULL){
		cjp=percorreCatalogoP(cjp,getEsq(a));
		cjp=insereConjP(cjp,(Produto)get(a));
		cjp=percorreCatalogoP(cjp,getDir(a));
	}
	if(cjp->quantos!=0){
		cjp->pag_atual=1;
		cjp->pag_final=(cjp->quantos/PAGESIZE)+1;
	}
	return cjp;
}

/* Função que dado um catálogo de produtos e uma letra, percorre a AVL de produtos corresponde a essa letra e insere esses produtos num conjunto de produtos. */

ConjP leituraProdsLetra(Cat_Produto cp,char letra){
	ConjP cjp=init_ConjP(cp->tamAvls[letra-65]);
	cjp=percorreCatalogoP(cjp,cp->CatLetra[letra-65]);
	cjp->pag_atual=1;
	return cjp;
}

/* Função que atualiza os indices para a próxima página */

PaginaP nextPageP(ConjP cp){
	PaginaP p;
	if(cp->pag_atual<cp->pag_final){
		cp->pag_atual+=1;
	}
	p=malloc(sizeof(struct pagP));
	p->pagina=cp->conjP;
	p->index=(cp->pag_atual-1)*20-1;
	if(cp->pag_atual==cp->pag_final) p->pag_size=cp->quantos - (p->index+1);
	else p->pag_size=cp->pag_size;
	return p;
}
/* Função que atualiza os indices para a pagina anterior */

PaginaP prevPageP(ConjP cp){
  	PaginaP p;
	if(cp->pag_atual>1){
		cp->pag_atual-=1;
	}
	if(cp->pag_atual==0) cp->pag_atual=1;
	p=malloc(sizeof(struct pagP));
	p->pagina=cp->conjP;
	p->index=(cp->pag_atual-1)*20-1;
	p->pag_size=cp->pag_size;
	return p;
}
/* Função que atualiza os indices para a primeira página */

PaginaP firstPageP(ConjP cp){
	PaginaP p;
  cp->pag_atual=1;
	p=malloc(sizeof(struct pagP));
	p->pagina=cp->conjP;
	p->index=(cp->pag_atual-1)*20-1;
	p->pag_size=cp->pag_size;
	return p;
}
/* Função que atualiza os indices para a ultima página */

PaginaP lastPageP(ConjP cp){
	PaginaP p;
  cp->pag_atual=cp->pag_final;
	p=malloc(sizeof(struct pagP));
	p->pagina=cp->conjP;
	p->index=(cp->pag_atual-1)*20-1;
	p->pag_size=cp->quantos - (p->index+1);
	return p;
}


/*Função que liberta o espaço de memória ocupada pela estrutura do tipo PaginaP*/

void removePaginaP(PaginaP p){
	free(p);
}

/*Função que liberta o espaço de memória ocupada pela estrutura do tipo ConjP*/

void removeConjP(ConjP cp){
	int i;
	for(i=0;i<cp->quantos;i++)
		free(cp->conjP[i]);
	free(cp->conjP);
	free(cp);
}
