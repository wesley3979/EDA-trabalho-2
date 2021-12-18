#include "lib.h"

void menu(){
	int op, i;
	
	//--------- iniciando a estrutura --------------------//
    Tregistro valor;
    Tcliente novoCliente;
    Tpedido novoPedido;
	Tpagina pagina = 0;
    
    do{    
    //--------------- Exibir menu ---------------------//
        system("cls");
        puts("\n\t\t\t\tARVORE B - ORDEM 2\n");
        puts("\t1 - INSERIR ELEMENTO\n \t2  - IMPRIMIR ARVORE\n \t0  - SAIR");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op);//Escolha da Opção
        
        switch(op){
        //Opção de exibir lista
    		case 1:{
    			printf("Informe um elemento: ");
    			scanf("%d", &valor.chave);
    			pagina = insere(valor, pagina);
				break;
			}
    			
    		case 2: imprime(pagina,0); break;
    			
	    	default:
	    		puts("OPCAO INCORRETA,TENTAR NOVAMENTE.");break;
	      
	        }
		getch();
	}while(op!=0);
}


Tregistro* buscar(int chave, Tpagina a){ 
  long i = 0;
  if (a == NULL) 
  	return NULL;
  while (i < a->n && chave > a->registro[i].chave) 
  	i++;
  if (chave == a->registro[i].chave) 
  	return &a->registro[i];
  if (chave < a->registro[i].chave)
    return buscar(chave, a->folha[i]);
  else
    return buscar (chave, a->folha[i+1]);
}

void imprime(Tpagina p, int nivel){ 
  if (p == NULL) 
  	return;
  printf("Nivel %d : ", nivel);
  for (int i = 0; i < p->n; i++)
    printf("%d ", p->registro[i].chave);
  printf("\n");
  for (int i = 0; i <= p->n; i++)
    imprime(p->folha[i], nivel+1);
} 

void insere_na_pagina(Tpagina pag, Tregistro reg, Tpagina pag_dir)
{ 
  int i;
  for (i = pag->n; (i > 0) && (reg.chave < pag->registro[i-1].chave); i--){
    pag->registro[i] = pag->registro[i-1];
    pag->folha[i+1] = pag->folha[i];    
  }
  pag->registro[i] = reg;
  pag->folha[i+1] = pag_dir;
  pag->n++;
} 

short insere_rec(Tregistro reg, Tpagina pag, Tregistro *reg_retorno, Tpagina *pag_retorno)
{ 
  short cresceu;
  long j, i = 0;
  Tpagina pag_temp;

  if (pag == NULL){ 
  	*reg_retorno = reg; 
  	*pag_retorno = NULL;
    return TRUE;
  }
  
  while (i < pag->n && reg.chave > pag->registro[i].chave) 
  		i++;

  if (reg.chave == pag->registro[i].chave) { 
  	printf("REGISTRO ja esta presente\n");
    return FALSE; //não consegui incluir
  }

  cresceu = insere_rec(reg, pag->folha[i], reg_retorno, pag_retorno); //desce e verifica se existe 
  if (!cresceu) 
  	return (FALSE);

  if (pag->n < maximo){   /* PAGINA tem espaco */
    insere_na_pagina(pag, *reg_retorno, *pag_retorno);
    return FALSE;
  }

  /* PAGINA tem que ser dividida */
  pag_temp = (Tpagina)malloc(sizeof(pagina));
  pag_temp->n = 0;  
  pag_temp->folha[0] = NULL;
  
  if (i < ordem+1){ //entre a primeira e quase a metade das folhas
    insere_na_pagina(pag_temp, pag->registro[maximo-1], pag->folha[maximo]);//insere o último elemento em uma flha temporária
    pag->n--;
    insere_na_pagina(pag, *reg_retorno, *pag_retorno);
  } 
  else //últimas folhas
    insere_na_pagina(pag_temp, *reg_retorno, *pag_retorno);
  
  for (j = ordem + 2; j <= maximo; j++)
    insere_na_pagina(pag_temp, pag->registro[j-1], pag->folha[j]);
  
  pag->n = ordem;  
  pag->folha[0] = pag->folha[ordem+1];
  *reg_retorno = pag->registro[ordem];
  *pag_retorno = pag_temp;
  return TRUE;
}

Tpagina insere(Tregistro reg, Tpagina pag_raiz){ 
  short cresceu;
  Tregistro reg_retorno;
  Tpagina pag_retorno, pag_temp;

  cresceu = insere_rec(reg, pag_raiz, &reg_retorno, &pag_retorno);
  if (cresceu){
    pag_temp = (Tpagina)malloc(sizeof(pagina));
    pag_temp->n = 1;
    pag_temp->registro[0] = reg_retorno;
    pag_temp->folha[1] = pag_retorno;
    pag_temp->folha[0] = pag_raiz;
    return pag_temp;
  }
  return pag_raiz;
}


