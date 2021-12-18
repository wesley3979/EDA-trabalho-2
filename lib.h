#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#define FALSE           0
#define TRUE            1

#define ordem 2
#define maximo (ordem*2)
typedef struct pagina* Tpagina;
typedef struct paginaCliente* TpaginaCliente;
typedef struct paginaPedido* TpaginaPedido;


typedef struct{
  int chave;
} Tregistro;

typedef struct{
	char cpf[11];
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

typedef struct pagina{
  int n;
  Tregistro registro[maximo];
  Tpagina folha[maximo + 1];
};

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

// Funções referentes a uma arvore b de numeros inteiros
Tregistro* buscar(int, Tpagina );
void insere_na_pagina(Tpagina, Tregistro, Tpagina );
short insere_rec(Tregistro, Tpagina, Tregistro *, Tpagina *);
Tpagina insere(Tregistro, Tpagina);
void imprime(Tpagina, int);

//Funções referentes a uma arvore b do tipo de dado Cliente


//Funções referentes a uma arvore b do tipo de dado Pedido
// (Fazer primeiro essa, pois é mais simples, já que só trabalharemos com números inteiros)





