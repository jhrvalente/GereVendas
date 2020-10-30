
all: GereVendas

GereVendas: Boolean.o avl.o Produtos.o Clientes.o listaStrings.o FaturacaoGlobal.o filial.o main.o 
	 gcc -Wall -O2 -ansi -pedantic Boolean.o avl.o Produtos.o Clientes.o listaStrings.o FaturacaoGlobal.o filial.o main.o -o GereVendas

Boolean.o: Boolean.c Boolean.h
	gcc -c -Wall -O2 -pedantic -ansi Boolean.c

avl.o: Boolean.h avl.h avl.c
	gcc -c -Wall -O2 -pedantic -ansi avl.c

Produtos.o: avl.h Boolean.h Produtos.h Produtos.c 
	gcc -c -Wall -O2 -pedantic -ansi Produtos.c

Clientes.o: avl.h Boolean.h Clientes.h Clientes.c
	gcc -c -Wall -O2 -pedantic -ansi Clientes.c

listaStrings.o: avl.h Boolean.h Produtos.h Clientes.h listaStrings.h listaStrings.c
	gcc -c -Wall -O2 -pedantic -ansi listaStrings.c

FaturacaoGlobal.o: avl.h Boolean.h Produtos.h Clientes.h listaStrings.h FaturacaoGlobal.h FaturacaoGlobal.c
	gcc -c -Wall -O2 -pedantic -ansi FaturacaoGlobal.c

filial.o :avl.h Boolean.h Produtos.h Clientes.h listaStrings.h FaturacaoGlobal.h filial.h filial.c
	gcc -c -Wall -O2 -pedantic -ansi filial.c

main.o :avl.h Boolean.h Produtos.h Clientes.h listaStrings.h FaturacaoGlobal.h filial.h main.c
	gcc -c -Wall -O2 -pedantic -ansi main.c

clean:
	rm -rf *.o
