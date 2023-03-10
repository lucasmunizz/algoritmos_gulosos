// MATHEUS SALERMO GUIRAO   13719941

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h> 

typedef struct{
    int indice;
    int valorDuracao;
    bool acontecendo;
}ATUALIZACOES;



void ordenar(ATUALIZACOES l[], int tam){ 
    int i, j;
    ATUALIZACOES aux;
    for (i = 1; i < tam; i++){
        aux = l[i];
        j = i - 1;
        while ((j >= 0) && (aux.valorDuracao < l[j].valorDuracao)){
            l[j + 1] = l[j];
            j--;
        }
        l[j + 1] = aux;
    }
}

void ordenar2(ATUALIZACOES l[], int tam){ 
    int i, j;
    ATUALIZACOES aux;
    for (i = 1; i < tam; i++){
        aux = l[i];
        j = i - 1;
        while ((j >= 0) && (aux.valorDuracao < l[j].valorDuracao) && l[j].acontecendo == false){
            l[j + 1] = l[j];
            j--;
        }
        l[j + 1] = aux;
    }
}


int nAtualizacoes(ATUALIZACOES l[], int horas, int qtd){
    int i, soma = 0,  quantidade = 0;
    for(i = 0 ; i < qtd ; i++){
        soma = soma + l[i].valorDuracao;
        if(soma > horas){
            break;
        }
        quantidade++;
    }
    return quantidade;
}


int main(int argc, char* argv[]) {
    /*
    argv[0] = nome do arquivo exe
    argv[1] = horas
    argv[2] = cenario
    argv[3]  = texto
    */
    int quantidade, valor;
    int horas = atoi(argv[1]);
    int cenario = atoi(argv[2]);
    

    if(cenario == 1){
        FILE* file;
        file = fopen(argv[3],"r");
        fscanf(file, "%i", &quantidade);
        ATUALIZACOES lista[quantidade]; 
        int i;
        for(i=0; i<quantidade;i++){
            fscanf(file, "%i", &valor);
            lista[i].valorDuracao = valor;
            lista[i].indice = i+1;
            lista[i].acontecendo = false;
        }
        fclose(file);
        ordenar(lista, quantidade);
        int nAtt = nAtualizacoes(lista, horas, quantidade);
        file = fopen("saida1.txt", "w");
        fprintf(file, "%i ", nAtt);
        for(i=0; i<nAtt;i++){
            fprintf(file, "%i ", lista[i].indice);
        }
        fprintf(file, "\n");
        fclose(file);
    }

    else if(cenario == 2){
        FILE* file;
        file = fopen(argv[3],"r");
        fscanf(file, "%i", &quantidade);
        ATUALIZACOES lista[quantidade]; 
        int i;
        for(i=0; i<quantidade;i++){
            fscanf(file, "%i", &valor);
            lista[i].valorDuracao = valor;
            lista[i].indice = i+1;
            lista[i].acontecendo = false;
        }
        ordenar(lista, quantidade);
        char rotina;
        while(fscanf(file, " %c", &rotina) != EOF) {
            int novaAttHora = 0;
            int novaAttIndice = 0;
            int novaAttDuracao = 0;
            if(rotina == 'c'){                
                fscanf(file, "%i %i %i\n", &novaAttHora, &novaAttIndice, &novaAttDuracao);
                if(novaAttHora > 1){
                    lista[0].acontecendo = true;    
                }
                int somaHora=0;
                for(i = 0; i < quantidade; i++){
                    somaHora = somaHora + lista[i].valorDuracao;
                    if(somaHora > novaAttHora){
                        lista[i].acontecendo = true;
                        break;
                    } 
                    lista[i].acontecendo = true;
                }
                for(i=0; i<quantidade; i++){
                    if(lista[i].indice == novaAttIndice){
                        lista[i].valorDuracao = novaAttDuracao;
                    }
                }
                ordenar2(lista,quantidade);
            }
            else if(rotina == 'i'){
                fscanf(file, "%i %i %i\n", &novaAttHora, &novaAttIndice, &novaAttDuracao);
                quantidade++;
                int nroIndice = novaAttIndice - 1;
                lista[nroIndice].valorDuracao = novaAttDuracao;
                lista[i].indice = i+1;
                lista[i].acontecendo = false;
                ordenar2(lista,quantidade);  
            } 
        }
        fclose(file);
        int nAtt = nAtualizacoes(lista, horas, quantidade);
        file = fopen("saida2.txt", "w");
        fprintf(file, "%i ", nAtt);
        for(i=0; i<nAtt;i++){
            fprintf(file, "%i ", lista[i].indice);
        }
        fprintf(file, "\n");
        fclose(file);
        }
    }