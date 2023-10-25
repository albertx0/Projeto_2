#include "biblioteca.h"

char Nome_Cliente[50];
char CPF_Cliente[15];//CPF do usuário de origem
char CPF_Destinatario[15];//CPF do destinatário
char Tipo_Conta[10];
double Saldo;
char Senha_Cliente[50];
int opcao=0; //Variavel de seleção
double Valor_Operacao;//Quantidade à serem debitadas ou transferidas

Clientes* leitura(char *nome_arquivo) {

    FILE *f = fopen(nome_arquivo, "rb"); // Abre o arquivo

    Clientes *clientes_arquivados = (Clientes *)malloc(100 * sizeof(Clientes)); // Comentar

    if(f == NULL){
        clientes_arquivados->qtd = 0;
    }else{
        fread(clientes_arquivados, sizeof(Clientes), 100,f); // Comentar
        fclose(f); // Fecha o arquivo
    }

    return clientes_arquivados; // Comentar
}

void escreve(Clientes *clientes , char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "w"); // Realiza a abertura do arquivo com o objetivo de escrever todas as possiveis tarefas feitas pelo usuario

    fwrite(clientes, sizeof(Clientes), clientes->qtd , f); // Escreve as tarefas

    fclose(f); // Fecha o arquivo
}

int menu(){
    printf("1 - Cadastrar Clientes.\n");
    printf("2 - Apagar Cliente.\n");
    printf("3 - Listar todos os clientes.\n");
    printf("4 - Debitar valor de um cliente.\n");
    printf("5 - Depositar dinheiro.\n");
    printf("6 - Visualizar extrato.\n");
    printf("7 - Transfrencia.\n");
    printf("8 - Sair.\n\n");
    printf("Digite o numero da opcao desejada: ");
    scanf("%d",&opcao);

    return opcao;
}

Clientes* cadastrar(Clientes* usuarios){

    printf("\n==============\n");
    printf("Opcao cadastro: \n");
    printf("Digite o nome do cliente: ");
    input(Nome_Cliente);
    printf("Digite o CPF do cliente: ");
    input(CPF_Cliente);
    printf("Digite a senha do cliente: ");
    input(Senha_Cliente);
    printf("Digite o tipo de conta do cliente: ");
    input(Tipo_Conta);
    printf("Digite o saldo inicial da conta: ");
    scanf("%lf", &Saldo);

    if(buscaCPF(usuarios , CPF_Cliente) == -1){
        int nova_posicao = usuarios->qtd;

        //Copia as variaveis do struct para as variaveis da função
        strcpy(usuarios->lista[nova_posicao].nome , Nome_Cliente);
        strcpy(usuarios->lista[nova_posicao].CPF, CPF_Cliente);
        strcpy(usuarios->lista[nova_posicao].Tipo_conta, Tipo_Conta);
        usuarios->lista[nova_posicao].Saldo = Saldo;
        strcpy(usuarios->lista[nova_posicao].Senha, Senha_Cliente);
        usuarios->qtd++;
        usuarios->lista[nova_posicao].qtd_extrato = 0;
        printf("\n==============\n");
        printf("Cliente cadastrado com sucesso.\n");
        printf("==============\n");
    }else{
        printf("\n==============\n");
        printf("O banco ja possui um cliente cadastrado com este CPF, tente novamente.\n");
        printf("==============\n");
    }

    return usuarios;
}

