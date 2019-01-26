#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>  
#include <sys/ipc.h> 
#include <sys/sem.h>
#include <sys/msg.h>
#define exit_on_error(s,m) if (s<0) {perror(m); exit(1);}
#define exit_on_null(s,m) if (s == NULL ) { perror(m); exit(1);}
int nCondutores;
int nPassageiros;



typedef struct{
    int numero;
    char nome[50];
    char turma[10];
    char telemovel[15];
    char email[40];
    char tipo[20];
    char marca[20];
    char matricula[15];
    int viagens;
    int pontos;
    float saldo;
    int activo;
    long disponivel_desde;
    int PID;
} Tcondutor;

typedef struct{
    int numero;
    char nome[50];
    char turma[10];
    char telemovel[15];
    char email[40];
    char c_credito[20];
} Tpassageiro;

typedef struct{
    long tipo;
    struct{
        int pid_passageiro;
        int pid_condutor;
        char local_encontro[100];
        long data;
        float pontos;
        float valor;
    } dados;
} MsgViagem;

const int NUMERO_PARAMETEROS_PASSAGEIROS = 6;
const int NUMERO_PARAMETEROS_CONDUTOR = 11;
const int msgq_key = 822230;
const int passageiros_shm_key = 822231;
const int condutores_shm_key = 822232;
const char fnamePassageiros[] = "passageiros.txt";
const char fnameCondutores[] = "condutores.txt";
const char fnameViagens[] = "viagens.txt";
const char fnamePID[] = "lyftadmin.pid";


void obter_substring(char linha[], char resultado[], char separador, int indice) {
   int i, j=0, meu_indice = 0;
   for (i=0; linha[i] != '\0'; i++) {
     if ( linha[i] == separador ) {
       meu_indice++;
     } else if (meu_indice == indice) {
       resultado[j++]=linha[i];
     }
   }
   resultado[j]='\0';
}
int numeroLinhas(char fname[]){
    FILE *f;
    int count = 0;
    f = fopen(fname, "r");
    if (f == NULL) {
        printf("N�o foi encontrado o ficheiro %s", fname);
    }
    char linha[200];
    while(fgets(linha,sizeof(linha)-1,f)){
        count++;
    }
    fclose(f);
    return count;
}

int confirmar_passageiro(int i){
    printf("Número passageiros = %d\nNúmero de passageiro pedido = %d\n",nPassageiros,i);
    int shmid = shmget(passageiros_shm_key, nPassageiros * sizeof(Tpassageiro), IPC_CREAT | 0700 );
    exit_on_error(shmid, "shmget");
    Tpassageiro* p = (Tpassageiro *)shmat(shmid, 0, 0);
    exit_on_null(p, "shmat");
    for(int j=0;j<nPassageiros;j++){
        if( p[j].numero == i ) {
            printf("Encontrado o passageiro %s\n", p[j].nome);
            return 1;
        }
    }
    return 0;
}

int confirmar_condutor(int i){
    printf("Número condutores = %d\nNúmero de condutor pedido = %d\n",nCondutores,i);
    int shmid = shmget(condutores_shm_key, nCondutores * sizeof(Tcondutor), IPC_CREAT | 0700 );
    exit_on_error(shmid, "shmget");
    Tcondutor* c = (Tcondutor *)shmat(shmid, 0, 0);
    exit_on_null(c, "shmat");
    for(int j=0;j<nCondutores;j++){
        if( c[j].numero == i ) {
            printf("Encontrado o condutor %s\n", c[j].nome);
            return 1;
        }
    }
    return 0;
}

Tpassageiro criaPassageiro(char string[]){
    Tpassageiro passageiro;
    char resultado [100];
    for(int i = 0; i <NUMERO_PARAMETEROS_PASSAGEIROS;i++){
            obter_substring(string, resultado,':',i);
            if(i == 0){
                passageiro.numero=atoi(resultado);
            } else if(i==1){
                strcpy(passageiro.nome,resultado);
            } else if (i==2){
                strcpy(passageiro.turma,resultado);
            }else if(i==3){
                strcpy(passageiro.telemovel,resultado);
            }else if(i==4){
                strcpy(passageiro.email,resultado);
            }else if(i==5){
                strcpy(passageiro.c_credito,resultado);
            }
        }
        return passageiro;
}

Tcondutor criaCondutor(char string[]){
    Tcondutor condutor;
    char resultado [100];
    for(int i = 0; i <NUMERO_PARAMETEROS_CONDUTOR;i++){
            obter_substring(string, resultado,':',i);
            if(i == 0){
                condutor.numero=atoi(resultado);
            } else if(i==1){
                strcpy(condutor.nome,resultado);
            } else if (i==2){
                strcpy(condutor.turma,resultado);
            }else if(i==3){
                strcpy(condutor.telemovel,resultado);
            }else if(i==4){
                strcpy(condutor.email,resultado);
            }else if(i==5){
                strcpy(condutor.tipo,resultado);
            } else if(i==6){
                strcpy(condutor.marca,resultado);
            }else if (i==7){
                 strcpy(condutor.matricula,resultado);
            } else if (i==8){
                condutor.viagens=atoi(resultado);
            } else if (i==9){
                condutor.pontos=atoi(resultado);
            } else if (i==10){
                condutor.saldo=atof(resultado);
            }
        }
        return condutor;
}

/* void criarPassageiros(){
    FILE *f;
    char linha[100];
    if ( access(fnamePassageiros, R_OK) == 0){
        f = fopen(fnamePassageiros, "r");
            while(fgets(linha,sizeof(linha)-1, f)){
                passageiros[nPassageiros] = criaPassageiro(linha);
                nPassageiros++;
            }
        fclose(f);
    }

}  */

/* void criarCondutores(){
FILE *f;
    char linha[200];
    if ( access(fnameCondutores, R_OK) == 0){
        f = fopen(fnameCondutores, "r");
            while(fgets(linha,sizeof(linha)-1, f)){
                condutores[nCondutores] = criaCondutor(linha);
                nCondutores++;
            }
        fclose(f);
    }
}
 */


/* void escreveCondutoresStr(char condutor[],Tcondutor c){
    snprintf(condutor,200,"%d:%s:%s:%s:%s:%s:%s:%s:%d:%d:%.02f\n",
        c.numero,c.nome,c.turma,
        c.telemovel,c.email,c.tipo,
        c.marca,c.matricula,c.viagens,
        c.pontos,c.saldo);
} */

void escrevePassageiroStr(char passageiro[], Tpassageiro p){
    snprintf(passageiro,200 ,"%d:%s:%s:%s:%s:%s",
        p.numero,p.nome,
        p.turma,p.telemovel,
        p.email, p.c_credito);
}

/* void rescreveCondutores(){
    FILE *f;
    f=fopen("condutores.txt","w+");
    for(int i = 0; i < nCondutores;i++){
        char buf[200];
        escreveCondutoresStr(buf,condutores[i]);
        fprintf(f,"%s",buf);
    }
    fclose(f);
} */

/* void rescrevePassageiros(){
    FILE *f;
    f =fopen("passageiros.txt","w+");
    for(int i = 0; i < nPassageiros; i++){
        char buf[200];
        escrevePassageiroStr(buf,passageiros[i]);
        fprintf(f,"%s",buf);
    }
    fclose(f);
} */

void ler_enter() {
   while ( getc(stdin) != '\n' );
}

void criaPID(){
    FILE *f;
    f = fopen(fnamePID, "w+");
    fprintf(f,"%d\n",getpid());
    fclose(f);
}

