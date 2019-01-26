#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "funcgerais.h"



void updateCondutores(){
    FILE *f;
    char linha[200];
    int i = 0;
    char valor[10];
    
     if (access(fnameCondutores, R_OK)==0){
        f = fopen(fnameCondutores, "r");
            while(fgets(linha,sizeof(linha),f)){
                obter_substring(linha,valor,':',8);
                int viagens = atoi(valor);
                if(viagens != condutores[i].viagens){
                    condutores[i].viagens = viagens;
                }
                obter_substring(linha,valor,':',9);
                int pontos = atoi(valor);
                if(pontos != condutores[i].pontos){
                    condutores[i].saldo = pontos;
                }
                obter_substring(linha,valor,':',10);
                float saldo = atof(valor);
                if(saldo != condutores[i].saldo){
                    condutores[i].saldo = saldo;
                }
                i++;
            } 
         fclose(f); 
    }
}

void rescreveFicheiros(){
    rescreveCondutores();
    rescrevePassageiros();
    exit(0);
}

void imprimirMemoria(){
    char buf[200];
    for (int i = 0; i < nCondutores; i++){
        escreveCondutoresStr(buf,condutores[i]);
        printf("%s\n",buf);        
    }
    for (int i = 0; i < nPassageiros;i++){
        escrevePassageiroStr(buf, passageiros[i]);
        printf("%s\n",buf);
    }
    printf("\nNúmero de condutores: %d, número de passageiros: %d\n",nCondutores,nPassageiros);
}

void alterarPassageiro(){
    int numero; 
    int i=0;
    int matches=0;
    printf("Qual é o número do passageiro?\n");
    scanf("%d", &numero);
    ler_enter();
    while(matches!=1 && i < nPassageiros){
        if(passageiros[i].numero == numero){
            matches=1;
        }
        i++;
    } 
    if(matches==1){
        Tpassageiro passageiroNovo;
        printf("Qual o número novo\n");
        scanf("%d", &passageiroNovo.numero);
        ler_enter();
        printf("Qual o nome novo\n");
        scanf("%s", &passageiroNovo.nome);
        ler_enter();
        printf("Qual a turma nova\n");
        scanf("%s", &passageiroNovo.turma);
        ler_enter();
        printf("Qual o número de telemóvel novo\n");
        scanf("%s", &passageiroNovo.telemovel);
        ler_enter();
        printf("Qual o email novo\n");
        scanf("%s", &passageiroNovo.email);
        ler_enter();
        printf("Qual o cartão de crédito novo\n");
        scanf("%s", strcat(&passageiroNovo.c_credito,"\n\n"));
        passageiros[i-1] = passageiroNovo;      
    }else{
        printf("Não existe um passageiro com o número fornecido. (%d)\n",numero);
    }   
}

void alterarCondutor(){
    int numero; 
    int i=0;
    int matches=0;
    printf("Qual é o número do condutor?\n");
    scanf("%d", &numero);
    ler_enter();
    while(matches!=1 && i < nCondutores){
        if(condutores[i].numero == numero){
            matches=1;
        }
        i++;
    } 
    if(matches==1){
        Tcondutor condutorNovo;
        printf("Qual o número novo?\n");
        scanf("%d", &condutorNovo.numero);
        ler_enter();
        printf("Qual o nome novo?\n");
        scanf("%s", &condutorNovo.nome);
        ler_enter();
        printf("Qual a turma nova?\n");
        scanf("%s", &condutorNovo.turma);
        ler_enter();
        printf("Qual o número de telemóvel novo?\n");
        scanf("%s", &condutorNovo.telemovel);
        ler_enter();
        printf("Qual o email novo?\n");
        scanf("%s", &condutorNovo.email);
        ler_enter();
        printf("Qual o tipo do carro novo?\n");
        scanf("%s", &condutorNovo.tipo);
        ler_enter();
        printf("Qual a marca do carro novo?\n");
        scanf("%s", &condutorNovo.marca);
        ler_enter();
        printf("Qual a matrícula  do carro novo?\n");
        scanf("%s", &condutorNovo.matricula); 
        condutorNovo.viagens = condutores[i-1].viagens;
        condutorNovo.pontos = condutores[i-1].pontos;
        condutorNovo.saldo = condutores[i-1].saldo;
        condutores[i-1] = condutorNovo;      
    }else{
        printf("Não existe um condutor com o número fornecido. (%d)\n",numero);
    }   
}

void menu(){
    int opcao;
    do {
        printf ("1. Imprimir Memória\n" );
        printf ("2. Alterar Passageiro\n" );
        printf ("3. Alterar Condutor\n" );
        printf ("0. Sair \n" );
        printf ("Opcao: ");
        scanf ("%d", &opcao );
        ler_enter();
        if ( opcao == 1 ) imprimirMemoria();
        else if ( opcao == 2 ) alterarPassageiro();
        else if ( opcao == 3 ) alterarCondutor();
        else if (opcao == 0) exit(0);
        else printf("Opção inválida\n"); 

    } while  ( 1 );
}

void trataAlarme(){
    int n = fork();
    if (n == 0){
        execl("LyftTask",NULL);
        exit(0);
    }
}

 void main(){  
    signal(SIGALRM,trataAlarme);  
    alarm(60);
    criarPassageiros();
    criarCondutores();
    criaPID(); 
    signal(SIGUSR1,updateCondutores);
    signal(SIGTERM, rescreveFicheiros);
    menu();
} 
