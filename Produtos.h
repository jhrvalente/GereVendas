#ifndef Produtos_h 
#define Produtos_h

typedef struct produto* Produto;
typedef struct catP* Cat_Produto;
typedef struct pagP* PaginaP;
typedef struct conjProds* ConjP;

/* Função que retorna o tamanho da AVL de produtos na posição n */
int getTamanho(Cat_Produto cp,int n);
/* Função responsável por criar uma estrutura com o código do produto, retornando um apontador para essa estrutura */
Produto criaProduto(char* );
/* Função que verifica se um determinado produto existe no catalogo de produtos */
Boolean existe_Produto(Cat_Produto, Produto);
/* Função que dado um produto retorna o código desse produto */
char* getCodProd(Produto );
/* Função que inicializa a estrutura do catalogo de produtos */
Cat_Produto initCatalogo(void);
/* Função que insere um produto no catálogo de produtos */
Cat_Produto insereCatP(Cat_Produto,Produto);
/* Função que indica o total de produtos existentes no catálogo de produtos */
int totalProdutos(Cat_Produto);
/* Função que retorna o número total de produtos que começam por uma determinada letra */
int totalProdutosLetra(Cat_Produto, char);
/* Função que liberta o espaço de memória ocupado pela estrutura do catálogo de produtos */
void removeCatProds(Cat_Produto);

/* Função que cria um conjunto de produtos com o tamanho parametrizado e devolve um apontador para essa estrutura. */
ConjP init_ConjP(int );
/* Função que dado um catálogo de produtos e uma letra, percorre a AVL de produtos corresponde a essa letra e insere esses produtos num conjunto de produtos. */
ConjP leituraProdsLetra(Cat_Produto ,char );
/* Função que atualiza os indices para a pagina anterior */
PaginaP prevPageP(ConjP );
/* Função que atualiza os indices para a próxima página */
PaginaP nextPageP(ConjP );
/* Função que atualiza os indices para a primeira página */
PaginaP firstPageP(ConjP );
/* Função que atualiza os indices para a ultima página */
PaginaP lastPageP(ConjP );
/* Função que retorna o código do Produto que está na posição index da Pagina */
char* getNextProdP(PaginaP );
/* Função que retorna o tamanho da página */
int getPageSizeP(PaginaP );
/*Função que liberta o espaço de memória ocupada pela estrutura do tipo PaginaP*/
void removePaginaP(PaginaP );
/*Função que liberta o espaço de memória ocupada pela estrutura do tipo ConjP*/
void removeConjP(ConjP );

#endif
