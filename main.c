#include <stdio.h>
#include "Boolean.h"
#include "avl.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Produtos.h"
#include "listaStrings.h"
#include "Clientes.h"
#include "FaturacaoGlobal.h" 
#include "filial.h"



/** Função que verifica se a venda está correta */
Boolean validaVenda(Cat_Produto cp,Cat_Cliente cc,char linha[]){
  char cliente[64],produto[64],*tipoV;
  int preco,quantidade,mes,filial;
  Boolean b=initBool(),existeP=initBool(),existeC=initBool();
  strcpy(produto,strtok(linha," "));                  
  preco=atof(strtok(NULL," "));
  quantidade=atoi(strtok(NULL," "));
  tipoV=strtok(NULL," ");
  strcpy(cliente,strtok(NULL," "));
  mes=atoi(strtok(NULL," "));
  filial=atoi(strtok(NULL,"\r\n"));
  if(filial>3||filial<1||mes>12||mes<1||(*tipoV!='N'&&*tipoV!='P')||preco<0||preco>999.99||quantidade<=0||quantidade>200) return setBool(b,False);
  existeP=existe_Produto(cp,criaProduto(produto));
  existeC=existe_ClienteCat(cc,criaCliente(cliente));
  if(getBool(existeC)==False||getBool(existeP)==False) return setBool(b,False); 
  return setBool(b,True); 
}

void imprimeProds(ConjP cjp){
  char linha[128],*tok=NULL;
  int i,psize;
	PaginaP pag;
	tok=malloc(sizeof(char)*10);
	strcpy(tok,"next");
	pag=NULL;
  while(strcmp(tok,"quit")!=0){
		if(strcmp(tok,"next")==0) pag=nextPageP(cjp);
		if(strcmp(tok,"prev")==0) pag=prevPageP(cjp);
		if(strcmp(tok,"last")==0) pag=lastPageP(cjp);
		if(strcmp(tok,"first")==0) pag=firstPageP(cjp);
    psize=getPageSizeP(pag);
    for(i=0;i<psize;i++)
      printf("%s\n",getNextProdP(pag));
		puts("--next - Próxima Página; prev - Página Anterior;\n--first - Primeira Página;last - Última Página;\n--quit - Regressar ao menu.");
		if(fgets(linha,128,stdin)!=NULL) tok=strtok(linha,"\r\n");
	}
}

void imprimeLista(Lista_Strings lst){
  char linha[128],*tok=NULL;
  	int i,	psize;
	Pagina pag;
	pag=NULL;
  tok=malloc(sizeof(char)*10);
  strcpy(tok,"next");
  while(strcmp(tok,"quit")!=0){
		if(strcmp(tok,"next")==0) pag=nextPage(lst);
		if(strcmp(tok,"prev")==0) pag=prevPage(lst);
		if(strcmp(tok,"last")==0) pag=lastPage(lst);
		if(strcmp(tok,"first")==0) pag=firstPage(lst);
    psize=getPageSize(pag);
    for(i=0;i<psize;i++)
      printf("%s\n",getNextString(pag));
		puts("--next - Próxima Página; prev - Página Anterior;\n--first - Primeira Página;last - Última Página;\n--quit - Regressar ao menu.");
		if(fgets(linha,128,stdin)!=NULL) tok=strtok(linha,"\r\n");
	}
}

int imprimeResultadosQ5(TabCompras q5,ClienteF cf){
  int i;
  printf("\n\t\t*** Cliente-%s ***\n\n", getCodClienteF(cf));
  printf("Mes\tFilial 1\tFilial 2\tFilial 3\n");
  for(i=0;i!=12;i++){
    printf("%d\t   %d\t\t   %d\t\t   %d\n",i+1,getQTmes1(q5,i),getQTmes2(q5,i),getQTmes3(q5,i));
  }
  return 0;
}

