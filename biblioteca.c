#include "biblioteca.h"

void menu(){
    printf("1 - Cadastrar Clientes.\n");
    printf("2 - Apagar Cliente.\n");
    printf("3 - Listar todos os clientes.\n");
    printf("4 - Debitar valor de um cliente.\n");
    printf("5 - Depositar dinheiro.\n");
    printf("6 - Visualizar extrato.\n");
    printf("7 - Transfrencia.\n");
    printf("Digite o numero da opcao desejada: \n");
}

Clientes* deletar_cliente(Clientes* usuarios , char* CPF){
    Clientes* usuarios_temp = (Clientes*)malloc(1000*sizeof(Clientes));

    int posicao = buscaCPF(usuarios , CPF);

    if(usuarios->qtd == 0){
        printf("==============\n");
        printf("Nenhum usuario cadastro no banco\n");
        printf("==============\n");
        return usuarios;

    }else if(posicao == -1){
        printf("==============\n");
        printf("Nenhum usuario cadastro com o CPF digitado.\n");
        printf("==============\n");
        return usuarios;

    }else {
        int cont = 0;

        for (int i = 0; i < usuarios->qtd; i++) {
            if (i != posicao) {
                strcpy(usuarios_temp->lista[cont].nome, usuarios->lista[i].nome);
                strcpy(usuarios_temp->lista[cont].CPF, usuarios->lista[i].CPF);
                strcpy(usuarios_temp->lista[cont].Tipo_conta, usuarios->lista[i].Tipo_conta);
                usuarios_temp->lista[cont].Saldo = usuarios_temp->lista[cont].Saldo;
                strcpy(usuarios_temp->lista[cont].Senha, usuarios->lista[i].Senha);
                cont++;
            }
        }
        printf("==============\n");
        printf("Cliente apagado com sucesso !\n");
        printf("==============\n");

        return usuarios_temp;
    }
}

void listar_clientes(Clientes* usuarios){

    if(usuarios->qtd == 0){
        printf("==============\n");
        printf("Nenhum usuario cadastrado no banco\n");
        printf("==============\n");
    }else{
        printf("==============\n");

        for(int i = 0 ; i < usuarios->qtd ; i++){
            printf("Nome: %s\n" , usuarios->lista[i].nome);
            printf("CPF: %s\n" , usuarios->lista[i].CPF);
            printf("Tipo de conta: %s\n" , usuarios->lista[i].Tipo_conta);
        }

        printf("==============\n");
    }
}

Clientes* deposita(Clientes* usuarios , char* CPF , double valor){

    int posicao = buscaCPF(usuarios , CPF);
    double taxas;

    if(posicao == -1){
        printf("==============\n");
        printf("Nenhum cliente cadastrado com o CPF digitado.\n");
        printf("==============\n");
    }else {
        if (strcmp(usuarios->lista[posicao].Tipo_conta, "Comum") == 0 || strcmp(usuarios->lista[posicao].Tipo_conta, "comum") == 0) {
            taxas = valor * 0.95;
        } else {
            taxas = valor * 0.97;
        }
    }

    usuarios->lista[posicao].extrato[usuarios->lista[posicao].qtd_extrato] = adiciona_transacao("Deposito", valor, taxas);

    usuarios->lista[posicao].qtd_extrato++;

    return usuarios;
}

Extrato adiciona_transacao(char* operacao , double valor , double taxa){
    Extrato stc_temp;
    strcpy(stc_temp.operacao, operacao);
    stc_temp.valor = valor;
    stc_temp.taxa = taxa;

    struct tm *p;
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    stc_temp.hora = p->tm_hour;
    stc_temp.minuto = p->tm_min;
    stc_temp.segundo = p->tm_sec;

    stc_temp.dia = p->tm_mday;
    stc_temp.mes = p->tm_mon + 1;
    stc_temp.ano = p->tm_year + 1900;

    return stc_temp;
}


int buscaCPF(Clientes* usuarios, char* CPF){

    for(int i = 0 ; i < usuarios->qtd ; i++){
        if(strcmp(usuarios->lista[i].CPF , CPF) == 0){
            return i;
        }
    }

    return -1;
}



int buscaSenha(Clientes* usuarios , char* Senha){

    for(int i = 0 ; i < usuarios->qtd ; i++){
        if(strcmp(usuarios->lista[i].Senha , Senha) == 0){
            return 1;
        }
    }

    return 0;
}