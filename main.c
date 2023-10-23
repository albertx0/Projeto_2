#include "biblioteca.h"

int main(){
  char nome[50];
  char CPF[15];//CPF do usuário de origem
  char CPF_destinatario[15];//CPF do destinatário
  char tipo_conta[10];
  double saldo;
  char senha[50];
  int opcao=0; //Variavel de seleção
  double valor_operacao;//Quantidade à serem debitadas ou transferidas
  
  Clientes* lista_clientes = leitura("arquivo_clientes.txt");

  printf("tam = %d\n" , lista_clientes->qtd);



    do{

    menu();
    scanf("%d",&opcao);

    while (getchar() != '\n');
    if(opcao==1){
        printf("==============\n");
        printf("Digite o nome do cliente: ");
        input(nome);
        printf("Digite o CPF do cliente: ");
        input(CPF);
        printf("Digite a senha do cliente: ");
        input(senha);
        printf("Digite o tipo de conta do cliente: ");
        input(tipo_conta);
        printf("Digite o saldo inicial da conta: ");
        scanf("%lf", &saldo);
        cadastrar(lista_clientes , nome,saldo,CPF,tipo_conta,senha);
        printf("==============\n");
    }
    else if(opcao==2){
        printf("Digite o CPF do cliente que deseja apagar: ");
        input(CPF);
        lista_clientes = deletar_cliente(lista_clientes , CPF);
    }
    else if(opcao==3){
      listar_clientes(lista_clientes);
    }
    else if(opcao==4){
      printf("Digite seu CPF: ");
      input(CPF);
      printf("Digite sua senha: ");
      input(senha);
      printf("Digite o valor a ser debitado da conta: ");
      scanf("%lf",&valor_operacao);
      debitar( valor_operacao , CPF , senha);
    }else if(opcao == 5){
        printf("Digite seu CPF: ");
        input(CPF);
        printf("Digite o valor que deseja depositar em sua conta: ");
        scanf("%lf" , &valor_operacao);
        lista_clientes = deposita(lista_clientes , CPF ,valor_operacao);
    }
    else if(opcao==7){
      printf("Digite O Seu CPF: ");
      input(CPF);
      printf("Digite Sua Senha: ");
      input(senha);
      printf("Digite O CPF Do Destinatario: ");
      input(CPF_destinatario);
      printf("Digite A Quantidade A Ser Tranferida: ");
      scanf("%lf",&valor_operacao);
      transferencia(valor_operacao ,CPF ,CPF_destinatario ,senha);
    }

    printf("\n");
  }while(opcao !=8 );

  escreve(lista_clientes , "arquivo_clientes.txt");
  printf("Obrigado Por Escolher QuemPoupaTem!\n");
  
  
    return 0;

}