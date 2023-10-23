//
// Created by unifgpinheiro on 29/09/2023.
//

#ifndef PROJETO_2_BIBLIOTECA_H
#define PROJETO_2_BIBLIOTECA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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


Clientes* leitura(char *nome);
void escreve(Clientes *v , char *nome);
Clientes* cadastrar(Clientes* usuarios, char *nome, double saldo_inicial, char *CPF, char *tipo_conta, char *senha);
Clientes* deletar_cliente(Clientes* usuarios , char* CPF);
void listar();
void listar_clientes(Clientes* usuarios);
void debitar(double qtd,char *CPF,char *senha);
void transferencia(double qtd,char *cpfa, char *cpfd,char *senha);
void menu();
char* input(char *str);


#endif //PROJETO_2_BIBLIOTECA_H
