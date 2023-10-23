#include "biblioteca.h"

void cadastrar(char *nome, double saldo, char *CPF, char *tc, char *senha){
    Dados pessoa;

    // Verifica se as strings não excedem os limites das strings
    if (strlen(nome) >= 100 || strlen(CPF) >= 15 || strlen(tc) >= 10 || strlen(senha) >= 50) {
        printf("Erro: uma ou mais strings ultrapassaram os limites de tamanho.\n");
        return;
    }
    //Copia as variaveis do struct para as variaveis da função
    strcpy(pessoa.nome, nome);
    strcpy(pessoa.CPF, CPF);
    strcpy(pessoa.Tipo_conta, tc);
    pessoa.Saldo = saldo;
    strcpy(pessoa.Senha, senha);

    // Abrindo o arquivo para escrita binária
    FILE *arquivo = fopen("dados.bin", "ab");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        printf("Erro Ao Abrir o Arquivo\n");
    }

    // Escrevendo a estrutura no arquivo
    size_t elementos_gravados = fwrite(&pessoa, sizeof(Dados), 1, arquivo);

    if (elementos_gravados != 1) {
        printf("Erro ao escrever no arquivo.\n");
        fclose(arquivo);
        // Termina a execução em caso de erro
    }

    // Fechando o arquivo
    fclose(arquivo);
  
  
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

void listar(){
    FILE* arquivo = fopen("dados.bin", "rb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        printf("Erro Ao Abrir O Arquivo\n");
    }

    Dados pessoa_lida;

    int c=0;
    /*Enquanto todos os dados do arquvo não tiverem
    Passado Pelo Struc Dados o Programa Continua Printando os Dados dos             Clintes(exceto as senhas)*/
    while (fread(&pessoa_lida, sizeof(Dados), 1, arquivo) == 1) {
        printf("Cliente Numero %d:\n", c + 1);
        printf("Nome: %s\n", pessoa_lida.nome);
        printf("CPF: %s\n", pessoa_lida.CPF);
        printf("Tipo De Conta: %s\n", pessoa_lida.Tipo_conta);
        printf("Saldo : R$ %0.2lf\n",pessoa_lida.Saldo);
        printf("\n");
        c++;
    }

}

void debitar(double qtd,char *CPF,char *senha){
  int v=0;//Verifica se foram encontrados os dados
  FILE* f = fopen("dados.bin","rb+");

  Dados pessoa_lida;
  

  if (f == NULL) {
      perror("Erro ao abrir o arquivo");
      printf("Erro Ao Abrir O Arquivo\n");
  }
  
  while (fread(&pessoa_lida, sizeof(Dados), 1, f) == 1) {
    if(strcmp(pessoa_lida.CPF,CPF)==0 && strcmp(pessoa_lida.Senha,senha)==0){
        pessoa_lida.Saldo = pessoa_lida.Saldo - qtd;
        fseek(f,-sizeof(Dados),SEEK_CUR);
        fwrite(&pessoa_lida,sizeof(Dados),1,f);
        v=1;
        break;
      }
    
  }
  if(v==0){
    printf("----------------------------\n\n");
    printf("CPF E/Ou Senha Incorreto(s)\n");
    printf("Tente Novamente\n\n");
    printf("----------------------------\n\n");
  }
  fclose(f);
  
}

void transferencia(double qtd,char *cpfa, char *cpfd,char *senha);