Clientes* deletar_cliente(Clientes* usuarios){
    printf("Digite o CPF do cliente que deseja apagar: ");
    input(CPF_Cliente);

    Clientes* usuarios_temp = (Clientes*)malloc(sizeof(Clientes) * usuarios->qtd);

    int posicao = buscaCPF(usuarios , CPF_Cliente);
    printf("aq aq %d\n" , posicao);
    if(usuarios->qtd == 0){
        printf("==============\n");
        printf("Nenhum usuario cadastro no banco\n");
        printf("==============\n");
        return usuarios;

    }else if(posicao == -1){
        printf("==============\n");
        printf("Nenhum usuario cadastro com o CPF digitado, tente novamente.\n");
        printf("==============\n");
        return usuarios;
    }else {
        int cont = 0;

        for (int i = 0 ; i < usuarios->qtd ; i++) {

            if (i != posicao) {
                strcpy(usuarios_temp->lista[cont].nome, usuarios->lista[i].nome);
                strcpy(usuarios_temp->lista[cont].CPF, usuarios->lista[i].CPF);
                strcpy(usuarios_temp->lista[cont].Tipo_conta, usuarios->lista[i].Tipo_conta);
                usuarios_temp->lista[cont].Saldo = usuarios_temp->lista[i].Saldo;
                strcpy(usuarios_temp->lista[cont].Senha, usuarios->lista[i].Senha);

                cont++;
            }
        }
        printf("==============\n");
        printf("Cliente apagado com sucesso !\n");
        printf("==============\n");

        usuarios_temp->qtd = cont;

        return usuarios_temp;
    }
}

void listar_clientes(Clientes* usuarios) {

    if (usuarios->qtd == 0) {
        printf("\n==============\n");
        printf("Nenhum usuario cadastrado no banco\n");
        printf("==============\n");
    } else {
        printf("\n==============\n");


        for (int i = 0; i < usuarios->qtd; i++) {
            printf("Cliente %d:\n" , i+1);
            printf("Nome: %s\n", usuarios->lista[i].nome);
            printf("CPF: %s\n", usuarios->lista[i].CPF);
            printf("Tipo de conta: %s\n\n", usuarios->lista[i].Tipo_conta);
        }
        printf("==============\n");
    }
}

Clientes* transferencia(Clientes* usuarios) {

    double Valor_com_Taxas;
    printf("Digite O Seu CPF: ");
    input(CPF_Cliente);
    printf("Digite Sua Senha: ");
    input(Senha_Cliente);
    printf("Digite O CPF Do Destinatario: ");
    input(CPF_Destinatario);
    printf("Digite A Quantidade A Ser Tranferida: ");
    scanf("%lf", &Valor_Operacao);

    int posicao_cliente_origem = buscaCPF(usuarios, CPF_Cliente);
    int posicao_cliente_destino = buscaCPF(usuarios, CPF_Destinatario);

    if (posicao_cliente_origem == -1) {
        printf("==============\n");
        printf("O CPF de origem digitado não foi encontrado nos clientes do banco.\n");
        printf("==============\n");
    } else if (posicao_cliente_destino == -1) {
        printf("==============\n");
        printf("O CPF de destino digitado não foi encontrado nos clientes do banco.\n");
        printf("==============\n");
    } else {
        int tipo_cliente = verifica_saldo(usuarios->lista[posicao_cliente_origem].Tipo_conta,usuarios->lista[posicao_cliente_origem].Saldo, Valor_Operacao);

        if (tipo_cliente == 0) {
            printf("==============\n");
            printf("Saldo insuficiente para realizar a operacao.\n");
            printf("==============\n");
            return usuarios;
        }else if(tipo_cliente == 1){
            Valor_com_Taxas = Valor_Operacao * 1.05;
        }else if(tipo_cliente == 2){
            Valor_com_Taxas = Valor_Operacao * 1.03;
        }

        usuarios->lista[posicao_cliente_origem].Saldo -= Valor_com_Taxas;
        usuarios->lista[posicao_cliente_destino].Saldo += Valor_Operacao;

        return usuarios;
    }
}


Clientes* debitar(Clientes* usuarios){

    double Valor_com_Taxas;

    printf("Digite seu CPF: ");
    input(CPF_Cliente);
    printf("Digite sua senha: ");
    input(Senha_Cliente);
    printf("Digite o valor a ser debitado da conta: ");
    scanf("%lf",&Valor_Operacao);

    int posicao_cliente = buscaCPF(usuarios , CPF_Cliente);

    int tipo_cliente = verifica_saldo(usuarios->lista[posicao_cliente].Tipo_conta , usuarios->lista[posicao_cliente].Saldo , Valor_Operacao);

    if(buscaCPF(usuarios , CPF_Cliente) == -1){
        printf("==============\n");
        printf("Nenhum cliente cadastrado com o CPF digitado.\n");
        printf("==============\n");
    }else{
        if(tipo_cliente == 1){
            Valor_com_Taxas = Valor_Operacao * 1.05;
        }else if(tipo_cliente == 2){
            Valor_com_Taxas = Valor_Operacao * 1.03;
        }else{
            printf("==============\n");
            printf("Saldo insuficiente para realizar a operacao.\n");
            printf("==============\n");
        }
        int posicao_extrato = usuarios->lista[posicao_cliente].qtd_extrato;
        usuarios->lista[posicao_cliente].qtd_extrato++;

        usuarios->lista[posicao_cliente].extrato[posicao_extrato] = adiciona_transacao("Deposita" , Valor_Operacao , Valor_com_Taxas);
    }

    return usuarios;
}

