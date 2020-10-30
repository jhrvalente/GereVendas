#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"
#include "avl.h"
#include "Produtos.h"
#include "Clientes.h"
#include "listaStrings.h"
#include "filial.h"

#define PAGESIZE 20 

/* Estrutura que representa um produto */
struct prodF{ 
	Produto Produto;
	int qt;
	float preco;
	char tipoVenda;
};

/* Estrutura que representa um cliente */
struct clienteFil{
	Cliente clienteF;
	int comprou;
	int tam;
	AVL mes[12];
};

/* Estrutura Filiais */
struct filial {
	AVL filial;
};

char* getCodClienteF(ClienteF cf){
	return getCodCliente(cf->clienteF);
}

int getComprou(ClienteF cf){
	return cf->comprou;
}

/* Função que retorna um cliente presente na estrutura clienteF*/
Cliente getClienteFil(ClienteF cf){
	return cf->clienteF;
}

/* Função que vai permitir fazer as comparações na AVL */
static int compara_ProdsF(void* a,void* b ) {
	Produto p1,p2;
	p1=(Produto)((ProdF) a)->Produto;
	p2=(Produto)((ProdF) b)->Produto;
    return (strcmp(getCodProd(p1),getCodProd(p2)));}

/* Função de comparação para a estrutura clienteF */
static int compara_ClientesF(void* a,void* b){
	Cliente c1,c2;
	c1=(Cliente)((ClienteF) a)->clienteF;
	c2=(Cliente)((ClienteF) b)->clienteF;
    return (strcmp(getCodCliente(c1),getCodCliente(c2)));
}
/* Função que criar uma estrutura clienteF */
ClienteF cria_clienteF(char* cliente){
	int i;
	ClienteF c=malloc(sizeof(struct clienteFil));
	c->clienteF=criaCliente(cliente);
	c->comprou=c->tam=0;
	for(i=0;i!=12;i++)
		c->mes[i]=NULL;
	return c;
}
/* Função que cria um prodf */
ProdF criar_ProdF(char* p,int qt,float preco,char tV){
	ProdF pf=malloc(sizeof(struct prodF));
	pf->Produto=criaProduto(p);
	pf->qt=qt;
	pf->preco=preco;
	pf->tipoVenda=tV;
	return pf;
}

/* Função que insere um cliente na avl de clientes */
Filial insereCliente(Filial f,ClienteF c){
	int cr=0;
	f->filial=insereAVL(f->filial,c,&cr,compara_ClientesF);
	return f;
}


/* Função que insere produtos repetidos */
static AVL alteraProd(AVL a,ProdF pf,int comp(void* a,void* b)){
	int cmp;
	if(a!=NULL){
		cmp=comp(pf,(ProdF)get(a));
		if(cmp<0) a=setEsq(a,alteraProd(getEsq(a),pf,comp));
		else if(cmp>0) a=setDir(a,alteraProd(getDir(a),pf,comp));
			 else {
			 		((ProdF)get(a))->qt+=pf->qt;
		}    }
	return a;
	}

/* Função auxiliar que permite inserir um prodf na avl dos produtos */ 
static AVL insereProduto(AVL a,ClienteF cf,ProdF pf,int m,int comp1(void* a, void* b),int comp2(void* c,void* d)){
	int cr=0,cmp1;
	if(a!=NULL){
		cmp1=comp1(cf,(ClienteF)get(a));
		if(cmp1<0) a=setEsq(a,insereProduto(getEsq(a),cf,pf,m,comp1,comp2));
		else if(cmp1>0) a=setDir(a,insereProduto(getDir(a),cf,pf,m,comp1,comp2));
			 else {
			 	((ClienteF) get(a))->comprou=1;
			 	if(getBool(existe_String(((ClienteF) get(a))->mes[m-1],pf,compara_ProdsF))==True) ((ClienteF) get(a))->mes[m-1]=alteraProd(((ClienteF) get(a))->mes[m-1],pf,comp2);
			    ((ClienteF) get(a))->mes[m-1]=insereAVL(((ClienteF) get(a))->mes[m-1],pf,&cr,comp2);
			 }
			}
	return a;
}

