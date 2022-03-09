#include "lib.h"

void menu(){
	int op, i;
	
	//--------- iniciando a estrutura --------------------//
    Tcliente novoCliente;
    Tpedido novoPedido;
	TpaginaCliente paginaCliente = 0;
	TpaginaPedido paginaPedido = 0;
    
    do{    
    //--------------- Exibir menu ---------------------//
        system("cls");
        puts("\n\t\t\t\tARVORE B - ORDEM 2\n");
        puts("\t1  - CADASTRAR UM CLIENTE\n \t2  - CADASTRAR UM PEDIDO\n \t3  - ATUALIZAR PEDIDO DE UM CLIENTE\n \t4  - IMPRIMIR PEDIDOS DE UM CLIENTE\n \t0  - SAIR");
        printf("\nINFORME SUA OPCAO:\n");
        scanf("%d", &op);//Escolha da Opção
        
        switch(op){
        //Opção de exibir lista
    		case 1:{
    			//cadastro do cliente
    			printf("Informe um Id para o Cliente: ");
    			scanf("%d", &novoCliente.id);
    			
       			printf("Informe o CPF do Cliente: ");
    			scanf(" %[^\n]", novoCliente.cpf);
    			
    			printf("Informe o nome Cliente: ");
    			scanf(" %[^\n]", novoCliente.nome);
    			
    			printf("Informe o endereco do Cliente: ");
    			scanf(" %[^\n]", novoCliente.endereco);
    			
    			paginaCliente = insereCliente(novoCliente, paginaCliente);
    			
    			printf("\n ****CADASTRO DO PRIMEIRO PEDIDO****\n ");
    			
    			printf("Informe a ordem de servico do pedido: ");
    			scanf("%d", &novoPedido.ordemServico);
    			
    			//id do cliente que cadastrou o pedido
    			novoPedido.idCliente = novoCliente.id;
				
				printf("Informe a quantidade de itens desse pedido: ");
    			scanf("%d", &novoPedido.quantidade);
    			
    			printf("Informe a descricao desse pedido {Banner = 1, Logo = 2 , Cracha = 3, Catalogo = 4, Outro = 5}: ");
    			scanf("%d", &novoPedido.descProduto);
    			
    			printf("Informe o status desse pedido {Andamento = 1, Cancelado = 2, Entregue = 3}: ");
    			scanf("%d", &novoPedido.status);
    			
    			paginaPedido = inserePedido(novoPedido, paginaPedido);
				break;
			}
    		
    		case 2:{
				printf("Informe a ordem de servico do pedido: ");
    			scanf("%d", &novoPedido.ordemServico);
    			
    			printf("Informe o Id do cliente que realizou esse pedido: ");
    			scanf("%d", &novoPedido.idCliente);
    			
    			if( buscarCliente(novoPedido.idCliente, paginaCliente) ) {
					printf("ERRO: O Id do cliente informado nao esta cadastrado.");
					break;
				}
				
				printf("Informe a quantidade de itens desse pedido: ");
    			scanf("%d", &novoPedido.quantidade);
    			
    			printf("Informe a descricao desse pedido {Banner = 1, Logo = 2 , Cracha = 3, Catalogo = 4, Outro = 5}: ");
    			scanf("%d", &novoPedido.descProduto);
    			
    			printf("Informe o status desse pedido {cancelado = 2, Entregue = 3 , Andamento = 1}: ");
    			scanf("%d", &novoPedido.status);
    			
    			paginaPedido = inserePedido(novoPedido, paginaPedido);
				break;
			}
			
			case 3:{
				int ordemServico = 0, status = 0, quantidade = 0;
				printf("Informe a ordem de servico do pedido que deseja atualizar: ");
    			scanf("%d", &ordemServico);
    			
    			printf("\nInforme o novo status {cancelado = 2, Entregue = 3 , Andamento = 1}: ");
    			scanf("%d", &status);
    			
    			printf("\nInforme a nova quantidade: ");
    			scanf("%d", &quantidade);
    			
				short statusAtualizacao = atualizaPedido(ordemServico, status, quantidade, paginaPedido);
				if( statusAtualizacao )
					printf("SUCESS: Pedido atualizado.");	
				else
					printf("ERROR: Nao foi possivel atualizar o pedido pois ele ja foi encerrado ou a ordem de servico nao existe.");	
				
				break;
			}
			
			case 4:{
				int idCliente;
				printf("Digite o ID do cliente para listar seus pedidos: ");
				scanf("%d", &idCliente);
				
				imprimePedidoPorIdCliente(paginaPedido, 0, idCliente); 
				break;
			}
    			
	    	default:
	    		puts("OPCAO INCORRETA,TENTE NOVAMENTE.");
				break;
	      
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
    return FALSE;
  }

  cresceu = insere_rec_cliente(reg, pag->folhaCliente[i], reg_retorno, pag_retorno);
  if (!cresceu) 
  	return (FALSE);

  if (pag->n < maximo){
    insere_cliente_na_pagina(pag, *reg_retorno, *pag_retorno);
    return FALSE;
  }

  pag_temp = (TpaginaCliente)malloc(sizeof(paginaCliente));
  pag_temp->n = 0;  
  pag_temp->folhaCliente[0] = NULL;
  
  if (i < ordem+1){
    insere_cliente_na_pagina(pag_temp, pag->registroCliente[maximo-1], pag->folhaCliente[maximo]);
    pag->n--;
    insere_cliente_na_pagina(pag, *reg_retorno, *pag_retorno);
  } 
  else
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

void imprimePedidoPorIdCliente(TpaginaPedido p, int nivel, int idCliente){ 
  if (p == NULL) 
  	return;
  printf("Nivel %d : ", nivel);
  for (int i = 0; i < p->n; i++){
  	if(p->registroPedido[i].idCliente == idCliente){
	  	printf("\nORDEM DE SERVICO: %d \n", p->registroPedido[i].ordemServico);
	  	printf("ID DO CLIENTE: %d \n", p->registroPedido[i].idCliente);
	  	printf("DESCRICAO DO PRODUTO: %d \n", p->registroPedido[i].descProduto);
	  	printf("QUANTIDADE: %d \n", p->registroPedido[i].quantidade);
	  	printf("STATUS: %d \n", p->registroPedido[i].status);	
	}
  }
 
  printf("\n");
  for (int i = 0; i <= p->n; i++)
    imprimePedidoPorIdCliente(p->folhaPedido[i], nivel+1, idCliente);
}

TpaginaPedido inserePedido(Tpedido pedido, TpaginaPedido pag_raiz_pedido){ 

  short cresceu;
  Tpedido reg_pedido_retorno;
  TpaginaPedido pag_pedido_retorno, pag_pedido_temp;

  cresceu = insere_rec_pedido(pedido, pag_raiz_pedido, &reg_pedido_retorno, &pag_pedido_retorno);
  if (cresceu){
    pag_pedido_temp = (TpaginaPedido)malloc(sizeof(paginaPedido));
    pag_pedido_temp->n = 1;
    pag_pedido_temp->registroPedido[0] = reg_pedido_retorno;
    pag_pedido_temp->folhaPedido[1] = pag_pedido_retorno;
    pag_pedido_temp->folhaPedido[0] = pag_raiz_pedido;
    return pag_pedido_temp;
  }
  return pag_raiz_pedido;
}

void insere_pedido_na_pagina(TpaginaPedido pag, Tpedido reg, TpaginaPedido pag_dir){ 
  int i;
  for (i = pag->n; (i > 0) && (reg.ordemServico < pag->registroPedido[i-1].ordemServico); i--){
    pag->registroPedido[i] = pag->registroPedido[i-1];
    pag->folhaPedido[i+1] = pag->folhaPedido[i];    
  }
  pag->registroPedido[i] = reg;
  pag->folhaPedido[i+1] = pag_dir;
  pag->n++;
} 

short insere_rec_pedido(Tpedido reg, TpaginaPedido pag, Tpedido *reg_retorno, TpaginaPedido *pag_retorno){ 
  short cresceu;
  long j, i = 0;
  TpaginaPedido pag_temp;

  if (pag == NULL){ 
  	*reg_retorno = reg; 
  	*pag_retorno = NULL;
    return TRUE;
  }
  
  while (i < pag->n && reg.ordemServico > pag->registroPedido[i].ordemServico) 
  		i++;

  if (reg.ordemServico == pag->registroPedido[i].ordemServico) { 
  	printf("REGISTRO ja esta presente\n");
    return FALSE;
  }

  cresceu = insere_rec_pedido(reg, pag->folhaPedido[i], reg_retorno, pag_retorno);
  if (!cresceu) 
  	return (FALSE);

  if (pag->n < maximo){
    insere_pedido_na_pagina(pag, *reg_retorno, *pag_retorno);
    return FALSE;
  }

  pag_temp = (TpaginaPedido)malloc(sizeof(paginaPedido));
  pag_temp->n = 0;  
  pag_temp->folhaPedido[0] = NULL;
  
  if (i < ordem+1){
    insere_pedido_na_pagina(pag_temp, pag->registroPedido[maximo-1], pag->folhaPedido[maximo]);
    pag->n--;
    insere_pedido_na_pagina(pag, *reg_retorno, *pag_retorno);
  } 
  else
    insere_pedido_na_pagina(pag_temp, *reg_retorno, *pag_retorno);
  
  for (j = ordem + 2; j <= maximo; j++)
    insere_pedido_na_pagina(pag_temp, pag->registroPedido[j-1], pag->folhaPedido[j]);
  
  pag->n = ordem;  
  pag->folhaPedido[0] = pag->folhaPedido[ordem+1];
  *reg_retorno = pag->registroPedido[ordem];
  *pag_retorno = pag_temp;
  return TRUE;
}

short atualizaPedido(int ordemServico, int status, int quantidade, TpaginaPedido pag){
  long i = 0;
  if (pag == NULL) 
  	return FALSE;
  while (i < pag->n && ordemServico > pag->registroPedido[i].ordemServico) 
  	i++;
  if (ordemServico == pag->registroPedido[i].ordemServico){
  	if(pag->registroPedido[i].status == 1){
	  	pag->registroPedido[i].quantidade = quantidade;
		pag->registroPedido[i].status = status;
  		return TRUE;	  
	  }

  } 
  	
  if (ordemServico < pag->registroPedido[i].ordemServico)
    return atualizaPedido(ordemServico, status, quantidade, pag->folhaPedido[i]);
  else
    return atualizaPedido(ordemServico, status, quantidade, pag->folhaPedido[i+1]);
}




