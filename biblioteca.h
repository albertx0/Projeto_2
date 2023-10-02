//
// Created by unifgpinheiro on 29/09/2023.
//

#ifndef PROJETO_2_BIBLIOTECA_H
#define PROJETO_2_BIBLIOTECA_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char operacao[20];
    double valor;
    double taxa;
    int hora;
    int minuto;
    int segundo;
    int dia;
    int mes;
    int ano;
} Extrato;

typedef struct{
    char nome[100];
    char CPF[15];
    char Tipo_conta[10];
    double Saldo;
    char Senha[50];
    int qtd_extrato;
    Extrato extrato[1000];
} Dados;

typedef struct{
    Dados lista[1000];
    int qtd;
} Clientes;



void menu();
Clientes* deletar_cliente(Clientes* usuarios , char* CPF);
void listar_clientes(Clientes* usuarios);
Clientes* deposita(Clientes* usuarios , char* CPF , double valor);
int buscaCPF(Clientes* usuarios, char* CPF);
Extrato adiciona_transacao(char* operacao , double valor , double taxa);

#endif //PROJETO_2_BIBLIOTECA_H
