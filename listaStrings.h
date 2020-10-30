#ifndef listaStrings_h 
#define listaStrings_h

typedef struct pag* Pagina;
typedef struct lstStr* Lista_Strings;

/*Inicia a estrutura Lista de Strings. O tamanho da lista deve ser pssado como argumento*/
Lista_Strings initListaStrings(int );
/*Insere uma String na Lista de Strings(com tamanho pré-definido)*/
Lista_Strings insereLista(Lista_Strings ,char* );
/*Inicia a estrutura Lista de Strings, sem tamanho pré-definido.*/
Lista_Strings initListaStrings_dim(void);
/*Insere uma String na Lista de Strings(sem tamanho pré-definido)*/
Lista_Strings insereLista_dim(Lista_Strings ,char* );
/*Atualiza os indices das páginas da lista. Esta função deve ser realizada, depois de realizadas todas as inserções.*/
Lista_Strings atualizaIndices(Lista_Strings );
/*Permite definir um novo tamanho de página*/
Lista_Strings setPageSize(Lista_Strings ,int );
/*Dada uma Lista de Strings, devolve a Página seguinte*/
Pagina nextPage(Lista_Strings );
/*Dada uma Lista de Strings, devolve a Página anterior*/
Pagina prevPage(Lista_Strings );
/*Dada uma Lista de Strings, devolve a primeira Página*/
Pagina firstPage(Lista_Strings );
/*Dada uma Lista de Strings, devolve a última Página*/
Pagina lastPage(Lista_Strings );
/*Dada uma página, devolve o seu tamanho*/
int getPageSize(Pagina );
/*Dada uma página, devolve a próxima String*/
char* getNextString(Pagina );
/*Dada uma Lista de Strings devolve o seu tamanho*/
int tamanhoLista(Lista_Strings );
/*Liberta o espaço de memória alocado para uma dada Página*/
void removePagina(Pagina );
/*Liberta o espaço de memória alocado para uma dada Lista de Strings*/
void removeListaStrings(Lista_Strings );



#endif