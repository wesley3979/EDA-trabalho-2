#include "lib.h"

void menu(){
	int op, i;
	
	//--------- iniciando a estrutura --------------------//
    Tcliente novoCliente;
    Tpedido novoPedido;
	TpaginaCliente pagina = 0;
    
    do{    
    //--------------- Exibir menu ---------------------//
        system("cls");
        puts("\n\t\t\t\tARVORE B - ORDEM 2\n");
        puts("\t1  - CADASTRAR UM CLIENTE\n \t2  - CADASTRAR PEDIDOS\n \t3  - IMPRIMIR PEDIDOS DE UM CLIENTE\n \t0  - SAIR");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op);//Escolha da Opção
        
        switch(op){
        //Opção de exibir lista
    		case 1:{
    			printf("Informe um Id para o Cliente: ");
    			scanf("%d", &novoCliente.id);
    			
       			printf("Informe o CPF do Cliente: ");
    			scanf(" %[^\n]", novoCliente.cpf);
    			
    			printf("Informe o nome Cliente: ");
    			scanf(" %[^\n]", novoCliente.nome);
    			
    			printf("Informe o endereco do Cliente: ");
    			scanf(" %[^\n]", novoCliente.endereco);
    			
    			pagina = insereCliente(novoCliente, pagina);
				break;
			}
    		
    		case 2:{
    			printf("Informe a ordem de servico do pedido: ");
    			scanf("%d", &novoPedido.ordemServico);
    			
    			printf("Informe a quantidade de itens desse pedido: ");
    			scanf("%d", &novoPedido.quantidade);
    			
    			printf("Informe a descrição desse pedido: ");
    			scanf("%d", &novoPedido.descProduto);
    			
    			printf("Informe o cpf do cliente: ");
    			scanf("%d", &novoPedido.cpfCliente);
    			
    			pagina = insereCliente(novoCliente, pagina);
				break;
			}
			
			case 3: imprimeCliente(pagina,0); break;
    			
	    	default:
	    		puts("OPCAO INCORRETA,TENTE NOVAMENTE.");break;
	      
	        }
		getch();
	}while(op!=0);
}

//Implementação das funções referentes aos Clientes
Tcliente* buscarCliente(int chave, TpaginaCliente a){ 
  long i = 0;
  if (a == NULL) 
  	return NULL;
  while (i < a->n && chave > a->registroCliente[i].id) 
  	i++;
  if (chave == a->registroCliente[i].id) 
  	return &a->registroCliente[i];
  if (chave < a->registroCliente[i].id)
    return buscarCliente(chave, a->folhaCliente[i]);
  else
    return buscarCliente(chave, a->folhaCliente[i+1]);
}

void imprimeCliente(TpaginaCliente p, int nivel){ 
  if (p == NULL) 
  	return;
  printf("Nivel %d : ", nivel);
  for (int i = 0; i < p->n; i++){
  	printf("ID: %d \n", p->registroCliente[i].id);
    printf("NOME: ");
    puts(p->registroCliente[i].nome);
	printf("CPF: ");
	puts(p->registroCliente[i].cpf);
    printf("ENDERECO: ");
    puts(p->registroCliente[i].endereco);
  }
 
  printf("\n");
  for (int i = 0; i <= p->n; i++)
    imprimeCliente(p->folhaCliente[i], nivel+1);
}

TpaginaCliente insereCliente(Tcliente cliente, TpaginaCliente pag_raiz_cliente){ 

  short cresceu;
  Tcliente reg_cliente_retorno;
  TpaginaCliente pag_cliente_retorno, pag_cliente_temp;

  cresceu = insere_rec_cliente(cliente, pag_raiz_cliente, &reg_cliente_retorno, &pag_cliente_retorno);
  if (cresceu){
    pag_cliente_temp = (TpaginaCliente)malloc(sizeof(paginaCliente));
    pag_cliente_temp->n = 1;
    pag_cliente_temp->registroCliente[0] = reg_cliente_retorno;
    pag_cliente_temp->folhaCliente[1] = pag_cliente_retorno;
    pag_cliente_temp->folhaCliente[0] = pag_raiz_cliente;
    return pag_cliente_temp;
  }
  return pag_raiz_cliente;
}

void insere_cliente_na_pagina(TpaginaCliente pag, Tcliente reg, TpaginaCliente pag_dir)
{ 
  int i;
  for (i = pag->n; (i > 0) && (reg.id < pag->registroCliente[i-1].id); i--){
    pag->registroCliente[i] = pag->registroCliente[i-1];
    pag->folhaCliente[i+1] = pag->folhaCliente[i];    
  }
  pag->registroCliente[i] = reg;
  pag->folhaCliente[i+1] = pag_dir;
  pag->n++;
} 

short insere_rec_cliente(Tcliente reg, TpaginaCliente pag, Tcliente *reg_retorno, TpaginaCliente *pag_retorno)
{ 
  short cresceu;
  long j, i = 0;
  TpaginaCliente pag_temp;

  if (pag == NULL){ 
  	*reg_retorno = reg; 
  	*pag_retorno = NULL;
    return TRUE;
  }
  
  while (i < pag->n && reg.id > pag->registroCliente[i].id) 
  		i++;

  if (reg.id == pag->registroCliente[i].id) { 
  	printf("REGISTRO ja esta presente\n");
    return FALSE; //não consegui incluir
  }

  cresceu = insere_rec_cliente(reg, pag->folhaCliente[i], reg_retorno, pag_retorno); //desce e verifica se existe 
  if (!cresceu) 
  	return (FALSE);

  if (pag->n < maximo){   /* PAGINA tem espaco */
    insere_cliente_na_pagina(pag, *reg_retorno, *pag_retorno);
    return FALSE;
  }

  /* PAGINA tem que ser dividida */
  pag_temp = (TpaginaCliente)malloc(sizeof(paginaCliente));
  pag_temp->n = 0;  
  pag_temp->folhaCliente[0] = NULL;
  
  if (i < ordem+1){ //entre a primeira e quase a metade das folhas
    insere_cliente_na_pagina(pag_temp, pag->registroCliente[maximo-1], pag->folhaCliente[maximo]);//insere o último elemento em uma flha temporária
    pag->n--;
    insere_cliente_na_pagina(pag, *reg_retorno, *pag_retorno);
  } 
  else //últimas folhas
    insere_cliente_na_pagina(pag_temp, *reg_retorno, *pag_retorno);
  
  for (j = ordem + 2; j <= maximo; j++)
    insere_cliente_na_pagina(pag_temp, pag->registroCliente[j-1], pag->folhaCliente[j]);
  
  pag->n = ordem;  
  pag->folhaCliente[0] = pag->folhaCliente[ordem+1];
  *reg_retorno = pag->registroCliente[ordem];
  *pag_retorno = pag_temp;
  return TRUE;
}
//Implementação das funções referentes aos Pedidos
