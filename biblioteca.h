//
// Created by unifgpinheiro on 29/09/2023.
//

#ifndef PROJETO_2_BIBLIOTECA_H
#define PROJETO_2_BIBLIOTECA_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char nome[100];
    char CPF[15];
    char Tipo_conta[10];
    double Saldo;
    char Senha[50];
} Dados;

typedef struct{
    Dados lista[1000];
    int qtd;
} Clientes;



void cadastrar(char *nome, double saldo, char *CPF, char *tc, char *senha);
Clientes* deletar_cliente(Clientes* usuarios , char* CPF);
void listar();
void debitar(double qtd,char *CPF,char *senha);
void transferencia(double qtd,char *cpfa, char *cpfd,char *senha);
void menu();
void input(char *str);


#endif //PROJETO_2_BIBLIOTECA_H
