#include "biblioteca.h"

int main(){

  
  Clientes* lista_clientes = leitura("arquivo_clientes.txt");

    int opcao;

    printf("Bem vindo ao banco QuemPoupaTem !\n");

    do{

    opcao = menu();

    while(getchar() != '\n');

    if(opcao==1){
        cadastrar(lista_clientes);
        escreve(lista_clientes , "arquivo_clientes.txt");
    }
    else if(opcao==2){
        lista_clientes = deletar_cliente(lista_clientes);
        escreve(lista_clientes , "arquivo_clientes.txt");
    }
    else if(opcao==3){
      listar_clientes(lista_clientes);
        escreve(lista_clientes , "arquivo_clientes.txt");
    }
    else if(opcao==4){
      debitar( lista_clientes);
    }else if(opcao == 5){
        lista_clientes = deposita(lista_clientes);
        escreve(lista_clientes , "arquivo_clientes.txt");
    }else if(opcao == 6){
        listar_extrato(lista_clientes);
        escreve(lista_clientes , "arquivo_clientes.txt");
    }
    else if(opcao==7){
      transferencia(lista_clientes);
        escreve(lista_clientes , "arquivo_clientes.txt");
    }

    printf("\n");
  }while(opcao !=8 );

  printf("Obrigado Por Escolher QuemPoupaTem!\n");
  
  
    return 0;

}