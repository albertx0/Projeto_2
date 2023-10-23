#include "biblioteca.h"

int main(){
  char nome[50];
  char CPFu[15];//CPF do usuário
  char CPFd[15];//CPF do destinatário
  char tipo_conta[10];
  double saldo;
  char senha[50];
  int s=0; //Variavel de selção
  double qtd=0;//Quantidade à serem debitadas ou transferidas
  

  
  do{
    printf("----------------------------\n\n");
    menu();
    scanf("%d",&s);
    printf("\n----------------------------\n\n");
    while (getchar() != '\n');
    if(s==1){
        printf("----------------------------\n");
        printf("Digite O Nome: ");
        input(nome);
        printf("Digite O CPF: ");
        input(CPFu);
        printf("Digite A Senha: ");
        input(senha);
        printf("Digite O Tipo De Conta: ");
        input(tipo_conta);
        printf("Digite O Saldo Incial: ");
        scanf("%lf",&saldo);
        cadastrar(nome,saldo,CPFu,tipo_conta,senha);
        printf("----------------------------\n");
    }
    else if(s==2){
        //deletar_cliente();
    }
    else if(s==3){
      listar();
    }
    else if(s==4){
      printf("Digite O Seu CPF: ");
      input(CPFu);
      printf("Digite A Sua Senha: ");
      input(senha);
      printf("Digite A Quantidade A Ser Debitada: ");
      scanf("%lf",&qtd);
      debitar(qtd,CPFu,senha); 
    }
    else if(s==7){
      printf("Digite O Seu CPF: ");
      input(CPFu);
      printf("Digite Sua Senha: ");
      input(senha);
      printf("Digite O CPF Do Destinatario: ");
      input(CPFd);
      printf("Digite A Quantidade A Ser Tranferida: ");
      scanf("%lf",&qtd);
      transferencia(qtd,CPFu,CPFd,senha);
    }

    printf("\n");
  }while(s!=8);

  printf("Obrigado Por Escolher Quem Poupa Tem!\n");
  
  
    return 0;
}