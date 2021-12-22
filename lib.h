#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define FALSE           0
#define TRUE            1

#define ordem 2
#define maximo (ordem*2)
typedef struct paginaCliente* TpaginaCliente;
typedef struct paginaPedido* TpaginaPedido;

typedef struct{
	int id;
	char cpf[12];
	char nome[80];
	char endereco[80];
} Tcliente;

typedef struct{
	int ordemServico;
	int quantidade;
	int descProduto; //{Banner = 1, Logo = 2 , Cracha = 3, Catalogo = 4, Outro = 5};
	int status; //{cancelado = 1, Entregue = 2 , Andamento = 3};
	char cpfCliente[11]; 
} Tpedido;

typedef struct paginaCliente{
  int n;
  Tcliente registroCliente[maximo];
  TpaginaCliente folhaCliente[maximo + 1];
};

typedef struct paginaPedido{
  int n;
  Tpedido registroPedido[maximo];
  TpaginaPedido folhaPedido[maximo + 1];
};

//ajustar menu
void menu();

//Funções referentes a uma arvore b do tipo de dado Cliente
Tcliente* buscarCliente(int, TpaginaCliente );
void insere_na_pagina(TpaginaCliente, Tcliente, TpaginaCliente );
short insere_rec_cliente(Tcliente, TpaginaCliente, Tcliente *, TpaginaCliente *);
TpaginaCliente insereCliente(Tcliente, TpaginaCliente);
void imprimeCliente(TpaginaCliente, int);

//Funções referentes a uma arvore b do tipo de dado Pedido
//(Fazer primeiro essa, pois é mais simples, já que só trabalharemos com números inteiros)

/*
Tpedido* buscar(int, TpaginaPedido );
void insere_na_pagina(TpaginaPedido, Tpedido, TpaginaPedido );
short insere_rec(Tpedido, TpaginaPedido, Tpedido *, TpaginaPedido *);
TpaginaPedido insere(Tpedido, TpaginaPedido);
void imprime(TpaginaPedido, int);
*/