/* Função que permite inserir um produto no modulo da filial */
Filial insereProd(Filial f,ClienteF cf,ProdF pf,int m){
	f->filial=insereProduto(f->filial,cf,pf,m,compara_ClientesF,compara_ProdsF);
	return f;
}

/* Função que inicializa uma estrutura filial */
Filial init_filial(){
	Filial f=malloc(sizeof(struct filial));
	f->filial=NULL;
	return f;
}

static void removeAvlProds(AVL a){
	ProdF p;
	if(a!=NULL){
		p=(ProdF)get(a);
		free(p->Produto);
		free(p);
		removeAvlProds(getEsq(a));
		removeAvlProds(getDir(a));
	}
}

static void removeAvlClientes(AVL c){
	ClienteF cf;
	int i;
	if(c!=NULL){
		cf=(ClienteF)get(c);
		for(i=0;i!=12;i++)
			removeAvlProds(cf->mes[i]);
		free(cf);
		removeAvlClientes(getEsq(c));
		removeAvlClientes(getDir(c));
	}
}

void removeFilial(Filial f1,Filial f2,Filial f3){
		 if(f1!=NULL) {removeAvlClientes(f1->filial);free(f1);}
		 if(f2!=NULL) {removeAvlClientes(f2->filial);free(f2);}
		 if(f3!=NULL) {removeAvlClientes(f3->filial);free(f3);}
}

/* QUERIE 7*/

/* Estrutura que guarda os clientes que realizaram compras em todas as filiais */
typedef struct todasFiliais
{
	int tam;
	AVL todasFil;
}*TodasFiliais;


/* Função que inicializa a estrutura todasFiliais */
TodasFiliais init_TodasFiliais(){
	TodasFiliais tf=malloc(sizeof(struct todasFiliais));
	tf->todasFil=NULL;
	tf->tam=0;
	return tf;
}
/* Função auxiliar que percorre o catalogo de clientes e insere no conjunto de clientes */
static Lista_Strings percorreCatalogoCFilial(Lista_Strings cjc,AVL a){
	if(a!=NULL){
		cjc=percorreCatalogoCFilial(cjc,getEsq(a));
		cjc=insereLista(cjc,getCodClienteF((ClienteF)get(a)));
		cjc=percorreCatalogoCFilial(cjc,getDir(a));
	}
	return cjc;
}
/* Função responsável por fazer a inserção no conjunto de clientes */
Lista_Strings leTodosClientesFilial(AVL clientes,int tam){
	Lista_Strings cjc=initListaStrings(tam);
	cjc=percorreCatalogoCFilial(cjc,clientes);
	cjc=atualizaIndices(cjc);
	return cjc;
}

/* QUERIE 7 (Clientes que compraram em todas as filiais) */
static TodasFiliais compTodas(TodasFiliais tf,AVL a,AVL b,AVL c){
	int cr=0;
	if(a!=NULL){
		ClienteF a2,b2,c2;
		a2=get(a);  b2=get(b);  c2=get(c);
		if(a2->comprou==1&&b2->comprou==1&&c2->comprou==1) {tf->tam+=1;tf->todasFil=insereAVL(tf->todasFil,get(a),&cr,compara_ClientesF);}
		tf=compTodas(tf,getEsq(a),getEsq(b),getEsq(c));
		tf=compTodas(tf,getDir(a),getDir(b),getDir(c));
	}
	return tf;
}

/* Função que carrega um conjunto de clientes, neste caso os que compraram em todas as filiais. */
Lista_Strings carregaConjTF(Filial f1,Filial f2,Filial f3){
	Lista_Strings cjc;
	TodasFiliais tf=init_TodasFiliais();
	tf=compTodas(tf,f1->filial,f2->filial,f3->filial);
	cjc=leTodosClientesFilial(tf->todasFil,tf->tam+=1);
	return cjc;
}

/* QUERIE 9 */

/* Criar conjunto de Produtos filial */

