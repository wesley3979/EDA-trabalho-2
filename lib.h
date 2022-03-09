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
	int descProduto;
	int status;
	int idCliente; 
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
void insere_cliente_na_pagina(TpaginaCliente, Tcliente, TpaginaCliente );
short insere_rec_cliente(Tcliente, TpaginaCliente, Tcliente *, TpaginaCliente *);
TpaginaCliente insereCliente(Tcliente, TpaginaCliente);
void imprimeCliente(TpaginaCliente, int);

//Funções referentes a uma arvore b do tipo de dado Pedido
void imprimePedidoPorIdCliente(TpaginaPedido, int, int);
TpaginaPedido inserePedido(Tpedido, TpaginaPedido);
short insere_rec_pedido(Tpedido, TpaginaPedido, Tpedido *, TpaginaPedido *);
void insere_pedido_na_pagina(TpaginaPedido , Tpedido, TpaginaPedido);
short atualizaPedido(int, int, int, TpaginaPedido);





