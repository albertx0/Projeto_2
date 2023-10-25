//
// Created by unifgpinheiro on 29/09/2023.
//

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
    char Data_Hora[30];
    /*
    int Hora;
    int Minuto;
    int Segundo;
    int Dia;
    int Mes;
    int Ano;
     */
} Extrato;

typedef struct{
    char nome[100];
    char CPF[15];
    char Tipo_conta[10];
    double Saldo;
    char Senha[50];
    Extrato extrato[1000];
    int qtd_extrato;
} Dados;

typedef struct{
    Dados lista[1000];
    int qtd;
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
void listar_extrato(Clientes* usuarios);
char* input(char *str);
int verifica_saldo(char* Tipo_conta , double saldo_atual , double valor_operacao);
Extrato adiciona_transacao(char* operacao , double valor , double taxa);
int buscaCPF(Clientes* usuarios, char* CPF);
int buscaSenha(Clientes* usuarios , int posicao_cliente , char* Senha);




#endif //PROJETO_2_BIBLIOTECA_H
