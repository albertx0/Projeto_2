//Paulo Gabriel Gonçalves Leme | R.A: 21.123.075.4
//Gabriel Albertini Pinheiro | R.A: 24.123.004-4

#include "biblioteca.h"

char Nome_Cliente[50]; //Nome do cliente
char CPF_Cliente[15];//CPF do usuário de origem
char CPF_Destinatario[15];//CPF do destinatário
char Tipo_Conta[10];
double Saldo;
char Senha_Cliente[50];
int Opcao; //Variavel de seleção
double Valor_Operacao;//Quantidade à serem debitadas ou transferidas

Clientes* leitura(char* nome_arquivo) { // Funcao para realizar a leitura de todas as informacoes contidas no arquivo e retorna um array de struct Clientes

    FILE* arquivo = fopen(nome_arquivo, "rb"); // Abre o arquivo

    Clientes* clientes_arquivados = (Clientes*)malloc(100 * sizeof(Clientes)); // Comentar

    if (arquivo == NULL) {
        clientes_arquivados->Quantidade_Clientes = 0;
    }
    else {
        fread(clientes_arquivados, sizeof(Clientes), 1, arquivo); // Comentar
        fclose(arquivo); // Fecha o arquivo
    }

    return clientes_arquivados; // Comentar
}

void escreve(Clientes* Clientes_Banco, char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "wb"); // Funcao para abri o arquivo desejado e escrever em binario todas as informacoes dos clientes contidas no array de strucy Clientes

    fwrite(Clientes_Banco, sizeof(Clientes), 1, arquivo); // Escrita das informacoes
    fclose(arquivo); // Fecha o arquivo
}

int menu() { // Funcao de menu para exibir ao cliente todas as opcoes disponiveis no banco
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

    return Opcao;   // A funcao retorna o numero da opcao que o cliente escolheu
}

Clientes* cadastrar(Clientes* Clientes_Banco) { //Funcao para realizar o cadastro de novos clientes

    if(Clientes_Banco->Quantidade_Clientes == 1000){
        printf("\n==============\n");
        printf("O limite de clientes cadastrados no banco foi atingido, no momento nao eh possivel cadastrar mais cliente.\n");
        printf("Opercao finalizada.\n");
        printf("==============\n");
    }else{
        printf("\n==============\n");
        printf("Opcao cadastro: \n");

        printf("Digite o nome do cliente: ");
        input_string(Nome_Cliente); //Recebe o nome do cliente

        int verifica_saida = 1; //Variavel de verificacao em caso do cliente ter desejado cancelar a operacao durante seu funcionamento
        printf("Digite o CPF do cliente: ");
        while (true) { // Inicia um looping para verificar se o CPF digitado pelo cliente ja esta cadastrado no banco
            input_string(CPF_Cliente);
            int verifica_novo_cliente = buscaCPF(Clientes_Banco, CPF_Cliente);


            if (strcmp(CPF_Cliente, "Finalizar") == 0) { // Caso o usuario escreva "Finalizar" o looping eh finalizado e a variavel "verifica_saida" tem seu valor alterado para 0
                verifica_saida = 0;
                break;
            }else if (verifica_novo_cliente == -1){ //Se a funcao retornar -1 significa que o CPF digitado pelo cliente nao existe no banco
                break;
            }else{ // Caso contrario eh notificado ao cliente que o CPF digitado ja esta cadastrado no banco e adiciona a opcao do cliente finalizar a operacao
                printf("CPF ja cadastrado no banco, digite novamente ou escreva 'Finalizar' para encerrar operacao\n");
            }

        }

        if (verifica_saida == 0) { // Caso a variavel "verifica_saida" teve o valor trocado para 0, a funcao eh encerrada retornando o array de struct Clientes
            printf("\n==============\n");
            printf("Operacao finalizada.\n");
            printf("==============\n");
        }
        else {
            printf("Digite a senha do cliente: "); // Recebe que o cliente deseja colocar em sua conta
            input_string(Senha_Cliente);

            printf("Digite o tipo de conta do cliente (Comum / Plus) : "); //Recebe o tipo de conta que o cliente deseja ter
            input_string(Tipo_Conta);

            printf("Digite o saldo inicial da conta: "); //Recebe o valor inicial que o cliente deseja ter em sua conta
            scanf_s("%lf", &Saldo);

            int nova_posicao = Clientes_Banco->Quantidade_Clientes; // Variavel que recebe o indice de clientes atual do banco

            //Acessa cada variavel do array de Dados e copia cada dado recebido pelo cliente com o correpondente da struct Dados
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
        }
    }
    return Clientes_Banco;
}

