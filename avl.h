#ifndef avl_h 
#define avl_h

typedef struct avl *AVL; 
typedef int (*comp)(const void*, const void*);

/* Função que redefine a sub-arvore direita de uma dada avl a, como sendo a AVL b. */
AVL setDir(AVL a,AVL b);
/* Função que redefine a sub-arvore esquerda de uma dada avl a, como sendo a AVL b. */
AVL setEsq(AVL a,AVL b);
/* Função que dada uma avl retorna o que estiver no campo str da avl */
void* get(AVL );
/* Função que dada uma avl modifica o que estiver no campo str da avl */
AVL set(AVL,void*);
/* Função que retorna a sub-árvore direita de uma dada AVL */
AVL getDir(AVL );
/* Função que retorna a sub-árvore esquerda de uma dada AVL */
AVL getEsq(AVL );
/* Função que dada uma AVL e um parâmetro do tipo void* e com base num comparador, retorna uma avl com esse valor do tipo void* como raíz da avl. */
AVL percorreAVL(AVL a,void* c,int comp(void* arg1,void* arg2));
/* Função que copia uma AVL b para uma AVL a, retornando o apontador desta última */
AVL copiaAVL(AVL a,AVL b);
/* Função que liberta o espaço de memória alocado para a estrutura do tipo AVL */
void removeAVL(AVL );
/* Função que verifica se existe uma determinada string numa dada AVL */
Boolean existe_String(AVL a,void* c,int comp(void* a,void* b));
/**Função que faz a inserção na AVL, de um código c*/
AVL insereAVL (AVL a,void* c, int *cresceu,int comp(void* a,void* b));
/**Função que insere um código na sub-árvore esquerda*/
AVL insereEsquerda (AVL a,void* c, int *cresceu,int comp(void *,void*));
/**Função que insere um código na sub-árvore direita*/
AVL insereDireita (AVL a,void* c, int *cresceu,int comp(void *,void*));
#endif
