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

const int NUMERO_PARAMETEROS_PASSAGEIROS = 6;
const int NUMERO_PARAMETEROS_CONDUTOR = 11;
const char fnamePassageiros[] = "passageiros.txt";
const char fnameCondutores[] = "condutores.txt";
const char fnameViagens[] = "viagens.txt";
const char fnamePID[] = "lyftadmin.pid";
Tpassageiro passageiros[500];
Tcondutor condutores[15];
int nPassageiros=0;
int nCondutores=0;

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
void criarPassageiros(){
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
   
} 

void criarCondutores(){
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



void escreveCondutoresStr(char condutor[],Tcondutor c){
    snprintf(condutor,200,"%d:%s:%s:%s:%s:%s:%s:%s:%d:%d:%.02f\n",
        c.numero,c.nome,c.turma,
        c.telemovel,c.email,c.tipo,
        c.marca,c.matricula,c.viagens,
        c.pontos,c.saldo);
}

void escrevePassageiroStr(char passageiro[], Tpassageiro p){
    snprintf(passageiro,200 ,"%d:%s:%s:%s:%s:%s",
        p.numero,p.nome,
        p.turma,p.telemovel,
        p.email, p.c_credito);
}

void rescreveCondutores(){
    FILE *f;
    f=fopen("condutores.txt","w+");
    for(int i = 0; i < nCondutores;i++){
        char buf[200];
        escreveCondutoresStr(buf,condutores[i]);
        fprintf(f,"%s",buf);
    }
    fclose(f);
}

void rescrevePassageiros(){
    FILE *f;
    f =fopen("passageiros.txt","w+");
    for(int i = 0; i < nPassageiros; i++){
        char buf[200];
        escrevePassageiroStr(buf,passageiros[i]);
        fprintf(f,"%s",buf);
    }
    fclose(f);
}

void ler_enter() {
   while ( getc(stdin) != '\n' );
}

void criaPID(){
    FILE *f;
    f = fopen(fnamePID, "w+");
    fprintf(f,"%d\n",getpid());
    fclose(f);
}