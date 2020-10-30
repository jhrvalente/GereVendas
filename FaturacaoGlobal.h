#ifndef FaturacaoGlobal_h 
#define FaturacaoGlobal_h

typedef struct vend* Venda;
typedef struct prod* ProdVenda;
typedef struct fat* Fatura;
typedef struct FatGlob* FaturacaoGlobal;

/*Dada a informação de N ou P, o preço e quantidade comprada, cria uma estrutura Venda*/
Venda criaVenda(char*,double,int);
/*Dada uma String cria uma estrutura ProdVenda*/
ProdVenda criaProdVenda(char*);
/*Inicia a estrutura Fatura. Deve ser passado como argumento um ProdVenda*/
Fatura initFatura(ProdVenda );
/*Inicia a estrutura FaturacaoGlobal*/
FaturacaoGlobal initFatGlob(void);
/*Dada um ProdVenda, um mês e uma filial, adiciona à FaturacaoGlobal a informação da nova venda*/
FaturacaoGlobal searchAdd(FaturacaoGlobal,ProdVenda,int,int,Venda);
/*Dada uma Fatura, é inserida na FaturacaoGlobal*/
FaturacaoGlobal insereF(FaturacaoGlobal,Fatura);
/*Dado um Produto e uma FaturcaoGlobal devolve uma cópia da Fatura que lhe está associado*/
Fatura leituraProd(FaturacaoGlobal ,ProdVenda );
/*Dada uma Fatura, um mês e uma filial devolve quanto foi faturado em N nesse mês, nessa filial*/
double getReceitaN_MensalF(Fatura ,int , int );
/*Dada uma Fatura, um mês e uma filial devolve quanto foi faturado em P nesse mês, nessa filial*/
double getReceitaP_MensalF(Fatura ,int , int );
/*Dada uma Fatura, um mês e uma filial devolve quanto foi vendido(quantidade) em N nesse mês, nessa filial*/
int getQntN_MensalF(Fatura ,int , int );
/*Dada uma Fatura, um mês e uma filial devolve quanto foi vendido(quantidade) em P nesse mês, nessa filial*/
int getQntP_MensalF(Fatura ,int , int );
/*Dada uma Fatura, um mês e uma filial devolve o número de vendas nesse mês, nessa filial*/
int getNVendas_MensalF(Fatura ,int , int );
/*Dada uma Fatura devolve o número de vendas total*/
int getNVendas(Fatura );
/*Dada uma Fatura e uma filial devolve a quantidade vendida nessa filial*/
int getQuantF(Fatura ,int);
/*Dada uma FaturacaoGlobal e dois meses, devolve o total faturado no intervalo desses dois meses*/
double totalIntervaloMes(FaturacaoGlobal ,int ,int );
/*Dada uma FaturacaoGlobal conta quantos produtos nunca foram comprados*/
int contaNaoComprados(FaturacaoGlobal );
/*Dada uma FaturacaoGlobal devolve uma lista com os produtos que nunca foram comprados*/
Lista_Strings listaNaoComprados(FaturacaoGlobal );
/*Dada uma FaturacaoGlobal e uma filial gera uma Lista de Strings com os produtos que não foram comprados nessa filial*/
Lista_Strings listaNaoCompradosF(FaturacaoGlobal ,int );
/*Dada uma FaturacaoGlobal e um N, gera uma lista com os N produtos mais vendidos*/
Lista_Strings nMaisVendidos(FaturacaoGlobal ,int);
/*Devolve o número total de vendas registadas num intervalo de meses*/
int vendasIntervaloMes(FaturacaoGlobal ,int ,int );
/*Liberta o espaço de memória alocada a uma Fatura*/
void removeFatura(Fatura );
/*Liberta o espaço de memória alocada a uma FaturacaoGlobal*/
void removeFaturacaoGlobal(FaturacaoGlobal );


#endif