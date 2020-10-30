
typedef struct prodF *ProdF;
typedef struct clienteFil *ClienteF;
typedef struct filial *Filial;
typedef struct tabcompras *TabCompras;
typedef struct tresMaisCaros *TMCaros;

/* Função que inicializa a estrutura associada ao tipo Filial */
Filial init_filial();
/* Função que cria uma estrutura do tipo clienteF e inicializa todos os campos dessa estrutura, devolvendo um apontador para essa mesma estrutura. */
ClienteF cria_clienteF(char* cliente);
/* Função que insere um cliente numa determinada filial. */
Filial insereCliente(Filial f,ClienteF c);
/* Função que permite inserir um produto numa determinada filial. */
Filial insereProd(Filial f,ClienteF cf,ProdF pf,int m);
/* Função que cria uma estrutura do tipo ProdF, inicializa todos os seus campos e devolve um apontador para essa mesma estrutura. */
ProdF criar_ProdF(char* p,int qt,float preco,char tV);
/* Função que retorna um cliente presente numa estrutura do tipo clienteF*/
Cliente getClienteFil(ClienteF cf);
/* Função que carrega o conjunto de clientes que compraram em todas as filiais para uma lista de Strings. */
Lista_Strings carregaConjTF(Filial f1,Filial f2,Filial f3);
/* Função que carrega o conjunto de clientes associado à querie 9 */
Lista_Strings carregaConjQ9(Filial f1,Filial f2,Filial f3,ClienteF cf,int m,Lista_Strings cc);
/* Função que retorna uma lista de Strings com as compras do tipo "N" */
Lista_Strings comprasN(Lista_Strings lst,Filial f1,Filial f2,Filial f3,int fil,ProdF pf,int *tam);
/* Função que retorna uma lista de Strings com as compras do tipo "P" */
Lista_Strings comprasP(Lista_Strings lst,Filial f1,Filial f2,Filial f3,int fil,ProdF pf,int *tam);
/* Função que resolve a query 5 */
TabCompras querie5(Filial f1,Filial f2,Filial f3,ClienteF cf);
/* Função que retorna o número de compras relativo ao mês dado pelo índice i, na filial 1 */ 
int getQTmes1(TabCompras q5,int i);
/* Função que retorna o número de compras relativo ao mês dado pelo índice i, na filial 2 */ 
int getQTmes2(TabCompras q5,int i);
/* Função que retorna o número de compras relativo ao mês dado pelo índice i, na filial 3 */ 
int getQTmes3(TabCompras q5,int i);
/* Função que dada uma estrutura do tipo ClienteF retorna o código desse cliente */
char* getCodClienteF(ClienteF cf);
/* Função que inicializa uma estrutura do tipo tresMaisCaros. */
TMCaros init_tresmaiscaros();
/* Função que retorna o produto mais caro */
Produto getMaiores1(TMCaros tmc);
/* Função que retorna o 3º produto mais caro */
Produto getMaiores3(TMCaros tmc);
/* Função que retorna o 2º produto mais caro */
Produto getMaiores2(TMCaros tmc);
/* Função que retorna o valor gasto com o produto mais caro */
double getGastos1(TMCaros tmc);
/* Função que retorna o valor gasto com o 2º produto mais caro */
double getGastos2(TMCaros tmc);
/* Função que retorna o valor gasto com o 3º produto mais caro */
double getGastos3(TMCaros tmc);
/* Função que dado um cliente retorna um apontador para uma estrutura do tipo tresMaisCaros, com informação sobre os 3 produtos em que mais gastou dinheiro durante o ano.*/
TMCaros maisGastos(Filial f1,Filial f2,Filial f3,TMCaros tmc,ClienteF cf);
/*Função que, dadas as 3 filiais, conta quanto produtos não foram comprados nas 3*/
int getNuncaComprou(Filial ,Filial ,Filial );
/*Função que liberta o espaço de memória ocupada pela estrutura do tipo Filial */
void removeFilial(Filial f1,Filial f2,Filial f3);

