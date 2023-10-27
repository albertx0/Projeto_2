#include "biblioteca.h"

char Nome_Cliente[50];
char CPF_Cliente[15];//CPF do usuário de origem
char CPF_Destinatario[15];//CPF do destinatário
char Tipo_Conta[10];
double Saldo;
char Senha_Cliente[50];
int Opcao; //Variavel de seleção
double Valor_Operacao;//Quantidade à serem debitadas ou transferidas

Clientes* leitura(char* nome_arquivo) {

    FILE* f = fopen(nome_arquivo, "rb"); // Abre o arquivo

    Clientes* clientes_arquivados = (Clientes*)malloc(100 * sizeof(Clientes)); // Comentar

    if (f == NULL) {
        clientes_arquivados->Quantidade_Clientes = 0;
    }
    else {
        fread(clientes_arquivados, sizeof(Clientes), 100, f); // Comentar
        fclose(f); // Fecha o arquivo
    }

    return clientes_arquivados; // Comentar
}

void escreve(Clientes* clientes, char* nome_arquivo) {
    FILE* f = fopen(nome_arquivo, "wb"); // Realiza a abertura do arquivo com o objetivo de escrever todas as possiveis tarefas feitas pelo usuario

    fwrite(clientes, sizeof(Clientes), clientes->Quantidade_Clientes, f); // Escreve as tarefas
    fclose(f); // Fecha o arquivo
}

int menu() {
    printf("1 - Cadastrar Clientes.\n");
    printf("2 - Apagar Cliente.\n");
    printf("3 - Listar todos os clientes.\n");
    printf("4 - Debitar valor de um cliente.\n");
    printf("5 - Depositar dinheiro.\n");
    printf("6 - Visualizar extrato.\n");
    printf("7 - Transfrencia.\n");
    printf("0 - Sair.\n\n");
    printf("Digite o numero da opcao desejada: ");
    scanf_s("%d", &Opcao);

    return Opcao;
}

Clientes* cadastrar(Clientes* Clientes_Banco) {

    int verifica_saida = 1;

    printf("\n==============\n");
    printf("Opcao cadastro: \n");

    printf("Digite o nome do cliente: ");
    input(Nome_Cliente);

    printf("Digite o CPF do cliente: ");
    while (true) {
        input(CPF_Cliente);
        if (buscaCPF(Clientes_Banco, CPF_Cliente) == -1)
            break;
        else if (strcmp(CPF_Cliente, "Sair") == 0) {
            verifica_saida = 0;
            break;
        } else
            printf("CPF ja existente no banco, escreva novamente o CPF ou escreva 'Sair' para finalizar operacao.\n");
    }

    if (verifica_saida == 0){
        printf("\n==============\n");
    printf("Operacao finalizada.\n");
    printf("==============\n");
    return Clientes_Banco;
    }else {
        printf("Digite a senha do cliente: ");
        input(Senha_Cliente);

        printf("Digite o tipo de conta do cliente (Comum / Plus) : ");
        input(Tipo_Conta);

        printf("Digite o saldo inicial da conta: ");
        scanf_s("%lf", &Saldo);

        int nova_posicao = Clientes_Banco->Quantidade_Clientes;

        //Copia as variaveis do struct para as variaveis da função
        strcpy(Clientes_Banco->lista[nova_posicao].nome, Nome_Cliente);
        strcpy(Clientes_Banco->lista[nova_posicao].CPF, CPF_Cliente);
        strcpy(Clientes_Banco->lista[nova_posicao].Tipo_conta, Tipo_Conta);
        Clientes_Banco->lista[nova_posicao].Saldo = Saldo;
        strcpy(Clientes_Banco->lista[nova_posicao].Senha, Senha_Cliente);
        Clientes_Banco->Quantidade_Clientes++;
        Clientes_Banco->lista[nova_posicao].Quantidade_Extrato = 0;
        printf("\n==============\n");
        printf("Cliente cadastrado com sucesso.\n");
        printf("==============\n");

        return Clientes_Banco;
    }
}

