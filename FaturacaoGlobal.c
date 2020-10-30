#include <stdio.h>
#include "Boolean.h"
#include "avl.h"
#include "listaStrings.h"
#include "FaturacaoGlobal.h"
#include <string.h>
#include <stdlib.h>


/*Struct Venda*/

typedef struct vend{
	int nVendas,quantN,quantP;
	double receitasN,receitasP;
}vnd;

Venda criaVenda(char* NP,double preco,int quantdd){
	Venda v=malloc(sizeof(struct vend));
	if(NP[0]=='N'){
		v->quantN=quantdd;
		v->quantP=0;
		v->receitasP=0;
		v->receitasN=preco*quantdd;
	}
	else {
		v->quantP=quantdd;
		v->quantN=0;
		v->receitasN=0;
		v->receitasP=preco*quantdd;
	}
	v->nVendas=1;
	return v;
}

void removeVenda(Venda v){
	free(v);
}

Venda addVenda(Venda v,Venda aux){
	v->nVendas+=1;
	v->quantN+=aux->quantN;
	v->quantP+=aux->quantP;
	v->receitasP+=aux->receitasP;
	v->receitasN+=aux->receitasN;
	return v;
}

Venda cloneVenda(Venda v){
	Venda new=malloc(sizeof(struct vend));
	new->nVendas=v->nVendas;
	new->quantN=v->quantN;
	new->quantP=v->quantP;
	new->receitasP=v->receitasP;
	new->receitasN=v->receitasN;
	return new;
}


/*Produto*/

typedef struct prod{
	char* produto;
	int comprou_um,comprou_dois,comprou_tres;
}ProdF;


ProdVenda criaProdVenda(char* p){
	ProdVenda pr=malloc(sizeof(struct prod));
	pr->comprou_um=0;
	pr->comprou_dois=0;
	pr->comprou_tres=0;
	pr->produto=malloc(strlen(p)+1);
	strcpy(pr->produto,p);
	return pr;
}

void removeProdVenda(ProdVenda p){
	free(p->produto);
	free(p);
}

ProdVenda cloneProd(ProdVenda p){
	ProdVenda new=malloc(sizeof(struct prod));
	new->comprou_um=p->comprou_um;
	new->comprou_dois=p->comprou_dois;
	new->comprou_tres=p->comprou_tres;
	new->produto=malloc(strlen(p->produto)+1);
	strcpy(new->produto,p->produto);
	return new;
}

/*Struct Fatura*/

typedef struct fat{
	ProdVenda produto;
	int nVendas,quantTotal;
	double receitasTotal;
	Venda mesFilial[3][12];
}Fat;


Fatura initFatura(ProdVenda p){
	int i,j;
	Fatura fg=malloc(sizeof(struct fat));
	fg->produto=p;
	fg->nVendas=0;
	fg->quantTotal=0;
	fg->receitasTotal=0;
	for(i=0;i<3;i++)
		for(j=0;j<12;j++)
		fg->mesFilial[i][j]=NULL;
	return fg;
}


Fatura addFatura(Fatura fg,int mes,int filial,Venda v){
	if(filial==1) fg->produto->comprou_um=1;
	if(filial==2) fg->produto->comprou_dois=1;
	if(filial==3) fg->produto->comprou_tres=1;	
	if(fg->mesFilial[filial-1][mes-1]==NULL) {
		fg->mesFilial[filial-1][mes-1]=v;
		fg->nVendas+=1;
		fg->receitasTotal+=v->receitasP+v->receitasN;
		fg->quantTotal+=v->quantP+v->quantN;
	}
	else {
		fg->mesFilial[filial-1][mes-1]=addVenda(fg->mesFilial[filial-1][mes-1],v);
		fg->nVendas+=1;
		fg->receitasTotal+=v->receitasP+v->receitasN;
		fg->quantTotal+=v->quantP+v->quantN;
		removeVenda(v);
	}
	return fg;
}


double getReceitaN_MensalF(Fatura f,int mes, int filial){
	if(f->mesFilial[filial-1][mes-1]!=NULL) return f->mesFilial[filial-1][mes-1]->receitasN;
	else return 0;
}