void imprimeMaisVendidos(FaturacaoGlobal fg,Lista_Strings lst){
  char* tok,linha[128];
  Fatura f=NULL;
  Pagina pag=NULL;
  int i,psize=0;
  tok=malloc(sizeof(char)*10);
  strcpy(tok,"next");
  while(strcmp(tok,"quit")!=0){
    if(strcmp(tok,"next")==0) pag=nextPage(lst);
    if(strcmp(tok,"prev")==0) pag=prevPage(lst);
    if(strcmp(tok,"last")==0) pag=lastPage(lst);
    if(strcmp(tok,"first")==0) pag=firstPage(lst);
    psize=getPageSize(pag);     
    for(i=0;i<psize;i++){
      tok=getNextString(pag);
      f=leituraProd(fg,criaProdVenda(tok));
      printf("%s\n",tok);
      printf("Vendas:%d Filial 1:%d\tFilial 2:%d\tFilial 3:%d\n\n",getNVendas(f),getQuantF(f,1),getQuantF(f,2),getQuantF(f,3));
      } 
    puts("--next - Próxima Página; prev - Página Anterior;\n--first - Primeira Página;last - Última Página;\n--quit - Regressar ao menu.");
    if(fgets(linha,128,stdin)!=NULL) tok=strtok(linha,"\r\n");
  }
}




typedef struct files{
   char *fc;
   char *fp;
   char *fv;
} *FILES;



FILES init_f(){
  FILES fl=malloc(sizeof(struct files));
  fl->fc=NULL;
  fl->fp=NULL;
  fl->fv=NULL;
  return fl;
}
  


FILES query1(FILES files){
    char cmd[5];
    printf("Indique se pretende: \n");
    printf("1. Inserir nome dos ficheiros \n");
    printf("2. Nomes por omissão \n");
    files->fc=malloc(sizeof(char)*64);
    files->fp=malloc(sizeof(char)*64);
    files->fv=malloc(sizeof(char)*64);
    if(fgets(cmd,5,stdin)!=NULL){
      if(cmd[0]=='1') {
        printf("Indique o nome do ficheiro com os clientes \n");
          if(fgets(files->fc,64,stdin)!=NULL)  files->fc[strlen(files->fc)-1]='\0';
        printf("Indique o nome do ficheiro com os produtos \n");
          if(fgets(files->fp,64,stdin)!=NULL)  files->fp[strlen(files->fp)-1]='\0';
        printf("Indique o nome do ficheiro com as vendas \n");
          if(fgets(files->fv,64,stdin)!=NULL)  files->fv[strlen(files->fv)-1]='\0';
        }
       else {
            strcpy(files->fc,"Clientes.txt");
            strcpy(files->fp,"Produtos.txt");
            strcpy(files->fv,"Vendas_1M.txt");
        }}
     return files;
}



Cat_Cliente carregaCatClientes(Cat_Cliente cat_Clientes,char linha[],Filial f[],int *cc){
	char *token;
    token=strtok(linha,"\r\n");
    strcpy(token,linha); (*cc)++;
    cat_Clientes=insereCatC(cat_Clientes,criaCliente(token));
    f[0]=insereCliente(f[0],cria_clienteF(token));
    f[1]=insereCliente(f[1],cria_clienteF(token));
    f[2]=insereCliente(f[2],cria_clienteF(token)); 
    return cat_Clientes;
}


Cat_Produto carregaCatProdutos(Cat_Produto cat_Produtos,char linha[],int *cp,FaturacaoGlobal fg){
	  char *prod;
	  ProdVenda p;
	  Fatura ft;
      prod=strtok(linha,"\r\n");(*cp)++;
      cat_Produtos=insereCatP(cat_Produtos,criaProduto(prod));
      p=criaProdVenda(prod);
      ft=initFatura(p);
      fg=insereF(fg,ft); 
      return cat_Produtos;
}