/* Função auxiliar que percorre o catalogo de clientes e insere no conjunto de clientes */
static Lista_Strings percorreCatalogoPFilial(Lista_Strings cjc,AVL a){
	ProdF cf;
	if(a!=NULL){
	    cf=((ProdF)get(a));
		cjc=insereLista(cjc,getCodProd(cf->Produto));
		cjc=percorreCatalogoPFilial(cjc,getEsq(a));
		cjc=percorreCatalogoPFilial(cjc,getDir(a));
	}
	return cjc;
}

/* Função responsável por fazer a inserção no conjunto de clientes */
Lista_Strings leTodosProdsFilial(AVL prods,int tam){
	Lista_Strings cjc=initListaStrings(tam);
	cjc=percorreCatalogoPFilial(cjc,prods);
	cjc=atualizaIndices(cjc);
	return cjc;
}

typedef struct maisComprados{
	int tam;
	AVL avl;
}*MaisComprados;

/* Função que inicializa a estrutura querie 9 */
MaisComprados initQ9(){
	MaisComprados q9=malloc(sizeof(struct maisComprados));
	q9->avl=NULL;
	q9->tam=0;
	return q9;
}
/* Função de comparação para inteiros. */
static int comp_inteiros(void* x,void* y){
	int i1=((ProdF) x)->qt;
	int i2=((ProdF) y)->qt;
	if(i1<i2) return 1;
	else if(i1>i2) return (-1);
	     else return 0;
}
/* Função que percorre a AVL e insere na AVL nova (comparando por quantidade)*/
static AVL percorreToda(AVL a,AVL nova,int *tam){
	int cr=0;
	if(a!=NULL){
		nova=percorreToda(getEsq(a),nova,tam);
		nova=percorreToda(getDir(a),nova,tam);
		(*tam)++;
		if(getBool(existe_String(nova,get(a),compara_ProdsF))==True) {nova=alteraProd(nova,get(a),compara_ProdsF);(*tam)--;}
		nova=insereAVL(nova,get(a),&cr,comp_inteiros);
	}
	return nova;
}
/* Função que calcula a querie 9 */
static MaisComprados prodsMaisComprados(MaisComprados q9,Filial filial,ClienteF cf,int m){
	int tam=0;
	AVL aux=percorreAVL(filial->filial,cf,compara_ClientesF);
	ClienteF c=(ClienteF)get(aux);
	q9->avl=percorreToda(c->mes[m-1],q9->avl,&tam);
	q9->tam+=tam;
	return q9;
}

/* Função que carrega o conjunto de clientes, com todos os clientes que respeitam a querie 9 */
Lista_Strings carregaConjQ9(Filial f1,Filial f2,Filial f3,ClienteF cf,int m,Lista_Strings cc){
	MaisComprados q9;
	q9=initQ9();
	q9=prodsMaisComprados(q9,f1,cf,m);
	q9=prodsMaisComprados(q9,f2,cf,m);
	q9=prodsMaisComprados(q9,f3,cf,m);
	cc=leTodosProdsFilial(q9->avl,q9->tam);
	return cc;
}

/* QUERIE 8 */

/* Estrutura que contem a avl com os produtos comprados em modo N ou P, para o respetivo cliente. */
typedef struct comprasCliente{
	int tamn,tamp;
	AVL avln;
	AVL avlp;
}*ComprasCliente;

