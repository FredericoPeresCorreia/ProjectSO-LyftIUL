#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include "funcgerais.h"
int nViagens;
int viagensEscritas;
int alterado = 0;

void trataViagens(char viagem[]){
    int matches = 0, i = 0;
    char buf [10];
    obter_substring(viagem,buf,':',1);
    int numCondutor = atoi(buf);
    obter_substring(viagem,buf,':',2);
    int numPassageiro = atoi(buf);
    obter_substring(viagem,buf,':',3);
    int pontos = atoi(buf);
    obter_substring(viagem,buf,':',4);
    float valorViagem = atof(buf);
    
    while(matches!=1 && i < nCondutores){
        if(condutores[i].numero == numCondutor){
            matches=1;
        }
        i++;
    } 

    if(matches == 1){
        condutores[i-1].pontos+=pontos;
        condutores[i-1].saldo+=valorViagem;
        condutores[i-1].viagens++;
        alterado = 1;
    } else {
        printf("O condutor não existe na base de dados (%d)\n",numCondutor);
    }
}

void lerViagens(){
    FILE *f;
    criarCondutores();
    char viagem[100];
    if ( access(fnameViagens, R_OK) == 0){
        f = fopen(fnameViagens, "r");
            while(fgets(viagem,sizeof(viagem), f)){               
                trataViagens(viagem);
                nViagens++;
            }  
        fclose(f); 
        remove(fnameViagens);
     }
} 

void enviarSinal(){ 
    FILE *f;
    char line[100];
    if(access(fnamePID,R_OK)==0){    
        f = fopen(fnamePID, "r");
        fgets(line,sizeof(line),f);
        int PID = atoi(line);
        kill(SIGUSR1,PID);  
        fclose(f); 
    }else{
        printf("não conseguimos aceder ao ficheiro\n");
    }
}


void main() { 
   printf("A verificar viagens");
   lerViagens();
   if(alterado == 1){
       rescreveCondutores();
       enviarSinal();
   }
} 