Clientes* deletar_cliente(Clientes* Clientes_Banco) {

    if (Clientes_Banco->Quantidade_Clientes == 0) {
        printf("\n==============\n");
        printf("Nenhum usuario cadastro no banco\n");
        printf("==============\n");
        return Clientes_Banco;

    }

    printf("Digite o CPF do cliente que deseja apagar: ");
    input(CPF_Cliente);

    Clientes* Clientes_Banco_temp = (Clientes*)malloc(sizeof(Clientes) * Clientes_Banco->Quantidade_Clientes);

    int posicao = buscaCPF(Clientes_Banco, CPF_Cliente);

    if (posicao == -1) {
        printf("\n==============\n");
        printf("Nenhum usuario cadastro com o CPF digitado, tente novamente.\n");
        printf("==============\n");
        return Clientes_Banco;
    }
    else {
        int cont = 0;

        for (int i = 0; i < Clientes_Banco->Quantidade_Clientes; i++) {

            if (i != posicao) {
                strcpy(Clientes_Banco_temp->lista[cont].nome, Clientes_Banco->lista[i].nome);
                strcpy(Clientes_Banco_temp->lista[cont].CPF, Clientes_Banco->lista[i].CPF);
                strcpy(Clientes_Banco_temp->lista[cont].Tipo_conta, Clientes_Banco->lista[i].Tipo_conta);
                Clientes_Banco_temp->lista[cont].Saldo = Clientes_Banco_temp->lista[i].Saldo;
                strcpy(Clientes_Banco_temp->lista[cont].Senha, Clientes_Banco->lista[i].Senha);

                cont++;
            }
        }
        printf("==============\n");
        printf("Cliente apagado com sucesso !\n");
        printf("==============\n");

        Clientes_Banco_temp->Quantidade_Clientes = cont;

        return Clientes_Banco_temp;
    }
}

void listar_clientes(Clientes* Clientes_Banco) {

    if (Clientes_Banco->Quantidade_Clientes == 0) {
        printf("\n==============\n");
        printf("Nenhum usuario cadastrado no banco\n");
        printf("==============\n");
    }
    else {
        printf("\n==============\n\n");

        for (int i = 0; i < Clientes_Banco->Quantidade_Clientes; i++) {
            printf("Cliente %d:\n", i + 1);
            printf("Nome: %s\n", Clientes_Banco->lista[i].nome);
            printf("CPF: %s\n", Clientes_Banco->lista[i].CPF);
            printf("Tipo de conta: %s\n\n", Clientes_Banco->lista[i].Tipo_conta);
        }
        printf("==============\n");
    }
}

Clientes* transferencia(Clientes* Clientes_Banco) {

    printf("Digite O Seu CPF: ");
    strcpy(CPF_Cliente , solicitaCPF(Clientes_Banco));

    int posicao_cliente_origem = buscaCPF(Clientes_Banco , CPF_Cliente);

    printf("Digite Sua Senha: ");
    char* senha_verificada = solicitaSenha(Clientes_Banco , posicao_cliente_origem);

    if(strcmp(senha_verificada , "CLIENT_ERROR") == 0){
        printf("Limite de tentativas excedido.\n");
        printf("Operacao finalizada.\n");
        return Clientes_Banco;
    }else {
        printf("Digite O CPF Do Destinatario: ");
        strcpy(CPF_Destinatario , solicitaCPF(Clientes_Banco));

        printf("Digite A Quantidade A Ser Tranferida: ");
        scanf_s("%lf", &Valor_Operacao);

        int posicao_cliente_destino = buscaCPF(Clientes_Banco, CPF_Destinatario);

        int tipo_cliente = verifica_saldo(Clientes_Banco->lista[posicao_cliente_origem].Tipo_conta,
                                          Clientes_Banco->lista[posicao_cliente_origem].Saldo, Valor_Operacao);
        if (tipo_cliente == 0) {
            printf("==============\n");
            printf("Saldo insuficiente para realizar a operacao.\n");
            printf("==============\n");
            return Clientes_Banco;
        } else {
            double Taxas;

            if (tipo_cliente == 1) {
                Taxas = Valor_Operacao * 0.05;
            } else {
                Taxas = Valor_Operacao * 0.03;
            }

            Clientes_Banco->lista[posicao_cliente_origem].Saldo -= (Valor_Operacao + Taxas);
            Clientes_Banco->lista[posicao_cliente_destino].Saldo += Valor_Operacao;

            int posicao_extrato_origem = Clientes_Banco->lista[posicao_cliente_origem].Quantidade_Extrato;
            Clientes_Banco->lista[posicao_cliente_origem].Quantidade_Extrato++;

            int posicao_extrato_destino = Clientes_Banco->lista[posicao_cliente_destino].Quantidade_Extrato;
            Clientes_Banco->lista[posicao_cliente_destino].Quantidade_Extrato++;

            Clientes_Banco->lista[posicao_cliente_origem].extrato[posicao_extrato_origem] = adiciona_transacao(
                    "Transferencia", "-", Valor_Operacao, Taxas,
                    Clientes_Banco->lista[posicao_cliente_origem].Saldo);
            Clientes_Banco->lista[posicao_cliente_destino].extrato[posicao_extrato_destino] = adiciona_transacao(
                    "Transferencia", "+", Valor_Operacao, 0, Clientes_Banco->lista[posicao_cliente_destino].Saldo);

            printf("==============\n");
            printf("Operacao realizada com sucesso !\n");
            printf("Saldo atual apos a operacao: R$ %.2lf\n", Clientes_Banco->lista[posicao_cliente_origem].Saldo);
            printf("==============\n");
        }
    }
    return Clientes_Banco;
}