double getReceitaP_MensalF(Fatura f,int mes, int filial){
	if(f->mesFilial[filial-1][mes-1]!=NULL) return f->mesFilial[filial-1][mes-1]->receitasP;
	else return 0;
}


int getQntN_MensalF(Fatura f,int mes, int filial){
	if(f->mesFilial[filial-1][mes-1]!=NULL) return f->mesFilial[filial-1][mes-1]->quantN;
	else return 0;
}


int getQntP_MensalF(Fatura f,int mes, int filial){
	if(f->mesFilial[filial-1][mes-1]!=NULL) return f->mesFilial[filial-1][mes-1]->quantP;
	else return 0;
}


int getNVendas_MensalF(Fatura f,int mes, int filial){
	if(f->mesFilial[filial-1][mes-1]!=NULL) return f->mesFilial[filial-1][mes-1]->nVendas;
	else return 0;
}


int getNVendas(Fatura f){
	return f->nVendas;
}


int getQuantF(Fatura f,int filial){
	int i,sum=0;
	for(i=0;i<12;i++)
		if(f->mesFilial[filial-1][i]!=NULL) sum+=f->mesFilial[filial-1][i]->quantN+f->mesFilial[filial-1][i]->quantP;
	return sum;
}


Fatura cloneFatura(Fatura f){
	int i,j;
	Fatura new=malloc(sizeof(struct fat));
	new->nVendas=f->nVendas;
	new->produto=cloneProd(f->produto);
	new->receitasTotal=f->receitasTotal;
	new->quantTotal=f->quantTotal;
	for(i=0;i<3;i++)
		for(j=0;j<12;j++){
			if(f->mesFilial[i][j]==NULL) new->mesFilial[i][j]=NULL;
			else new->mesFilial[i][j]=cloneVenda(f->mesFilial[i][j]);
		}
	return new;
}

void removeFatura(Fatura f){
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<12;j++)
			if(f->mesFilial[i][j]!=NULL) removeVenda(f->mesFilial[i][j]);
	removeProdVenda(f->produto);
	free(f);
}


/*Struct FaturacaoGlobal*/


typedef struct FatGlob{
	AVL catalogo[26];
}fGlobal;


FaturacaoGlobal initFatGlob(){
	int i;
	FaturacaoGlobal fg=malloc(sizeof(struct FatGlob));
	for(i=0;i<26;i++)
		fg->catalogo[i]=NULL;
	return fg;
}


/*Inserção*/

int compareFatura(void* arg1, void* arg2){
	Fatura f1,f2;
	f1=(Fatura) arg1;
	f2=(Fatura) arg2;
	return strcmp(f1->produto->produto,f2->produto->produto);
}


AVL srcAddAux(AVL a,ProdVenda p, int m, int f,Venda v){
	int comp;
	Fatura fat;
	fat=(Fatura) get(a);
	comp=strcmp(p->produto,fat->produto->produto);
	if (comp==0) a=set(a,(Fatura) addFatura(fat,m,f,v));
	if (comp>0) a=setDir(a,srcAddAux(getDir(a),p,m,f,v));
	if (comp<0) a=setEsq(a,srcAddAux(getEsq(a),p,m,f,v));
	return a;
}

FaturacaoGlobal searchAdd(FaturacaoGlobal a,ProdVenda p, int m, int f,Venda v){
	int l=p->produto[0]-65;
	a->catalogo[l]=srcAddAux(a->catalogo[l],p,m,f,v);
	removeProdVenda(p);
	return a;
}


FaturacaoGlobal insereF(FaturacaoGlobal fg,Fatura f){
	int i, cr=0;
	i=f->produto->produto[0]-65;
	fg->catalogo[i]=insereAVL(fg->catalogo[i],f,&cr,compareFatura);
	return fg;
}


Fatura leituraAux(AVL a,ProdVenda p){
	int cmp;
	Fatura aux;
	aux=(Fatura) get(a);
	cmp=strcmp(p->produto,aux->produto->produto);
	if(cmp>0) aux=leituraAux(getDir(a),p);
	if(cmp<0) aux=leituraAux(getEsq(a),p);
	return aux;
}


Fatura leituraProd(FaturacaoGlobal fg,ProdVenda p){
	int l=p->produto[0]-65;
	return cloneFatura(leituraAux(fg->catalogo[l],p));
}


