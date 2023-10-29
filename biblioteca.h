//Paulo Gabriel Gonçalves Leme | R.A: 21.123.075.4
//Gabriel Albertini Pinheiro | R.A: 24.123.004-4
#ifndef PROJETO_2_BIBLIOTECA_H
#define PROJETO_2_BIBLIOTECA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char Operacao[20];
    double Valor;
    double Taxa;
    double Saldo_Momento;
    char Data_Hora[30];
    char Simbolo[2];
} Extrato;

typedef struct{
    char nome[100];
    char CPF[15];
    char Tipo_conta[10];
    double Saldo;
    char Senha[50];
    Extrato extrato[100];
    int Quantidade_Extrato;
} Dados;

typedef struct{
    Dados lista[1000];
    int Quantidade_Clientes;
} Clientes;


Clientes* leitura(char *nome);
void escreve(Clientes *v , char *nome);
int menu();
Clientes* cadastrar(Clientes* usuarios);
Clientes* deletar_cliente(Clientes* usuarios);
void listar_clientes(Clientes* usuarios);
Clientes* debitar(Clientes* usuarios);
Clientes* transferencia(Clientes* usuarios);
Clientes* deposita(Clientes* usuarios);
void gerar_extrato(Clientes* usuarios);
char* input_string(char *str);
int verifica_saldo(char* Tipo_conta , double saldo_atual , double valor_operacao);
Extrato adiciona_transacao(char* Operacao, char* Simbolo, double Valor_Movimentado, double Taxa , double Saldo_Atual);
int buscaCPF(Clientes* usuarios, char* CPF);
int buscaSenha(Clientes* usuarios , int posicao_cliente , char* Senha);
char* solicitaCPF(Clientes* Clientes_Banco);
char* solicitaSenha(Clientes* Clientes_Banco , int Posicao_Cliente);

#endif //PROJETO_2_BIBLIOTECA_H