ComprasCliente initQ8(){
	ComprasCliente q8=malloc(sizeof(struct comprasCliente));
	q8->avln=NULL;q8->avlp=NULL;
	q8->tamn=q8->tamp=0;
	return q8;
}
/* Se o prodF existir na avl retorna 'N' ou 'P', conforme o tipo de venda. Retorna NULL caso não exista na AVL. */
static char existeProdF(ClienteF cf,ProdF pf,int comp()){
	int i;
	AVL aux=NULL;
	for(i=0;i!=12;i++){
		aux=percorreAVL(cf->mes[i],pf,comp);
		if(aux==NULL) ;
		else return ((ProdF)get(aux))->tipoVenda;
	}
	return '\0';
}
/* Função que resolve a querie 8*/
static ComprasCliente querie8(AVL a,ComprasCliente q8,ProdF pf,int comp1()){
	int cr=0;
	if(a!=NULL){
		if(existeProdF((ClienteF)get(a),pf,compara_ProdsF)=='N')  {q8->avln=insereAVL(q8->avln,(ClienteF)get(a),&cr,comp1);q8->tamn+=1;}
		if(existeProdF((ClienteF)get(a),pf,compara_ProdsF)=='P')  {q8->avlp=insereAVL(q8->avlp,(ClienteF)get(a),&cr,comp1);q8->tamp+=1;} 
		q8=querie8(getEsq(a),q8,pf,comp1);
		q8=querie8(getDir(a),q8,pf,comp1);
	}
	return q8;
}
/* Função que carrega a estrutura ComprasCliente */
ComprasCliente comprasNPclientes(Filial f,ComprasCliente cc,ProdF pf){
	cc=querie8(f->filial,cc,pf,compara_ProdsF);
	return cc;
}

Lista_Strings comprasN(Lista_Strings lst,Filial f1,Filial f2,Filial f3,int fil,ProdF pf,int *tam){
	ComprasCliente cc; cc=initQ8();
	if(fil==1)cc=comprasNPclientes(f1,cc,pf);
	if(fil==2)cc=comprasNPclientes(f2,cc,pf);
	if(fil==3)cc=comprasNPclientes(f3,cc,pf);
	lst=leTodosClientesFilial(cc->avln,cc->tamn);
	lst=atualizaIndices(lst);
	*tam=cc->tamn;
	return lst;
}

Lista_Strings comprasP(Lista_Strings lst,Filial f1,Filial f2,Filial f3,int fil,ProdF pf,int *tam){
	ComprasCliente cc;cc=initQ8();
	if(fil==1)cc=comprasNPclientes(f1,cc,pf);
	if(fil==2)cc=comprasNPclientes(f2,cc,pf);
	if(fil==3)cc=comprasNPclientes(f3,cc,pf);
	lst=leTodosClientesFilial(cc->avlp,cc->tamp);
	lst=atualizaIndices(lst);
	*tam=cc->tamp;
	return lst;
}

/* QUERIE 5 */

/* Estrutura que guarda os valores referentes ao numero de compras mensais por filial. */
struct tabcompras{
	int qtMes1[12],qtMes2[12],qtMes3[12];
};

/* Get's para a estrutura tabcompras */
int getQTmes1(TabCompras q5,int i){
	return q5->qtMes1[i];
}

int getQTmes2(TabCompras q5,int i){
	return q5->qtMes2[i];
}

int getQTmes3(TabCompras q5,int i){
	return q5->qtMes3[i];
}
/* Função que retorna o tamanho da avl que contem todos os clientes que compraram em todas as filiais. */
int getTamCompTodas(TodasFiliais tf){
	return tf->tam;
}

/* Soma as quantidades de produtos comprados na avl */
static int somaQtAvls(AVL a){
	if(a!=NULL){
		ProdF pf=get(a);
		return pf->qt+somaQtAvls(getEsq(a))+somaQtAvls(getDir(a));
	}
	else return 0;}
/* Inicializa a estrutura TabCompras */
TabCompras initQ5(){
	TabCompras q5=malloc(sizeof(struct tabcompras));
	int j;
	for(j=0;j!=12;j++){
		q5->qtMes1[j]=0;
		q5->qtMes2[j]=0;
		q5->qtMes3[j]=0;
	}
	return q5;
}
/* Função que resolve a querie 5 */
TabCompras querie5(Filial f1,Filial f2,Filial f3,ClienteF cf){
	ClienteF c1,c2,c3;
	int i;
	TabCompras q5=initQ5();
	c1=(ClienteF)get(percorreAVL(f1->filial,cf,compara_ClientesF));
	c2=(ClienteF)get(percorreAVL(f2->filial,cf,compara_ClientesF));
	c3=(ClienteF)get(percorreAVL(f3->filial,cf,compara_ClientesF));
	for(i=0;i!=12;i++){
		q5->qtMes1[i]+=somaQtAvls(c1->mes[i]);
		q5->qtMes2[i]+=somaQtAvls(c2->mes[i]);
		q5->qtMes3[i]+=somaQtAvls(c3->mes[i]);
	}
	return q5;
}

