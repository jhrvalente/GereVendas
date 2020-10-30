#include <string.h>
#include <stdlib.h>
#include "listaStrings.h"

/*Conjunto de Produtos*/

#define PAGESIZE 20

typedef struct pag{
	char** pagina;
	int pag_size,index;
}pg;

typedef struct lstStr{
	char** lista;
	int quantos,pag_atual,pag_size,pag_final,tam;
}lst;

/* Get's */

/*Função que retorna o tamanho da página*/
int getPageSize(Pagina p){
	return p->pag_size;
}

/* Função que retorna a String que está na posição i */
char* getNextString(Pagina p){
	p->index+=1;
	return p->pagina[p->index];
}


/* Função que inicializa um conjunto de produtos */
Lista_Strings initListaStrings(int tamanho){
	Lista_Strings novo=malloc(sizeof(struct lstStr));	
	novo->lista=malloc(sizeof(char*)*tamanho);
	novo->quantos=0;
	novo->pag_atual=0;
	novo->pag_size=PAGESIZE;
	novo->pag_final=0;
	novo->tam=tamanho;
	return novo;
}

/*Função que insere na lista uma string*/
Lista_Strings insereLista(Lista_Strings ls,char* s){
	ls->lista[ls->quantos]=malloc(strlen(s)+1);
	strcpy(ls->lista[ls->quantos],s);
	ls->quantos+=1;
	return ls;
}


/* Função que inicializa a lista */
Lista_Strings initListaStrings_dim(){
	Lista_Strings novo=malloc(sizeof(struct lstStr));	
	novo->lista=malloc(sizeof(char*)*1024);
	novo->quantos=0;
	novo->pag_atual=0;
	novo->pag_size=PAGESIZE;
	novo->pag_final=0;
	novo->tam=1024;
	return novo;
}

/*Função que insere na lista uma string*/
Lista_Strings insereLista_dim(Lista_Strings ls,char* s){
	if(ls->quantos==ls->tam){
		ls->tam=ls->tam*2;
		ls->lista=realloc(ls->lista,sizeof(char*)*ls->tam);
	}
	ls->lista[ls->quantos]=malloc(strlen(s)+1);
	strcpy(ls->lista[ls->quantos],s);
	ls->quantos+=1;
	return ls;
}

Lista_Strings atualizaIndices(Lista_Strings ls){
	ls->pag_final=(ls->quantos/ls->pag_size)+1;
	if(ls->quantos-((ls->pag_final-1)*ls->pag_size)==0) ls->pag_final-=1;
	return ls;
}

/* Função que atualiza os indices para a próxima página */
Pagina nextPage(Lista_Strings ls){
	Pagina p;	
	if(ls->pag_atual<ls->pag_final){
		ls->pag_atual+=1;
	}
	p=malloc(sizeof(struct pag));
	p->pagina=ls->lista;
	p->index=(ls->pag_atual-1)*ls->pag_size-1;
	if(ls->pag_atual==ls->pag_final) p->pag_size=ls->quantos - (p->index+1);
	else p->pag_size=ls->pag_size;
	return p;
}
/* Função que atualiza os indices para a pagina anterior */
Pagina prevPage(Lista_Strings ls){
	Pagina p;
	if(ls->pag_atual>1){
		ls->pag_atual-=1;
	}
	if(ls->pag_atual==0) ls->pag_atual=1;
	p=malloc(sizeof(struct pag));
	p->pagina=ls->lista;
	p->index=(ls->pag_atual-1)*ls->pag_size-1;
	if(ls->quantos<ls->pag_size) p->pag_size=ls->quantos;	
	else p->pag_size=ls->pag_size;
	return p;
}
/* Função que atualiza os indices para a primeira página */
Pagina firstPage(Lista_Strings ls){
	Pagina p;	
	ls->pag_atual=1;
	p=malloc(sizeof(struct pag));
	p->pagina=ls->lista;
	p->index=-1;
	if(ls->quantos<ls->pag_size) p->pag_size=ls->quantos;	
	else p->pag_size=ls->pag_size;
	return p;
}
/* Função que atualiza os indices para a ultima página */
Pagina lastPage(Lista_Strings ls){
	Pagina p;	
	ls->pag_atual=ls->pag_final;
	p=malloc(sizeof(struct pag));
	p->pagina=ls->lista;
	p->index=(ls->pag_atual-1)*ls->pag_size-1;
	p->pag_size=ls->quantos - (p->index+1);
	return p;
}

Lista_Strings setPageSize(Lista_Strings ls,int size){
	ls->pag_size=size;
	return ls;
}

int tamanhoLista(Lista_Strings ls){
	return ls->quantos;
}

void removePagina(Pagina p){
	free(p);
}

void removeListaStrings(Lista_Strings ls){
	int i;
	for(i=0;i<ls->quantos;i++)
		free(ls->lista[i]);
	free(ls->lista);
	free(ls);
}