Lista_Strings naoCompListaAux(Lista_Strings ls,AVL a){
	Fatura f;
	if(a!=NULL){	
		ls=naoCompListaAux(ls,getEsq(a));
		f=(Fatura) get(a);
		if((f->produto->comprou_um==0 && f->produto->comprou_dois==0 && f->produto->comprou_tres==0)) ls=insereLista_dim(ls,f->produto->produto);
		ls=naoCompListaAux(ls,getDir(a));
	}
	return ls;
}


Lista_Strings listaNaoComprados(FaturacaoGlobal fg){
	int i;
	Lista_Strings ls=initListaStrings_dim();
	for(i=0;i<26;i++)
	 	ls=naoCompListaAux(ls,fg->catalogo[i]);
	ls=atualizaIndices(ls);
	return ls;

}

Lista_Strings naoCompListaFAux(Lista_Strings ls,AVL a,int filial){
	Fatura f;
	if(a!=NULL){
		if(filial==1){	
			ls=naoCompListaAux(ls,getEsq(a));
			f=(Fatura) get(a);
			if(f->produto->comprou_um==0) ls=insereLista_dim(ls,f->produto->produto);
			ls=naoCompListaAux(ls,getDir(a));
		}
		if(filial==2){	
			ls=naoCompListaAux(ls,getEsq(a));
			f=(Fatura) get(a);
			if(f->produto->comprou_dois==0) ls=insereLista_dim(ls,f->produto->produto);
			ls=naoCompListaAux(ls,getDir(a));
		}
		if(filial==3){	
			ls=naoCompListaAux(ls,getEsq(a));
			f=(Fatura) get(a);
			if(f->produto->comprou_tres==0) ls=insereLista_dim(ls,f->produto->produto);
			ls=naoCompListaAux(ls,getDir(a));
		}
	}
	return ls;
}

Lista_Strings listaNaoCompradosF(FaturacaoGlobal fg,int filial){
	int i;
	Lista_Strings ls=initListaStrings_dim();
	for(i=0;i<26;i++)
	 	ls=naoCompListaFAux(ls,fg->catalogo[i],filial);
	ls=atualizaIndices(ls);
	return ls;

}

int naoCompradosAux(AVL a){
	if(a==NULL) return 0;
	else {
		Fatura f=(Fatura) get(a);
		if((f->produto->comprou_um==0 && f->produto->comprou_dois==0 && f->produto->comprou_tres==0)) return 1 + naoCompradosAux(getEsq(a)) + naoCompradosAux(getDir(a));
		else return naoCompradosAux(getEsq(a)) + naoCompradosAux(getDir(a));
	}
}


int contaNaoComprados(FaturacaoGlobal fg){
	int i,sum=0;
	for(i=0;i!=26;i++){
		sum+=naoCompradosAux(fg->catalogo[i]);
	}
	return sum;
}

double totIntMesAux(AVL a,int mesU,int mesD){
	int i;
	double sum=0;
	if(a!=NULL){
		Fatura f=(Fatura) get(a);
		for(i=mesU-1;i<mesD;i++){
			if(f->mesFilial[0][i]!=NULL){
				sum+=f->mesFilial[0][i]->receitasN;
				sum+=f->mesFilial[0][i]->receitasP;
			}
			if(f->mesFilial[1][i]!=NULL){
				sum+=f->mesFilial[1][i]->receitasN; 
				sum+=f->mesFilial[1][i]->receitasP; 
			}
			if(f->mesFilial[2][i]!=NULL){
				sum+=f->mesFilial[2][i]->receitasN;
				sum+=f->mesFilial[2][i]->receitasP;
			}
		}
		sum+=totIntMesAux(getDir(a),mesU,mesD);
		sum+=totIntMesAux(getEsq(a),mesU,mesD);
	}
	return sum;
}

double totalIntervaloMes(FaturacaoGlobal fg,int mes_u,int mes_d){
	int i,mes_inf,mes_sup;
	double sum=0;
	if(mes_u<mes_d){
		mes_inf=mes_u;
		mes_sup=mes_d;
	}
	else {
		mes_inf=mes_d;
		mes_sup=mes_u;
	}
	for(i=0;i<26;i++)
		sum+=totIntMesAux(fg->catalogo[i],mes_inf,mes_sup);
	return sum;
}