/* QUERIE 11 */
struct tresMaisCaros{
	double gastos[3];
	Produto pmaiores[3];
};


Produto getMaiores1(TMCaros tmc){
	return tmc->pmaiores[0];
}

Produto getMaiores2(TMCaros tmc){
	return tmc->pmaiores[1];
}

Produto getMaiores3(TMCaros tmc){
	return tmc->pmaiores[2];
}

/* Calcula o tamanho da avl presente na estrutura ComprasCliente */
int getTamN(ComprasCliente cc){
	return cc->tamn;
}
/* Calcula o tamanho da avl presente na estrutura ComprasCliente */
int getTamP(ComprasCliente cc) {return cc->tamp;}

TMCaros init_tresmaiscaros(){
	TMCaros tmc=malloc(sizeof(struct tresMaisCaros));
	return tmc;
}
static TMCaros procuraTMC(TMCaros tmc,AVL a){
	if(a!=NULL){
		ProdF pf=(ProdF) get(a);
		double gasto;
		gasto=pf->qt*pf->preco;
		if(tmc->gastos[0]<gasto) {tmc->gastos[2]=tmc->gastos[1];tmc->gastos[1]=tmc->gastos[0];tmc->gastos[0]=gasto;
		                           tmc->pmaiores[2]=tmc->pmaiores[1];tmc->pmaiores[1]=tmc->pmaiores[0];tmc->pmaiores[0]=pf->Produto;}
		else if(tmc->gastos[1]<gasto) {tmc->gastos[2]=tmc->gastos[1];tmc->gastos[1]=gasto;
		                           tmc->pmaiores[2]=tmc->pmaiores[1];tmc->pmaiores[1]=pf->Produto;}
		     else if(tmc->gastos[2]<gasto) {tmc->gastos[2]=gasto;tmc->pmaiores[2]=pf->Produto;}
		tmc=procuraTMC(tmc,getEsq(a));
		tmc=procuraTMC(tmc,getDir(a));
	}
	return tmc;
}

TMCaros maisGastos(Filial f1,Filial f2,Filial f3,TMCaros tmc,ClienteF cf) {
	int j;
	AVL aux1=NULL,aux2=NULL,aux3=NULL;
	aux1=percorreAVL(f1->filial,cf,compara_ClientesF);
	aux2=percorreAVL(f2->filial,cf,compara_ClientesF);
	aux3=percorreAVL(f3->filial,cf,compara_ClientesF);
	cf=(ClienteF)get(aux1);
	for(j=0;j!=12;j++)
		tmc=procuraTMC(tmc,cf->mes[j]);
	cf=(ClienteF)get(aux3);
	for(j=0;j!=12;j++)
		tmc=procuraTMC(tmc,cf->mes[j]);
	cf=(ClienteF)get(aux2);
	for(j=0;j!=12;j++)
		tmc=procuraTMC(tmc,cf->mes[j]);
		
	return tmc;
}


/* Querie 12*/

typedef struct semCompras{
	int n;
}*SemCompras;

static SemCompras init_Sc(){
	SemCompras sc=malloc(sizeof(struct semCompras));
	sc->n=0;
	return sc;
}

static SemCompras zeroCompras(SemCompras sc,AVL f1,AVL f2,AVL f3){
	if(f1!=NULL){
		if((((ClienteF)get(f1))->comprou)==0&&((((ClienteF)get(f2))->comprou)==0)&&(((ClienteF)get(f3))->comprou)==0) (sc->n)++;
		sc=zeroCompras(sc,getEsq(f1),getEsq(f2),getEsq(f3));
		sc=zeroCompras(sc,getDir(f1),getDir(f2),getDir(f3));
	}
	return sc;
}

int getNuncaComprou(Filial f1,Filial f2,Filial f3){
	SemCompras sc;
	int i=0;
	sc=init_Sc();
	sc=zeroCompras(sc,f1->filial,f2->filial,f3->filial);
	i=sc->n;
	free(sc);
	return i;
}