Clientes* deletar_cliente(Clientes* Clientes_Banco) { //Funcao para deletar um cliente do banco por meio do CPF

    if (Clientes_Banco->Quantidade_Clientes == 0) { // Verifica se o banco possui algum cliente cadastrado, caso nao tiver a funcao eh encerrada
        printf("\n==============\n");
        printf("Nenhum usuario cadastro no banco\n");
        printf("==============\n");
    }else {

        printf("Digite o CPF do cliente que deseja apagar: "); // Recebe o CPF que o cliente deseja deletar
        strcpy(CPF_Cliente, solicitaCPF(Clientes_Banco));

        if (strcmp(CPF_Cliente, "Finalizar") != 0) {
            Clientes *Clientes_Banco_temp = (Clientes *) malloc(sizeof(Clientes) *
                                                                Clientes_Banco->Quantidade_Clientes); //Criacao de um array de struct Cliente temporario

            int posicao_cliente = buscaCPF(Clientes_Banco,
                                           CPF_Cliente); // Variavel que vai receber a posicao do cliente por meio da funcao


            int cont = 0;

            for (int i = 0; i <
                            Clientes_Banco->Quantidade_Clientes; i++) { //Realiza a copia de todos os dados da lista de clientes exceto quando o i eh igual a posicao do cliente

                if (i != posicao_cliente) { //Realiza a copia
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

        }
    }
    return Clientes_Banco;
}

void listar_clientes(Clientes* Clientes_Banco) {

    if (Clientes_Banco->Quantidade_Clientes == 0) { // Verifica se ha clientes na loja, caso contrario encerra a operacao
        printf("\n==============\n");
        printf("Nenhum usuario cadastrado no banco\n");
        printf("==============\n");
    }
    else {
        printf("\n==============\n\n");

        for (int i = 0; i < Clientes_Banco->Quantidade_Clientes; i++) { // Percorre cada indice da lista de clientes
            printf("Cliente %d:\n", i + 1);
            printf("Nome: %s\n", Clientes_Banco->lista[i].nome);
            printf("CPF: %s\n", Clientes_Banco->lista[i].CPF);
            printf("Tipo de conta: %s\n\n", Clientes_Banco->lista[i].Tipo_conta);
        }
        printf("==============\n");
    }
}

Clientes* transferencia(Clientes* Clientes_Banco) { //Funcao que realiza a transferencia

    printf("Digite O Seu CPF: "); //Recebe CPF de origem
    strcpy(CPF_Cliente, solicitaCPF(Clientes_Banco));

    if (strcmp(CPF_Cliente, "Finalizar") != 0) {

        int posicao_cliente_origem = buscaCPF(Clientes_Banco,
                                              CPF_Cliente); // Busca a posicao que o cliente esta na lista por meio do CPF

        printf("Digite Sua Senha: "); // Recebe a senha do usuario
        char *senha_verificada = solicitaSenha(Clientes_Banco, posicao_cliente_origem);

        if (strcmp(senha_verificada, "CLIENT_ERROR") ==
            0) { //Caso o cliente tenha ultrapassado o limite de tentativas para inserir a senha,a operacao eh encerrada
            printf("Limite de tentativas excedido.\n");
            printf("Operacao finalizada.\n");
            return Clientes_Banco;
        } else {
            printf("Digite O CPF Do Destinatario: "); //Recebe o CPF do destinatario
            strcpy(CPF_Destinatario, solicitaCPF(Clientes_Banco));

            if (strcmp(CPF_Cliente, "Finalizar") != 0) {

                printf("Digite A Quantidade A Ser Tranferida: "); //Solicita o valor que deseja transferir
                scanf_s("%lf", &Valor_Operacao);

                int posicao_cliente_destino = buscaCPF(Clientes_Banco,
                                                       CPF_Destinatario); // Busca a posicao que o destinatario esta na lista

                int tipo_cliente = verifica_saldo(Clientes_Banco->lista[posicao_cliente_origem].Tipo_conta,
                                                  Clientes_Banco->lista[posicao_cliente_origem].Saldo,
                                                  Valor_Operacao); //Variavel que retorna 0 caso o cliente nao tenha saldo suficiente para realizar a operacao
                if (tipo_cliente == 0) {
                    printf("==============\n");
                    printf("Saldo insuficiente para realizar a operacao.\n");
                    printf("==============\n");
                    return Clientes_Banco;
                } else {
                    double Taxas;

                    if (tipo_cliente == 1) { //Calculo da taxa caso o cliente for do tipo comum
                        Taxas = Valor_Operacao * 0.05;
                    } else {
                        Taxas = Valor_Operacao * 0.03; //Calculo da taxa caso o cliente for do tipo plus
                    }

                    Clientes_Banco->lista[posicao_cliente_origem].Saldo -= (Valor_Operacao +
                                                                            Taxas); //Execucao da tranferencia
                    Clientes_Banco->lista[posicao_cliente_destino].Saldo += Valor_Operacao;

                    int posicao_extrato_origem = Clientes_Banco->lista[posicao_cliente_origem].Quantidade_Extrato;
                    if(Clientes_Banco->lista[posicao_cliente_origem].Quantidade_Extrato == 99) //Caso o limite de historico de extrato seja atingido, ele comeca a alterar as operacoes mais antigas
                        Clientes_Banco->lista[posicao_cliente_origem].Quantidade_Extrato = 0;
                    else
                        Clientes_Banco->lista[posicao_cliente_origem].Quantidade_Extrato++;

                    int posicao_extrato_destino = Clientes_Banco->lista[posicao_cliente_destino].Quantidade_Extrato;
                    if(Clientes_Banco->lista[posicao_cliente_destino].Quantidade_Extrato == 99) //Caso o limite de historico de extrato seja atingido, ele comeca a alterar as operacoes mais antigas
                            Clientes_Banco->lista[posicao_cliente_destino].Quantidade_Extrato = 0;
                    else
                        Clientes_Banco->lista[posicao_cliente_destino].Quantidade_Extrato++;

                    //Adiciona no extrato de cada cliente a operacao realizada
                    Clientes_Banco->lista[posicao_cliente_origem].extrato[posicao_extrato_origem] = adiciona_transacao(
                            "Transferencia", "-", Valor_Operacao, Taxas,
                            Clientes_Banco->lista[posicao_cliente_origem].Saldo);
                    Clientes_Banco->lista[posicao_cliente_destino].extrato[posicao_extrato_destino] = adiciona_transacao(
                            "Transferencia", "+", Valor_Operacao, 0,
                            Clientes_Banco->lista[posicao_cliente_destino].Saldo);

                    printf("==============\n");
                    printf("Operacao realizada com sucesso !\n");
                    printf("Saldo atual apos a operacao: R$ %.2lf\n",
                           Clientes_Banco->lista[posicao_cliente_origem].Saldo);
                    printf("==============\n");
                }
            }
        }
    }
    return Clientes_Banco;
}

Clientes* debitar(Clientes* Clientes_Banco) {

    printf("Digite seu CPF: "); // Recebe o CPF do cliente
    strcpy(CPF_Cliente, solicitaCPF(Clientes_Banco));

    if (strcmp(CPF_Cliente, "Finalizar") != 0) {

        int posicao_cliente = buscaCPF(Clientes_Banco, CPF_Cliente); //Busca a posicao do cliente na lista do banco

        printf("Digite Sua Senha: "); // Recebe a senha do usuario
        char *senha_verificada = solicitaSenha(Clientes_Banco, posicao_cliente);

        if (strcmp(senha_verificada, "CLIENT_ERROR") ==
            0) { //Caso o cliente tenha ultrapassado o limite de tentativas para inserir a senha,a operacao eh encerrada
            printf("Limite de tentativas excedido.\n");
            printf("Operacao finalizada.\n");
            return Clientes_Banco;
        } else {

            printf("Digite o valor que deseja debitar da conta: ");
            scanf_s("%lf", &Valor_Operacao);

            int tipo_cliente = verifica_saldo(Clientes_Banco->lista[posicao_cliente].Tipo_conta,
                                              Clientes_Banco->lista[posicao_cliente].Saldo,
                                              Valor_Operacao); //Verifica o tipo do cliente

            if (tipo_cliente == 0) { //Caso o cliente nao tenha saldo suficiente a operacao eh encerrada
                printf("==============\n");
                printf("Saldo insuficiente para realizar a operacao.\n");
                printf("==============\n");

            } else {
                double Taxas;

                if (tipo_cliente == 1) { //Calculo de taxa da operacao caso o cliente for comum
                    Taxas = Valor_Operacao * 0.05;
                } else {
                    Taxas = Valor_Operacao * 0.03; //Calculo de taxa da operacao caso o cliente for plus
                }

                Clientes_Banco->lista[posicao_cliente].Saldo -= (Valor_Operacao +
                                                                 Taxas); //Deposita o valor da conta do cliente

                int posicao_extrato = Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato;
                if (Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato ==
                    99) //Caso o limite de historico de extrato seja atingido, ele comeca a alterar as operacoes mais antigas
                    Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato = 0;
                else
                    Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato++;

                Clientes_Banco->lista[posicao_cliente].extrato[posicao_extrato] = adiciona_transacao("Deposita", "-",
                                                                                                     Valor_Operacao,
                                                                                                     Taxas,
                                                                                                     Clientes_Banco->lista[posicao_cliente].Saldo); //Adiciona a operacao na lista de extrato do cliente
                printf("==============\n");
                printf("Operacao realizada com sucesso !\n");
                printf("Saldo atual apos a operacao: R$ %.2lf\n",
                       Clientes_Banco->lista[posicao_cliente].Saldo); //Mostra o saldo do cliente apos a operacao
                printf("==============\n");
            }
        }
    }
    return Clientes_Banco;
}

Clientes* deposita(Clientes* Clientes_Banco) {

    printf("Digite O Seu CPF: "); //Recebe o CPF do cliente
    strcpy(CPF_Cliente, solicitaCPF(Clientes_Banco));

    if (strcmp(CPF_Cliente, "Finalizar") != 0) {

        printf("Digite o valor que deseja depositar em sua conta: "); //Recebe o valor do deposito
        scanf_s("%lf", &Valor_Operacao);

        int posicao_cliente = buscaCPF(Clientes_Banco, CPF_Cliente); //Busca pelo indice do cliente na lista do banco

        Clientes_Banco->lista[posicao_cliente].Saldo += Valor_Operacao;

        int posicao_extrato = Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato;

        if(Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato == 99) //Caso o limite de historico de extrato seja atingido, ele comeca a alterar as operacoes mais antigas
            Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato = 0;
        else
            Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato++;

        Clientes_Banco->lista[posicao_cliente].extrato[posicao_extrato] = adiciona_transacao("Deposita", "+",
                                                                                              Valor_Operacao, 0,Clientes_Banco->lista[posicao_cliente].Saldo);
        printf("==============\n");
        printf("Operacao realizada com sucesso !\n");
        printf("Saldo atual apos a operacao: R$ %.2lf\n", Clientes_Banco->lista[posicao_cliente].Saldo);
        printf("==============\n");

    }
    return Clientes_Banco;
}

void gerar_extrato(Clientes* Clientes_Banco) { //Cria um arquivo .txt com o tendo como nome o CPF do usuario, ordena das operacoes mais recentes ate as mais antigas, ao alcancar o limite as opercoes mais antigas sao trocadas pelas mais novas
    printf("Digite O Seu CPF: "); //Recebe o CPF do cliente
    strcpy(CPF_Cliente, solicitaCPF(Clientes_Banco));

    if (strcmp(CPF_Cliente, "Finalizar") != 0) {

        int posicao_cliente = buscaCPF(Clientes_Banco, CPF_Cliente); //Busca o indice do cliente na lista do banco

        printf("Digite Sua Senha: "); //Recebe a senha do usuario
        char *senha_verificada = solicitaSenha(Clientes_Banco, posicao_cliente);

        if (strcmp(senha_verificada, "CLIENT_ERROR") ==
            0) { //Caso o cliente tenha ultrapassado o limite de tentativas a operacao eh encerrado
            printf("Limite de tentativas excedido.\n");
            printf("Operacao finalizada.\n");
        } else {
            //Realiza a escrita de todas as operacoes do cliente no arquivo
            strcat(CPF_Cliente, ".txt");
            FILE *arquivo_extrato = fopen(CPF_Cliente, "w");
            fprintf(arquivo_extrato, "Nome do cliente: %s\n", Clientes_Banco->lista[posicao_cliente].nome);
            fprintf(arquivo_extrato, "CPF do cliente: %s\n", Clientes_Banco->lista[posicao_cliente].CPF);
            fprintf(arquivo_extrato, "Tipo de conta do cliente: %s\n",
                    Clientes_Banco->lista[posicao_cliente].Tipo_conta);
            fprintf(arquivo_extrato, "==============\n");

            for (int i = Clientes_Banco->lista[posicao_cliente].Quantidade_Extrato - 1 ; i >= 0 ; i--) {
                fprintf(arquivo_extrato, "Transacao %d:\n", i + 1);
                fprintf(arquivo_extrato, "Operacao realizada: %s\n",
                        Clientes_Banco->lista[posicao_cliente].extrato[i].Operacao);
                fprintf(arquivo_extrato, "Valor movimentado: R$ %s",
                        Clientes_Banco->lista[posicao_cliente].extrato[i].Simbolo);
                fprintf(arquivo_extrato, "%.2lf\n", Clientes_Banco->lista[posicao_cliente].extrato[i].Valor);
                fprintf(arquivo_extrato, "Taxa aplicada na operacao: R$ %.2lf\n\n",
                        Clientes_Banco->lista[posicao_cliente].extrato[i].Taxa);
                fprintf(arquivo_extrato, "*Saldo na conta apos a transacao: R$ %.2lf\n\n",
                        Clientes_Banco->lista[posicao_cliente].extrato[i].Saldo_Momento);
            }
            fprintf(arquivo_extrato, "\n==============\n\n");
            fclose(arquivo_extrato);
        }
    }
}

char* input_string(char* str) { //Funcao para receber strings sem dar bugs
    int c;
    scanf("%[^\n]s", str); //Recebe o array de chars/string
    while ((c = getchar()) != '\n' && c != EOF) {} //Impede Que Sejam Pulados input futuros após ser pressionada a tecla "enter"

    return str;
}

int verifica_saldo(char* Tipo_conta, double saldo_atual, double valor_operacao) { //Funcao para verificar o tipo do cliente e verificar se o mesmo possui saldo suficiente para realizar a operacao
    if (strcmp(Tipo_conta, "Comum") == 0 || strcmp(Tipo_conta, "Comum") == 0) {
        if (saldo_atual - valor_operacao * 1.05 >= -1000) // A funcao retorna 1 caso o cliente for do tipo comum e ter saldo suficiente e 0 caso nao tenha
            return 1;
        else
            return 0;
    }
    else {
        if (saldo_atual - valor_operacao * 1.03 >= -5000)
            return 2; // A funcao retorna 1 caso o cliente for do tipo comum e ter saldo suficiente e 0 caso nao tenha
        else
            return 0;
    }
}

Extrato adiciona_transacao(char* Operacao, char* Simbolo, double Valor_Movimentado, double Taxa, double Saldo_Atual) { //Funcao que retorna um struct Extrato com todas as informacoes da operacao
    Extrato trasacao_temp;
    strcpy(trasacao_temp.Operacao, Operacao);
    strcpy(trasacao_temp.Simbolo, Simbolo);
    trasacao_temp.Valor = Valor_Movimentado;
    trasacao_temp.Taxa = Taxa;
    trasacao_temp.Saldo_Momento = Saldo_Atual;
    return trasacao_temp;
}

int buscaCPF(Clientes* Clientes_Banco, char* CPF) { //Busca a posicao do cliente no banco e retorna -1 caso o cliente nao tenha sido encontrado

    for (int i = 0; i < Clientes_Banco->Quantidade_Clientes; i++) {
        if (strcmp(Clientes_Banco->lista[i].CPF, CPF) == 0) {
            return i;
        }
    }
    return -1;
}

int buscaSenha(Clientes* Clientes_Banco, int posicao_cliente, char* Senha) { //Verifica que o cliente inseriu esta correta

    if (strcmp(Clientes_Banco->lista[posicao_cliente].Senha, Senha) == 0)
        return 1; //Retorna 1 se esta correta e 0 caso nao
    else
        return 0;
}

char* solicitaCPF(Clientes* Clientes_Banco) { //Funcao para realizar input de CPF e verificar se o mesmo eh valido
    int verifica;

    while (true) {
        input_string(CPF_Cliente);
        verifica = buscaCPF(Clientes_Banco, CPF_Cliente);

        if(strcmp(CPF_Cliente , "Finalizar") == 0 || verifica != -1)
            break;
        else
            printf("CPF nao existente no banco, escreva novamente o CPF ou escreva 'Finalizar' para encerrar a operacao.\n");
    }
    return CPF_Cliente;
}

char* solicitaSenha(Clientes* Clientes_Banco, int Posicao_Cliente) { //Funcao receber a senha do cliente e limitar a quantidade de tentativas
    int verifica;
    int erros_cliente = 3;

    while (true) {
        input_string(Senha_Cliente);
        verifica = buscaSenha(Clientes_Banco, Posicao_Cliente, Senha_Cliente);
        if (erros_cliente == 0 || verifica == 1)
            break;
        else {
            printf("Senha incorreta, possui mais %d tentativas: ", erros_cliente);
            erros_cliente--;
        }
    }
    if (erros_cliente == 0) {
        return "CLIENT_ERROR";
    }
    else {
        return "CORRECT_PASSWORD";
    }
}