Clientes* debitar(Clientes* Clientes_Banco) {

    printf("Digite seu CPF: ");
    strcpy(CPF_Cliente , solicitaCPF(Clientes_Banco));

    int posicao_cliente = buscaCPF(Clientes_Banco, CPF_Cliente);

    int tipo_cliente = verifica_saldo(Clientes_Banco->lista[posicao_cliente].Tipo_conta, Clientes_Banco->lista[posicao_cliente].Saldo, Valor_Operacao);

    if (buscaCPF(Clientes_Banco, CPF_Cliente) == -1) {
        printf("==============\n");
        printf("Nenhum cliente cadastrado com o CPF digitado.\n");
        printf("==============\n");
    }
    else {

        if(tipo_cliente == 0) {
            printf("==============\n");
            printf("Saldo insuficiente para realizar a operacao.\n");
            printf("==============\n");

            return Clientes_Banco;
        }else {
            double Taxas;

            if (tipo_cliente == 1) {
                Taxas = Valor_Operacao * 0.05;
            }
            else{
                Taxas = Valor_Operacao * 0.03;
            }

            Clientes_Banco->lista[posicao_cliente].Saldo -= (Valor_Operacao + Taxas);

            int posicao_extrato = Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato;
            Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato++;

            Clientes_Banco->lista[posicao_cliente].extrato[posicao_extrato] = adiciona_transacao("Deposita", "-", Valor_Operacao , Taxas , Clientes_Banco->lista[posicao_cliente].Saldo);
        }
    }

    printf("==============\n");
    printf("Operacao realizada com sucesso !\n");
    printf("Saldo atual apos a operacao: R$ %.2lf\n", Clientes_Banco->lista[posicao_cliente].Saldo);
    printf("==============\n");

    return Clientes_Banco;
}

Clientes* deposita(Clientes* Clientes_Banco) {

    printf("Digite O Seu CPF: ");
    strcpy(CPF_Cliente , solicitaCPF(Clientes_Banco));

    printf("Digite o valor que deseja depositar em sua conta: ");
    scanf_s("%lf", &Valor_Operacao);

    int posicao_cliente = buscaCPF(Clientes_Banco, CPF_Cliente);

    if (posicao_cliente == -1) {
        printf("==============\n");
        printf("Nenhum cliente cadastrado com o CPF digitado.\n");
        printf("==============\n");
        return Clientes_Banco;
    }
    else {
        int posicao_extrato = Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato;
        Clientes_Banco->lista[posicao_cliente].Saldo += Valor_Operacao;
        Clientes_Banco->lista[posicao_cliente].extrato[posicao_extrato] = adiciona_transacao("Deposita", "+", Valor_Operacao, 0 , Clientes_Banco->lista[posicao_cliente].Saldo);
        Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato++;

        printf("==============\n");
        printf("Operacao realizada com sucesso !\n");
        printf("Saldo atual apos a operacao: R$ %.2lf\n", Clientes_Banco->lista[posicao_cliente].Saldo);
        printf("==============\n");

        return Clientes_Banco;
    }
}

