#include "biblioteca.h"

int main(){

    while(true){
        int opcao;

        menu();

        scanf("%d" , &opcao);

        if(opcao == 1){
            //CadastrarCliente();
        }else if(opcao == 2){
            //deletar_cliente();
        }else if(opcao == 3){
            //listar_clientes();
        }else if(opcao == 4){
            //debitar();
        }else if(opcao == 5){
            //deposita();
        }else if(opcao == 6){
            //extrato();
        }else if(opcao == 7){
            //treanferencia();
        }else if(opcao == 8){
            //escreve();
            break;
        }
    }

}