FaturacaoGlobal carregaFF(Cat_Cliente cat_Clientes,Cat_Produto cat_Produtos,char linha[],Filial filial[],int *cv,int *cvv,FaturacaoGlobal fg){
		char linhaAux[128],*prod,*cliente,*np;
		ProdVenda pr;
		Venda v;
		int quant,mes,fil;
    Boolean val=initBool();
		double preco;
      	strcpy(linhaAux,linha); (*cv)++;
      	val=validaVenda(cat_Produtos,cat_Clientes,linha);
      	if(getBool(val)==True) {
        (*cvv)++;
        prod=strtok(linhaAux," ");
        preco=atof(strtok(NULL," "));
        quant=atoi(strtok(NULL," "));
        np=strtok(NULL," ");
        cliente=strtok(NULL," ");
        mes=atoi(strtok(NULL," "));
        fil=atoi(strtok(NULL,"\r\n"));
        pr=criaProdVenda(prod);
        v=criaVenda(np,preco,quant);
        fg=searchAdd(fg,pr,mes,fil,v);
        filial[fil-1]=insereProd(filial[fil-1],cria_clienteF(cliente),criar_ProdF(prod,quant,preco,np[0]),mes);
    }
    return fg;
}





int main(){
    static Cat_Cliente cat_Clientes;
    static Cat_Produto cat_Produtos;
    static FILES files;
    static Filial filial[3];
    static FaturacaoGlobal fg;
    static Lista_Strings lst=NULL,ls1=NULL,ls2=NULL,ls3=NULL;
    static TabCompras q5;
    static ConjP cjp;
    static Fatura fat;
    static TMCaros q11;
    static ProdVenda pv;
    static FILE *fv,*fp,*fc;
    static clock_t start, end;
    static double diff_t1,diff_t2;
    static int mes=0,mes2=0,n=0,fil=0,countCli,countProd,countVendas,countVendasVal,i,tam=0;
    static char linha[128],*token=NULL,*token2=NULL;
    
    filial[0]=filial[1]=filial[2]=NULL;

	/* INTERPRETADOR DE COMANDOS */     
	token=malloc(sizeof(char)*5);
	strcpy(token,"q1");
	while(strcmp(token,"quit")!=0){
     
 		 if(strcmp(token,"q")==0)   break;
  
 		 if(strcmp(token,"q1")==0){
         countCli=0;countProd=0;countVendas=0;countVendasVal=0;
    		 if(cat_Clientes!=NULL) removeCatClientes(cat_Clientes);
     		 if(cat_Produtos!=NULL) removeCatProds(cat_Produtos);
     	 	 if(fg!=NULL) removeFaturacaoGlobal(fg);
     		 removeFilial(filial[0],filial[1],filial[2]);
     		 files=init_f();
      		/* Opções da query 1*/
     		 query1(files);
        start = clock();
      		/* Inicialização dos modulos de dados */
     		cat_Produtos=initCatalogo(); 
     		cat_Clientes=inicia_CatalogoC(); 
     		fg=initFatGlob(); 
     		for(i=0;i!=3;i++) filial[i]=init_filial();
     		/* Carregar módulo de dados */
     		fc=fopen(files->fc,"r");
     		while(fgets(linha,128,fc)!=NULL)
     			cat_Clientes=carregaCatClientes(cat_Clientes,linha,filial,&countCli);
     
    		fp=fopen(files->fp,"r");
     		while(fgets(linha,128,fp)!=NULL) 
     			cat_Produtos=carregaCatProdutos(cat_Produtos,linha,&countProd,fg);
     
     		fv=fopen(files->fv,"r");
 	 		while(fgets(linha,128,fv)!=NULL)
    	 		fg=carregaFF(cat_Clientes,cat_Produtos,linha,filial,&countVendas,&countVendasVal,fg);
        
    		fclose(fc);fclose(fp);fclose(fv);
        end = clock();
    		/* Informações sobre os ficheiros lidos */
    		printf("Ficheiro de clientes lido: %s com %d linhas \n",files->fc,countCli);
   			printf("Ficheiro de produtos lido: %s com %d linhas \n",files->fp,countProd);
    		printf("Ficheiro de vendas lido: %s com %d linhas e %d linhas válidas \n\n",files->fv,countVendas,countVendasVal);
        printf("Tempo para carregar os módulos de dados = %.5f s\n",((double)(end - start))/1000000);
 		}
 			/* Execução da query 2 */
 		if(strcmp(token,"q2")==0){
 			printf("---------------------------------------------------------------------\n");
 			printf("Indique uma letra: \n");
 			if(fgets(linha,64,stdin)!=NULL) token=strtok(linha,"\n");
 			cjp=init_ConjP(getTamanho(cat_Produtos,token[0]-65));
     	cjp=leituraProdsLetra(cat_Produtos,token[0]);
 			imprimeProds(cjp);
 			printf("---------------------------------------------------------------------\n");
      removeConjP(cjp);
      	}


        /*Execução da Query 3*/
      if(strcmp(token,"q3")==0){
        printf("---------------------------------------------------------------------\n");
        printf("Indique um Produto: \n");
        if(fgets(linha,64,stdin)!=NULL) token=strtok(linha,"\n");
        pv=criaProdVenda(token);
        printf("Indique um Mês: \n");
        if(fgets(linha,64,stdin)!=NULL) mes=atoi(strtok(linha,"\n"));
        fat=leituraProd(fg,pv);
        printf("Valores Totais(t) ou Por Filiais(f): \n");
        if(fgets(linha,64,stdin)!=NULL) token2=strtok(linha,"\n");
        if(token2[0]=='f'){
          printf("Número de Vendas na Filial 1:%d\tFaturado na Filial 1, N:%f\tFaturado na Filial 1, P:%f\n",getNVendas_MensalF(fat,mes,1),getReceitaN_MensalF(fat,mes,1),getReceitaP_MensalF(fat,mes,1));
          printf("Número de Vendas na Filial 2:%d\tFaturado na Filial 2, N:%f\tFaturado na Filial 2, P:%f\n",getNVendas_MensalF(fat,mes,2),getReceitaN_MensalF(fat,mes,2),getReceitaP_MensalF(fat,mes,2));
          printf("Número de Vendas na Filial 3:%d\tFaturado na Filial 3, N:%f\tFaturado na Filial 3, P:%f\n",getNVendas_MensalF(fat,mes,3),getReceitaN_MensalF(fat,mes,3),getReceitaP_MensalF(fat,mes,3));}
        else 
          printf("Número de Vendas:%d\nTotal Faturado, N:%f\nTotal Faturado, P:%f\n", getNVendas_MensalF(fat,mes,1)+getNVendas_MensalF(fat,mes,2)+getNVendas_MensalF(fat,mes,3),getReceitaN_MensalF(fat,mes,1)+getReceitaN_MensalF(fat,mes,2)+getReceitaN_MensalF(fat,mes,3),getReceitaP_MensalF(fat,mes,1)+getReceitaP_MensalF(fat,mes,2)+getReceitaP_MensalF(fat,mes,3));
        printf("---------------------------------------------------------------------\n");
      }


      /*Execução da query 4*/
      if(strcmp(token,"q4")==0){
        printf("---------------------------------------------------------------------\n");
        printf("Valores Totais(t) ou Divididos por Filiais(f)\n"); 
        if(fgets(linha,64,stdin)!=NULL) token=strtok(linha,"\n");  
        if(token[0]=='f'){
          ls1=listaNaoCompradosF(fg,1);
          ls2=listaNaoCompradosF(fg,2);
          ls3=listaNaoCompradosF(fg,3);
          if(tamanhoLista(ls1)>0) {printf("\n\t\t***Filial 1***\n");printf("%d produtos não foram comprados\n",tamanhoLista(ls1));imprimeLista(ls1);}
          else {printf("\n\t\t***Filial 1***\n");printf("Todos os produtos foram comprados\n");}

          if(tamanhoLista(ls2)>0) {printf("\n\t\t***Filial 2***\n");printf("%d produtos não foram comprados\n",tamanhoLista(ls2));imprimeLista(ls2);}
          else {printf("\n\t\t***Filial 2***\n");printf("Todos os produtos foram comprados\n");}

          if(tamanhoLista(ls3)>0) {printf("\n\t\t***Filial 3***\n");printf("%d produtos não foram comprados\n",tamanhoLista(ls3));imprimeLista(ls3);}
          else {printf("\n\t\t***Filial 3***\n");printf("Todos os produtos foram comprados\n");}
          removeListaStrings(ls1);removeListaStrings(ls2);removeListaStrings(ls3);
        } 
        else{ 
          ls1=listaNaoComprados(fg);
          if(tamanhoLista(ls1)>0) {printf("%d produtos não foram comprados\n",tamanhoLista(ls1));imprimeLista(ls1);}
          else printf("Todos os produtos foram comprados\n");
          removeListaStrings(ls1);
        }
        
      }

   		 /* Execução da query 5*/
 		if(strcmp(token,"q5")==0){
			printf("---------------------------------------------------------------------\n");
	 		printf("Indique o cliente: \n");
			if(fgets(linha,128,stdin)!=NULL) token=strtok(linha,"\n");
	 		q5=querie5(filial[0],filial[1],filial[2],cria_clienteF(token));
	 		imprimeResultadosQ5(q5,cria_clienteF(token));
	 		printf("---------------------------------------------------------------------\n");
   		 }

       /*Execução da query 6*/
       if(strcmp(token,"q6")==0){
          printf("---------------------------------------------------------------------\n");
          printf("Indique um mês: \n");
          if(fgets(linha,128,stdin)!=NULL) mes=atoi(strtok(linha,"\n"));
          printf("Indique outro mês: \n");
          if(fgets(linha,128,stdin)!=NULL) mes2=atoi(strtok(linha,"\n"));
          printf("Total Faturado entre o mês %d e o mês %d: %f\nNúmero de Vendas:%d\n",mes,mes2,totalIntervaloMes(fg,mes,mes2),vendasIntervaloMes(fg,mes,mes2));
          printf("---------------------------------------------------------------------\n");
       }


    	/*Execução da query 7 */
    	 if(strcmp(token,"q7")==0){
    		printf("---------------------------------------------------------------------\n");
     		lst=carregaConjTF(filial[0],filial[1],filial[2]);
     		imprimeLista(lst);
    		printf("---------------------------------------------------------------------\n");
        removeListaStrings(lst);
 		}



 		/* Execução da query 8 */
 		if(strcmp(token,"q8")==0){
 			printf("---------------------------------------------------------------------\n");
 			printf("Indique a filial: \n");
    		if(fgets(linha,128,stdin)!=NULL) fil=atoi(strtok(linha,"\n"));
    		printf("Indique o Produto: \n");
    		if(fgets(linha,128,stdin)!=NULL) token=strtok(linha,"\n");
 			  printf("\n     *** Produto %s *** \n",token);
    		printf("Tipo da Compra N\n");
        start = clock();
        lst=initListaStrings_dim(); 
    		lst=comprasN(lst,filial[0],filial[1],filial[2],fil,criar_ProdF(token,0,0,'N'),&tam);
        end = clock();
    		printf("Número de clientes que compraram %d \n",tam);
 			  imprimeLista(lst);
        diff_t1 =((double)(end - start))/1000;
 		  	printf("\n     *** Produto %s *** \n",token);
   			printf("Tipo da Compra P\n"); 
        start=clock();
        lst=initListaStrings_dim();
    		lst=comprasP(lst,filial[0],filial[1],filial[2],fil,criar_ProdF(token,0,0,'N'),&tam);
    		printf("Número de clientes que compraram %d \n",tam);
 			  imprimeLista(lst);
        end=clock();
        diff_t2 = ((double)(end - start))/1000;
      printf("Tempo a executar a querie 8 = %.5f ms\n", (diff_t2+diff_t1));
 			printf("---------------------------------------------------------------------\n");
      removeListaStrings(lst);
		}



		/* Execução da query 9 */	
 		if(strcmp(token,"q9")==0){
 			 printf("---------------------------------------------------------------------\n");
    	 	 printf("Indique o mes: \n");
   			 if(fgets(linha,128,stdin)!=NULL) mes=atoi(strtok(linha,"\n"));
   			 printf("Indique o cliente: \n");
   			 if(fgets(linha,128,stdin)!=NULL) token=strtok(linha,"\n");
   			 printf("\n     *** Cliente %s *** \n",token);
   			 start=clock();
         lst=carregaConjQ9(filial[0],filial[1],filial[2],cria_clienteF(token),mes,lst);
   			 end=clock();
         imprimeLista(lst);
         diff_t1 =((double)end-start)/1000;
         printf("Tempo a executar a querie 9 = %.5f ms\n", diff_t1);
 			 printf("---------------------------------------------------------------------\n");
       removeListaStrings(lst);
 	 	}



        /**Execução da Query 10*/
        if(strcmp(token,"q10")==0){
           printf("---------------------------------------------------------------------\n");
          printf("Quantos produtos deseja visualizar:\n");
          if(fgets(linha,128,stdin)!=NULL) n=atoi(strtok(linha,"\n"));
          start=clock();
          lst=nMaisVendidos(fg,n);
          imprimeMaisVendidos(fg,lst);
          end=clock();
          removeListaStrings(lst);
          diff_t1 =((double)end-start)/1000;
           printf("Tempo a executar a querie 10 = %.5f ms\n", diff_t1);
          printf("---------------------------------------------------------------------\n");
        }



 		/* Execução da query 11 */
    if(strcmp(token,"q11")==0){ 
      printf("---------------------------------------------------------------------\n");
      printf("Indique o cliente: \n");
      if(fgets(linha,128,stdin)!=NULL) token=strtok(linha,"\n");
          printf("\n     *** Cliente %s *** \n",token);
          printf("3 produtos em que mais gastou dinheiro \n");
          start=clock();;q11=init_tresmaiscaros();
          q11=maisGastos(filial[0],filial[1],filial[2],q11,cria_clienteF(token)); 
          printf("%s \n",getCodProd(getMaiores1(q11)));
          printf("%s \n",getCodProd(getMaiores2(q11)));
          printf("%s \n",getCodProd(getMaiores3(q11)));
          end=clock();
          diff_t1 =((double)end-start)/1000;
           printf("Tempo a executar a querie 11 = %.5f ms\n", diff_t1);
          printf("---------------------------------------------------------------------\n");
          }

        /*Execução da Query 12*/
        if(strcmp(token,"q12")==0){
          printf("---------------------------------------------------------------------\n");
          start=clock();
          printf("Número de clientes que não efetuaram compras:  %d\n",getNuncaComprou(filial[0],filial[1],filial[2]));
          printf("Número de produtos que não foram comprados:  %d\n",contaNaoComprados(fg));
          end=clock();
          diff_t1 =((double)end-start)/1000;
          printf("Tempo a executar a querie 12 = %.5f ms\n", diff_t1);
          printf("---------------------------------------------------------------------\n");
        }  

	    /* Menu do interpretador de comandos */
      printf("Prima:\n'q1' - Recarregar os Ficheiros\n'q2' - Imprimir todos os Produtos começados pela mesma letra\n'q3' - Imprimir a faturação de um Produto num determinado mês\n'q4' - Imprimir os Códigos dos Produtos que não foram comprados \n'q5' - Criar tabela como o número total de produtos que um cliente comprou, mês a mês \n");
      printf("'q6' - Imprimir o total faturado num intervalo de meses \n'q7' - Imprimir os clientes que compraram em todas as filiais\n'q8' - Imprimir que clientes compraram um dado Produto numa dada filial\n");
      printf("'q9' - Imprimir os produtos comprados por um cliente num dado mês \n'q10' - Imprimir os N produtos mais vendidos\n'q11' - Imprimir os 3 produtos onde um cliente gastou mais dinheiro\n'q12' - Imprimir quantos clientes não compraram nada e quantos produtos não foram comprados \n'q' - para sair;\n");
	    if(fgets(linha,128,stdin)!=NULL) token=strtok(linha,"\n");
	    }
  	  return 0;
}
