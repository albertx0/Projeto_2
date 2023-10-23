#include "biblioteca.h"


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


void menu(){
    printf("Bem vindo ao banco QuemPoupaTem !");
    printf("1 - Cadastrar Clientes.\n");
    printf("2 - Apagar Cliente.\n");
    printf("3 - Listar todos os clientes.\n");
    printf("4 - Debitar valor de um cliente.\n");
    printf("5 - Depositar dinheiro.\n");
    printf("6 - Visualizar extrato.\n");
    printf("7 - Transfrencia.\n");

    printf("8 - Sair.\n\n");
    printf("Digite o numero da opcao desejada: ");
}

Clientes* cadastrar(Clientes* usuarios, char *nome, double saldo_inicial, char *CPF, char *tipo_conta, char *senha){

    int nova_posicao = usuarios->qtd;

    //Copia as variaveis do struct para as variaveis da função
    strcpy(usuarios->lista[nova_posicao].nome , nome);
    strcpy(usuarios->lista[nova_posicao].CPF, CPF);
    strcpy(usuarios->lista[nova_posicao].Tipo_conta, tipo_conta);
    usuarios->lista[nova_posicao].Saldo = saldo_inicial;
    strcpy(usuarios->lista[nova_posicao].Senha, senha);
    usuarios->qtd++;

    return usuarios;
}

Clientes* deletar_cliente(Clientes* usuarios , char* CPF){
    Clientes* usuarios_temp = (Clientes*)malloc(1000*sizeof(Clientes));

    int posicao = buscaCPF(usuarios , CPF);
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

void debitar(double qtd,char *CPF,char *senha){
  int v=0;//Verifica se foram encontrados os dados
  FILE* f = fopen("dados.bin","rb+");

  Dados pessoa_lida; //Forma como os dados do struct serão lidos pelo código dentro da função

  //Se o aruivo não existir para a função
  if (f == NULL) {
      perror("Erro ao abrir o arquivo");
      printf("Erro Ao Abrir O Arquivo\n");
  }
  //Enquanto o arquivo não for inteiramente lido, o while não para
  while (fread(&pessoa_lida, sizeof(Dados), 1, f) == 1) {
    if(strcmp(pessoa_lida.CPF,CPF)==0 && strcmp(pessoa_lida.Senha,senha)==0){
        pessoa_lida.Saldo = pessoa_lida.Saldo - qtd;
        fseek(f,sizeof(Dados),SEEK_CUR);
        fwrite(&pessoa_lida,sizeof(Dados),1,f);
        v=1;
        break;
      }

  }
  //Em caso de a(s) informação(ões) estiver(em) incorreta(s) ou inexistente(s), informa o usuaria com as mensagens
  if(v==0){
    printf("----------------------------\n\n");
    printf("CPF E/Ou Senha Incorreto(s)\n");
    printf("Tente Novamente\n\n");
    printf("----------------------------\n\n");
  }
  fclose(f);

}

void transferencia(double qtd,char *cpfu, char *cpfd,char *senha){
    int v = 0; // Int verifica de a primeira condição foi cumprida
    FILE* f = fopen("dados.bin", "rb+");

    Dados pessoa_lida;  //Forma como os dados do struct serão lidos pelo código dentro da função

    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        printf("Erro Ao Abrir O Arquivo\n");
        return;
    }
    //Enquanto o arquivo não for inteiramente lido, o while não para
    //Enquanto o CPF do usuario e sua senha não for encontrado, o arquivo também continuará a ser lido
    //caso ele não seja encontado, a variavel verificadora não mudará de valor e não ativára o segundo loop
    while (fread(&pessoa_lida, sizeof(Dados), 1, f) == 1) {
        if (strcmp(pessoa_lida.CPF, cpfu) == 0 && strcmp(pessoa_lida.Senha, senha) == 0) {
            printf("Teste\n");
            pessoa_lida.Saldo = pessoa_lida.Saldo - qtd;
            fseek(f, sizeof(Dados), SEEK_CUR);
            fwrite(&pessoa_lida, sizeof(Dados), 1, f);
            v = 1;
            break;
        }
    }

    rewind(f);  // Retorna o ponteiro de leitura para o início do arquivo
    if(v==1){
        //Enquanto o arquivo não for inteiramente lido, o while não para
        //Enquanto não for achado o CPF do destinatário o loop não para
        while (fread(&pessoa_lida, sizeof(Dados), 1, f) == 1) {
            if (strcmp(pessoa_lida.CPF, cpfd) == 0) {
                printf("Teste\n");
                pessoa_lida.Saldo = pessoa_lida.Saldo + qtd;
                fseek(f, sizeof(Dados), SEEK_CUR);
                fwrite(&pessoa_lida, sizeof(Dados), 1, f);
                break;
            }
        }
    }
    else{
        printf("\n----------------------------\n\n");
        printf("CPF Do Usuário E/Ou Senha Incorretos E/Ou\n");
        printf("CPF De Destinatário Incorreto\n");
        printf("Tente Novamente\n");
        printf("\n----------------------------\n\n");
    }

    fclose(f);
}



char* input(char *str){
  scanf("%[^\n]s",str); //Recebe o array de chars/string

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } //Impede Que Sejam Pulados Inputs futuros após ser pressionada a tecla "enter"

    return str;
}

Clientes* deposita(Clientes* usuarios , char* CPF , double valor){

    int posicao = buscaCPF(usuarios , CPF);

    if(posicao == -1){
        printf("==============\n");
        printf("Nenhum cliente cadastrado com o CPF digitado.\n");
        printf("==============\n");

        return usuarios;
    }else {
        double taxas;
        if (strcmp(usuarios->lista[posicao].Tipo_conta, "Comum") == 0 || strcmp(usuarios->lista[posicao].Tipo_conta, "comum") == 0) {
            taxas = valor * 0.95;
        } else {
            taxas = valor * 0.97;
        }
        usuarios->lista[posicao].extrato[usuarios->lista[posicao].qtd_extrato] = adiciona_transacao("Deposito", valor, taxas);
        usuarios->lista[posicao].qtd_extrato++;

        printf("Operacao feita com sucesso !\n");
        return usuarios;
    }
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