Clientes* deposita(Clientes* usuarios){

    printf("Digite seu CPF: ");
    input(CPF_Cliente);
    printf("Digite o valor que deseja depositar em sua conta: ");
    scanf("%lf" , &Valor_Operacao);

    int posicao_cliente = buscaCPF(usuarios , CPF_Cliente);

    if(posicao_cliente == -1){
        printf("==============\n");
        printf("Nenhum cliente cadastrado com o CPF digitado.\n");
        printf("==============\n");
        return usuarios;
    }else {
        int posicao_extrato = usuarios->lista[posicao_cliente].qtd_extrato;
        printf("aq pospos %d\n", usuarios->qtd);
        usuarios->lista[posicao_cliente].Saldo += Valor_Operacao;
        usuarios->lista[posicao_cliente].extrato[posicao_extrato] = adiciona_transacao("Deposita" , Valor_Operacao , 0);
        usuarios->lista[posicao_cliente].qtd_extrato++;
        printf("Operacao feita com sucesso !\n");
        return usuarios;
    }
}

void listar_extrato(Clientes* usuarios){
    printf("Digite seu CPF: ");
    input(CPF_Cliente);

    int posicao_cliente = buscaCPF(usuarios , CPF_Cliente);


    if(posicao_cliente == -1){
        printf("Nenhum cliente cadastrado com esse CPF\n");
    }else{
        printf("Digite sua senha: ");
        input(Senha_Cliente);

        printf("Nome: %s\n" , usuarios->lista[posicao_cliente].nome);

        if(buscaSenha(usuarios , posicao_cliente , Senha_Cliente) == 1){
            for(int i = 0 ; i < usuarios->lista[posicao_cliente].qtd_extrato; i++){
                printf("Operacao realizada: %s\n"  , usuarios->lista[posicao_cliente].extrato[i].Operacao);
                printf("Valor movimentado: R$ %.2lf\n"  , usuarios->lista[posicao_cliente].extrato[i].Valor);
                printf("Taxa aplicada na operacao: R$ %.2lf\n"  , usuarios->lista[posicao_cliente].extrato[i].Taxa);
                printf("Data: %s\n"  , usuarios->lista[posicao_cliente].extrato[i].Data_Hora);
            }
        }else{
            printf("Senha incorreta.\n");
        }
    }
}

char* input(char *str){
    int c;
    scanf("%[^\n]s",str); //Recebe o array de chars/string
    while ((c = getchar()) != '\n' && c != EOF) { } //Impede Que Sejam Pulados Inputs futuros após ser pressionada a tecla "enter"

    return str;
}

int verifica_saldo(char* Tipo_conta , double saldo_atual , double valor_operacao){
    if(Tipo_conta == "Comum" || Tipo_conta == "comum"){
        if(saldo_atual - valor_operacao * 1.05 >= -1000)
            return 1;
        else
            return 0;
    }else{
        if(saldo_atual - valor_operacao * 1.03 >= -5000)
            return 2;
        else
            return 0;
    }
}

Extrato adiciona_transacao(char* operacao , double valor , double taxa){
    Extrato stc_temp;
    strcpy(stc_temp.Operacao, operacao);
    stc_temp.Valor = valor;
    stc_temp.Taxa = taxa;

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

int buscaSenha(Clientes* usuarios , int posicao_cliente , char* Senha){

    if(strcmp(usuarios->lista[posicao_cliente].Senha , Senha) == 0){
        return 1;
    }
    return 0;
}
