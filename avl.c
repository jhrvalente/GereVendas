#include <stdio.h>
#include <stdlib.h>
#include "Boolean.h"
#include <string.h>
#include "avl.h"

#define E -1
#define B 0
#define D 1

#define TAM 10

/* Estrutura avl */

struct avl{
	void* str;
	int bal;
	struct avl* esq;
	struct avl* dir;
};

/* Função que dada uma avl retorna o que estiver no campo str da avl */

void* get(AVL a){
	return a->str;
	}

/* Função que dada uma avl modifica o que estiver no campo str da avl */
	
AVL set(AVL a,void* c){
	a->str=c;
	return a;
}

/* Função que redefine a sub-arvore direita de uma dada avl a, como sendo a AVL b. */

AVL setDir(AVL a,AVL b){
	a->dir=b;
	return a;
}

/* Função que redefine a sub-arvore esquerda de uma dada avl a, como sendo a AVL b. */

AVL setEsq(AVL a,AVL b){
	if(a!=NULL)
	a->esq=b;
	else return b;
	return a;
}

/* Função que retorna a sub-árvore esquerda de uma dada AVL */

AVL getEsq(AVL a){
	return a->esq;
}

/* Função que retorna a sub-árvore direita de uma dada AVL */

AVL getDir(AVL a){
	return a->dir;
}

/* Função que copia uma AVL b para uma AVL a, retornando o apontador para esta última */

AVL copiaAVL(AVL a,AVL b){
	a=b;
	return a;
}

void removeAVL(AVL a){
	if(a==NULL) ;
	else {
		removeAVL(a->esq);
		removeAVL(a->dir);
		free(a->str);
		free(a);
	}
}

/* Função que verifica se existe uma determinada string numa dada AVL */

Boolean existe_String(AVL a,void* c,int comp(void* arg1,void* arg2)){
	int cmp=0;
	AVL aux=a;
	Boolean b=initBool();
    while(aux!=NULL){
     	cmp=comp(aux->str,c);
     	if(cmp>0) aux=aux->esq;
     	else if (cmp==0) return setBool(b,True);
     		 else aux=aux->dir;}
     return setBool(b,False);}

/* Função que dada uma AVL e um parâmetro do tipo void* e com base num comparador, retorna uma avl com esse valor do tipo void* como raíz da avl */

AVL percorreAVL(AVL a,void* c,int comp(void* arg1,void* arg2)){
	AVL aux=a;
	int cmp=0;
    while(aux!=NULL){
     	cmp=comp(aux->str,c);
     	if(cmp>0) aux=aux->esq;
     	else if (cmp==0) return aux;
     		 else aux=aux->dir;}
    return NULL;}


/**Rotação simples da arvore para a esquerda*/
AVL rotateRight(AVL a) {
	AVL aux;
	if (a&&a->esq) {
	aux = a->esq;
	a->esq = aux->dir;
	aux->dir = a;
	a = aux;
	}
	else return NULL;
	return a;
}

/**Rotação simples da arvore para a esquerda*/
AVL rotateLeft(AVL a) {
        AVL aux;
        if (a&&a->dir) {
        aux = a->dir;
        a->dir = aux->esq;
        aux->esq = a;
        a = aux;
        }
        else return NULL;
        return a;
}

/**Função que balanceia a sub-arvore da direita*/
AVL balancaDireita(AVL a) {
	if (a->dir->bal==D) {
	/** Roda para a esquerda*/
	a = rotateLeft(a);
	a->bal = B;
	a->esq->bal = B;
	}
	else {
    /**rotações direita,e esquerda*/
	a->dir = rotateRight(a->dir);
	a = rotateLeft(a);
	/**Colocar os fatores de balanceamento*/
	if(a->bal==B) {
	a->esq->bal = B;
	a->dir->bal = B;}
	else if(a->bal==E){
	a->esq->bal =B;
	a->dir->bal =D;}
		 else if(a->bal==D){
			a->esq->bal=E;
			a->dir->bal=B;
	}}
	a->bal = B;
	return a;
}
/**Função que balanceia a sub-arvore da esquerda*/
AVL balancaEsquerda(AVL a) {
        if (a->esq->bal==E) {
        /** roda para a direita*/
        a = rotateRight(a);
        a->bal = B;
        a->dir->bal = B;
        }
	    else {
	    /**Dupla rotacao, primeiro para a esquerda, segundo para a direita*/
        a->esq = rotateLeft(a->esq);
        a = rotateRight(a);
        /**Colocar os fatores de balanceamento nas sub-arvores*/
        if (a->bal==B) {
        a->esq->bal = B;
        a->dir->bal = B;}
        else if(a->bal==D){
        a->esq->bal =E;
        a->dir->bal =B;}
             else if(a->bal==E){
        			a->esq->bal=B;
        			a->dir->bal=D;}}
        a->bal = B;
        return a;
}

/**Função que insere um código na árvore direita*/
AVL insereDireita (AVL a,void* c, int *cresceu,int comp(void *,void*)) {
	a->dir = insereAVL(a->dir,c,cresceu,comp);
	/**confirmacao se adicionou ou nao, se adicionar entao tem atualizar os indices de balanceamento*/
	if (*cresceu){
	    if(a->bal==E) {
			a->bal = B;
			*cresceu = 0;}
		else if(a->bal==B){
		a->bal = D;
		*cresceu = 1;}
			 else if(a->bal==D){
					a = balancaDireita(a);
					*cresceu = 0;}
	}
	return a;
}
/**Função que insere um código na árvore esquerda*/
AVL insereEsquerda (AVL a,void* c, int *cresceu,int comp(void *,void*)) {
        a->esq = insereAVL(a->esq,c,cresceu,comp);
        if (*cresceu){
           if (a->bal==D) {
                a->bal = B;
                *cresceu = 0;}
			else if(a->bal==B){
                a->bal = E;
                *cresceu = 1;}
                  else if(a->bal==E){
                		a = balancaEsquerda(a);
                		*cresceu = 0;}
                }
        return a;
}
/**Função que faz a inserção na AVL, de um código c*/
AVL insereAVL (AVL a,void* c, int *cresceu,int comp(void* a,void* b)) {
	int cmp=0;
	if (a==NULL) {
		a=malloc(sizeof(struct avl));
		a->str=c;
		a->dir = a->esq= NULL;
		a->bal = B;
		*cresceu = 1;}
	else {cmp=comp((a->str),c);
		 if (cmp==0) ;
	     else if (cmp<0){
				a = insereDireita(a,c,cresceu,comp);
	     }
		  else{ 
				a = insereEsquerda(a,c,cresceu,comp);
		  }}
	return a;
}