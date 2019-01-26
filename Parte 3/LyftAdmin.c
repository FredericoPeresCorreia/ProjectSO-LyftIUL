#include "funcgerais.h"
int idCondutores;
int idPassageiros;
int msg_id;
Tcondutor  * c;
Tpassageiro * p; 
MsgViagem m_rcvd;
int condutorAtribuido;
int status;

void criarCondutores(){
    FILE *f;
    char linha [200];
     if ( access(fnameCondutores, R_OK) == 0){
        f = fopen(fnameCondutores, "r");
        int i = 0;
            while(fgets(linha,sizeof(linha)-1,f)){    
                c[i] = criaCondutor(linha);
                printf("%d:%s:%s:%s:%s:%s:%s:%s:%d:%d:%.02f\n",
                c[i].numero,c[i].nome,c[i].turma,
                c[i].telemovel,c[i].email,c[i].tipo,
                c[i].marca,c[i].matricula,c[i].viagens,
                c[i].pontos,c[i].saldo);
                i++;
            }
        fclose(f);
    }   
        
}

void criarPassageiros(){
    FILE *f;
    char linha [200];
    if (access(fnamePassageiros, R_OK) == 0){
        f = fopen(fnamePassageiros,"r");
        int i = 0;
        while(fgets(linha,sizeof(linha)-1,f)){
            p[i] = criaPassageiro(linha);
            i++;
        }
        fclose(f);
    }
}
void imprimirCondutores(){
    for (int i = 0 ; i < nCondutores; i++){
         printf("%d:%s:%s:%s:%s:%s:%s:%s:%d:%d:%.02f\n",
        c[i].numero,c[i].nome,c[i].turma,
        c[i].telemovel,c[i].email,c[i].tipo,
        c[i].marca,c[i].matricula,c[i].viagens,
        c[i].pontos,c[i].saldo);
    }
}

void imprimirPassageiros(){  
    for (int i = 0 ; i < nPassageiros; i++){
         printf("%d:%s:%s:%s:%s:%s",
        p[i].numero,p[i].nome,
        p[i].turma,p[i].telemovel,
        p[i].email, p[i].c_credito);
    }
}
void setup(){
    int condutoresExistia = 0;
    int passageirosExistia = 0;
    msg_id = msgget(msgq_key, IPC_CREAT | 0700);
    nCondutores = numeroLinhas(fnameCondutores);
    printf("Existem %d condutores\n", nCondutores);
    idCondutores = shmget(condutores_shm_key, nCondutores* sizeof(Tcondutor), 0700);
    if(idCondutores == -1){
        idCondutores = shmget(condutores_shm_key, nCondutores* sizeof(Tcondutor), IPC_CREAT| 0700);
        condutoresExistia = -1;
    }
    c = (Tcondutor *) shmat(idCondutores, 0,0);
    exit_on_null(c,"Nullo");
    if(condutoresExistia == -1){
        criarCondutores();
    }else{
        imprimirCondutores();
    }    

    nPassageiros = numeroLinhas(fnamePassageiros);
    printf("Existem %d passageiros\n",nPassageiros);
    idPassageiros = shmget(passageiros_shm_key,nPassageiros* sizeof(Tpassageiro), 0700);
    if(idPassageiros == -1){
        idPassageiros = shmget(passageiros_shm_key,nPassageiros* sizeof(Tpassageiro), 0700);
        passageirosExistia = -1;
    }
    p = (Tpassageiro *) shmat(idPassageiros,0,0);
    exit_on_null(p, "Nulo pass");
    if(passageirosExistia == -1){
        criarPassageiros();
    }    
}



void imprimirMemoria(){
    imprimirCondutores();
    imprimirPassageiros();  
}

void alterarPassageiro(){
    int i;
    int existe;
    printf("Indique o seu número: \n");
    scanf ("%d", &i);
    existe = confirmar_passageiro(i);
    if(existe == 1){
        for(int j = 0; j < nPassageiros; j++){
            if(p[j].numero == i){
                printf("Insira a turma nova: (atual = %s)\n",p[j].turma);
                scanf("%s",&p[j].turma);
                ler_enter();
                printf("Insira o telemóvel novo: (atual = %s)\n",p[j].telemovel);
                scanf("%s",&p[j].telemovel);
                ler_enter();
                printf("Insira o mail novo: (atual = %s)\n",p[j].email);
                scanf("%s",&p[j].email);
                ler_enter();
                printf("Insira o cartão de crédito novo: (atual = %s)\n",p[j].c_credito);
                scanf("%s",&p[j].c_credito);
                strcat(p[j].c_credito,"\n");
                ler_enter();
                break;  
            }
        }
    }
}

void alterarCondutor(){
    int i;
    int existe;
    printf("Indique o seu número: \n");
    scanf ("%d", &i);
    existe =confirmar_condutor(i);   
    if(existe == 1){
        for(int j = 0; j < nCondutores; j++){
            if(c[j].numero == i){
                printf("Qual o número novo?\n");
                scanf("%d", &c[j].numero);
                ler_enter();
                printf("Qual o nome novo?\n");
                scanf("%s", &c[j].nome);
                ler_enter();
                printf("Qual a turma nova?\n");
                scanf("%s", &c[j].turma);
                ler_enter();
                printf("Qual o número de telemóvel novo?\n");
                scanf("%s", &c[j].telemovel);
                ler_enter();
                printf("Qual o email novo?\n");
                scanf("%s", &c[j].email);
                ler_enter();
                printf("Qual o tipo do carro novo?\n");
                scanf("%s", &c[j].tipo);
                ler_enter();
                printf("Qual a marca do carro novo?\n");
                scanf("%s", &c[j].marca);
                ler_enter();
                printf("Qual a matrícula  do carro novo?\n");
                scanf("%s", &c[j].matricula); 
                break;  
            }
        }
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

void obtemCondutor(){
    if(c[0].activo == 1){
        condutorAtribuido = 0;
    } else{
        int i = 0;
        while(c[i].activo != 1){
            i++;
        }
        condutorAtribuido = i;
    } 

    for(int i = condutorAtribuido; i < nCondutores; i++){
        if((c[condutorAtribuido].disponivel_desde < c[i].disponivel_desde )&& c[i].activo == 1){
            condutorAtribuido = i;
        }
    }

    c[condutorAtribuido].activo = 0;
    MsgViagem serverCondutor;
    serverCondutor.tipo = c[condutorAtribuido].PID;
    serverCondutor.dados.pid_passageiro = m_rcvd.dados.pid_passageiro;
    strcpy(serverCondutor.dados.local_encontro, m_rcvd.dados.local_encontro);
    status = msgsnd(msg_id, &serverCondutor, sizeof(MsgViagem),0);
}

void atualizarDados(){
    for(int i = 0; i < nCondutores; i++){
        if(m_rcvd.dados.pid_condutor == c[i].PID){
            c[i].saldo += m_rcvd.dados.valor;
            c[i].pontos += m_rcvd.dados.pontos; 
            c[i].activo = 1;
            c[i].disponivel_desde = (int)time(NULL);
        }
    }
}

void esperaMensagens(){
    while (msg_id > 0){
        status = msgrcv(msg_id, &m_rcvd, sizeof(MsgViagem), 1, 0);
        if(m_rcvd.dados.pid_condutor == 0){
            obtemCondutor();
        } else if(m_rcvd.dados.valor != 0){
            atualizarDados();
        }else{
            exit(1);
        }   
    }
}

void main(){
    setup();
    int n = fork();
    if (n == 0){ 
        esperaMensagens();
    }   
    menu();
}