int vIntMesAux(AVL a,int mesU,int mesD){
	int i,sum=0;
	if(a!=NULL){
		Fatura f=(Fatura) get(a);
		for(i=mesU-1;i<mesD;i++){
			if(f->mesFilial[0][i]!=NULL){
				sum+=f->mesFilial[0][i]->nVendas;
			}
			if(f->mesFilial[1][i]!=NULL){
				sum+=f->mesFilial[1][i]->nVendas; 
			}
			if(f->mesFilial[2][i]!=NULL){
				sum+=f->mesFilial[2][i]->nVendas;
			}
		}
		sum+=vIntMesAux(getDir(a),mesU,mesD);
		sum+=vIntMesAux(getEsq(a),mesU,mesD);
	}
	return sum;
}


int vendasIntervaloMes(FaturacaoGlobal fg,int mes_u,int mes_d){
	int i,mes_inf,mes_sup,sum=0;
	if(mes_u<mes_d){
		mes_inf=mes_u;
		mes_sup=mes_d;
	}
	else {
		mes_inf=mes_d;
		mes_sup=mes_u;
	}
	for(i=0;i<26;i++)
		sum+=vIntMesAux(fg->catalogo[i],mes_inf,mes_sup);
	return sum;
}


void freeAux(AVL a){
	if(a!=NULL){
		freeAux(getEsq(a));
		freeAux(getDir(a));
		removeFatura((Fatura) get(a));
		free(a);
	}
}

void removeFaturacaoGlobal(FaturacaoGlobal fg){
	int i;
	for(i=0;i<26;i++)
		if(fg->catalogo[i]!=NULL) freeAux(fg->catalogo[i]);
	free(fg);
}








typedef struct aux{
	Fatura* lista;
	int quantos,tam,lim;
}*NMais;



NMais initNMais(int limite){
	NMais novo=malloc(sizeof(struct aux));	
	novo->lista=malloc(sizeof(Fatura)*1024);
	novo->quantos=0;
	novo->lim=limite;
	novo->tam=1024;
	return novo;
}

NMais insereNMais(NMais nm,Fatura f){
	if(nm->quantos==nm->tam){
		nm->tam=nm->tam*2;
		nm->lista=realloc(nm->lista,sizeof(Fatura)*nm->tam);
	}
	nm->lista[nm->quantos]=f;
	nm->quantos+=1;
	return nm;
}

void removeNMais(NMais nm){
	free(nm->lista);
	free(nm);
}

Fatura* quickSort(Fatura* arr,int first,int last){
	int pivot,j,i;
	void* temp;
	if(first<last){
		pivot=first;
		i=first;
		j=last;
		while(i<j){
			while(i<last && arr[i]->quantTotal>=arr[pivot]->quantTotal)
				i+=1;
			while(arr[j]->quantTotal<arr[pivot]->quantTotal)
				j-=1;
			if(i<j){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
		temp=arr[pivot];
		arr[pivot]=arr[j];
		arr[j]=temp;
		arr=quickSort(arr,first,j-1);
		arr=quickSort(arr,j+1,last);
	}
	return arr;
}



NMais insertAux(AVL a,NMais lg){
	if(a!=NULL){
		lg=insereNMais(lg ,(Fatura) get(a));
		lg=insertAux(getDir(a),lg);
		lg=insertAux(getEsq(a),lg);
	}
	return lg;
}


Lista_Strings nMaisVendidos(FaturacaoGlobal fg, int n){
	int i;
	NMais nm;
	Lista_Strings ls;
	nm=initNMais(n);
	for(i=0;i<26;i++)
		nm=insertAux(fg->catalogo[i],nm);
	nm->lista=quickSort(nm->lista,0,nm->quantos-1);
	ls=initListaStrings(nm->lim);
	for(i=0;i<nm->lim;i++)
		ls=insereLista(ls,nm->lista[i]->produto->produto);
	ls=setPageSize(ls,10);
	ls=atualizaIndices(ls);
	removeNMais(nm);
	return ls;
}
