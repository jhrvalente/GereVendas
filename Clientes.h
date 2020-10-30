#ifndef Clientes_h 
#define Clientes_h

typedef struct cliente *Cliente;
typedef struct cat* Cat_Cliente;

/* Função responsável por criar uma estrutura com o código do cliente, retornando um apontador para essa estrutura */
Cliente criaCliente(char* );
/** Função que verifica se o cliente existe no catalogo de clientes. */
Boolean existe_ClienteCat(Cat_Cliente, Cliente );
/* Função que dado um cliente retorna o código desse cliente */
char* getCodCliente(Cliente );
/** Função que inicializa a estrutura do catalogo */
Cat_Cliente inicia_CatalogoC(void);
/**Função que insere na estrutura cat. A estrutura cat contém um array de apontadores para avls.*/
Cat_Cliente insereCatC(Cat_Cliente ,Cliente );
/** Função que retorna o total de clientes existente na estrutura. */
int totalClientes(Cat_Cliente );
/**Função que indica o total de clientes começados por uma certa letra. */
int totalClientesLetra(Cat_Cliente , char );
/** Função que liberta a memória utilizada pelo catalogo de clientes. */
void removeCatClientes(Cat_Cliente );


#endif