void gerar_extrato(Clientes* Clientes_Banco) {
    printf("Digite O Seu CPF: ");
    strcpy(CPF_Cliente , solicitaCPF(Clientes_Banco));

    int posicao_cliente = buscaCPF(Clientes_Banco, CPF_Cliente);

    printf("Digite Sua Senha: ");
    char* senha_verificada = solicitaSenha(Clientes_Banco , posicao_cliente);

    if(strcmp(senha_verificada , "CLIENT_ERROR") == 0) {
        printf("Limite de tentativas excedido.\n");
        printf("Operacao finalizada.\n");
    }else{
        strcat(CPF_Cliente , ".txt");
        FILE *arquivo_extrato = fopen(CPF_Cliente ,"w");
        fprintf(arquivo_extrato , "Nome do cliente: %s\n", Clientes_Banco->lista[posicao_cliente].nome);
        fprintf(arquivo_extrato , "CPF do cliente: %s\n", Clientes_Banco->lista[posicao_cliente].CPF);
        fprintf(arquivo_extrato , "Tipo de conta do cliente: %s\n", Clientes_Banco->lista[posicao_cliente].Tipo_conta);
        fprintf(arquivo_extrato , "==============\n");
        for (int i = 0 ; i < Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato; i++) {
            fprintf(arquivo_extrato , "Transacao %d:\n", i + 1);
            fprintf(arquivo_extrato ,"Operacao realizada: %s\n", Clientes_Banco->lista[posicao_cliente].extrato[i].Operacao);
            fprintf(arquivo_extrato , "Valor movimentado: R$ %s", Clientes_Banco->lista[posicao_cliente].extrato[i].Simbolo);
            fprintf(arquivo_extrato , "%.2lf\n", Clientes_Banco->lista[posicao_cliente].extrato[i].Valor);
            fprintf(arquivo_extrato , "Taxa aplicada na operacao: R$ %.2lf\n\n" , Clientes_Banco->lista[posicao_cliente].extrato[i].Taxa);
            fprintf(arquivo_extrato , "Saldo na conta apos a transacao: R$ %.2lf\n" ,Clientes_Banco->lista[posicao_cliente].extrato[i].Saldo_Momento);
        }
        fprintf(arquivo_extrato , "\n==============\n\n");
        fclose(arquivo_extrato);
    }
}

char* input(char* str) {
    int c;
    scanf("%[^\n]s", str); //Recebe o array de chars/string
    while ((c = getchar()) != '\n' && c != EOF) {} //Impede Que Sejam Pulados Inputs futuros após ser pressionada a tecla "enter"

    return str;
}

int verifica_saldo(char* Tipo_conta, double saldo_atual, double valor_operacao) {
    if (strcmp(Tipo_conta , "Comum") == 0 || strcmp(Tipo_conta , "Comum") == 0){
        if (saldo_atual - valor_operacao * 1.05 >= -1000)
            return 1;
        else
            return 0;
    }
    else {
        if (saldo_atual - valor_operacao * 1.03 >= -5000)
            return 2;
        else
            return 0;
    }
}

Extrato adiciona_transacao(char* Operacao, char* Simbolo, double Valor_Movimentado, double Taxa , double Saldo_Atual) {
    Extrato trasacao_temp;
    strcpy(trasacao_temp.Operacao, Operacao);
    strcpy(trasacao_temp.Simbolo, Simbolo);
    trasacao_temp.Valor = Valor_Movimentado;
    trasacao_temp.Taxa = Taxa;
    trasacao_temp.Saldo_Momento = Saldo_Atual;
    return trasacao_temp;
}

int buscaCPF(Clientes* Clientes_Banco, char* CPF) {

    for (int i = 0; i < Clientes_Banco->Quantidade_Clientes; i++) {
        if (strcmp(Clientes_Banco->lista[i].CPF, CPF) == 0) {
            return i;
        }
    }
    return -1;
}

int buscaSenha(Clientes* Clientes_Banco, int posicao_cliente, char* Senha) {

    if (strcmp(Clientes_Banco->lista[posicao_cliente].Senha, Senha) == 0)
        return 1;
    else
        return 0;
}

char* solicitaCPF(Clientes* Clientes_Banco){
    int verifica;

    while(true){
        input(CPF_Cliente);
        verifica = buscaCPF(Clientes_Banco, CPF_Cliente);

        if(verifica == -1)
            printf("CPF nao existente no banco, digite novamente: ");
        else
            break;

    }
    return CPF_Cliente;
}

char* solicitaSenha(Clientes* Clientes_Banco , int Posicao_Cliente){
    int verifica;
    int erros_cliente = 3;

    while(true){
        input(Senha_Cliente);
        verifica = buscaSenha(Clientes_Banco, Posicao_Cliente , Senha_Cliente);
        if(erros_cliente == 0 || verifica == 1)
            break;
        else{
            printf("Senha incorreta, possui mais %d tentativas: " , erros_cliente);
            erros_cliente--;
        }
    }
    if(erros_cliente == 0){
        return "CLIENT_ERROR";
    }else{
        return "CORRECT_PASSWORD";
    }
}