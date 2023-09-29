#include "biblioteca.h"

void cadastrar_cliente(){

    
}

Clientes* deletar_cliente(Clientes* usuarios , char* CPF){
    Clientes* usuarios_temp;

    if(usuarios->qtd == 0){
        printf("==============");
        printf("Nenhum usuario cadastro no banco\n");
        printf("==============");
    }else{
        int cont = 0;

        for(int i = 0 ; i < usuarios->qtd ; i++){
            if(usuarios->lista[i].CPF != CPF){
                strcpy(usuarios_temp->lista[cont].nome , usuarios->lista[i].nome);
                strcpy(usuarios_temp->lista[cont].CPF , usuarios->lista[i].CPF);
                strcpy(usuarios_temp->lista[cont].Tipo_conta , usuarios->lista[i].Tipo_conta);
                usuarios_temp->lista[cont].Saldo = usuarios_temp->lista[cont].Saldo;
                strcpy(usuarios_temp->lista[cont].Senha , usuarios->lista[i].Senha);

                cont++;
            }
        }
    }
}

void listar_clientes(Clientes* usuarios){

    if(usuarios->qtd == 0){
        printf("==============");
        printf("Nenhum usuario cadastrado no banco\n");
        printf("==============");
    }else{
        printf("==============");

        for(int i = 0 ; i < usuarios->qtd ; i++){
            printf("Nome: %s\n" , usuarios->lista[i].nome);
            printf("CPF: %s\n" , usuarios->lista[i].CPF);
            printf("Tipo de conta: %s\n" , usuarios->lista[i].Tipo_conta);
        }

        printf("==============");
    }
}