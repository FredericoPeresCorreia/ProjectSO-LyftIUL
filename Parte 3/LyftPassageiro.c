#include "funcgerais.h"

void main(){
    nPassageiros = numeroLinhas(fnamePassageiros);
    int i;
    int existe;
    printf("Indique o seu numero: \n");
    scanf ("%d", &i);
    existe = confirmar_passageiro(i);
    
    if(existe==0){
        printf("passageiro nao existe\n");
        exit(0);
    }
    
    else{
        char mens[250];
        printf("Indique o local de encontro: \n");
        scanf ("%s", mens);
        int msg_id;
        int status;
        MsgViagem msg;
        msg_id = msgget(msgq_key, 0700);
        exit_on_error (msg_id, "Criacao/Ligacao");
        msg.tipo = 1;
        msg.dados.data = (int)time(NULL);
        msg.dados.pid_passageiro = getpid();
        msg.dados.pid_condutor = 0;
        strcpy( msg.dados.local_encontro, mens);
        status = msgsnd( msg_id, &msg,sizeof(MsgViagem), 0);
        exit_on_error (status, "Envio");
        printf ("Mensagem enviada!\n");
        MsgViagem m_rcvd;
        status = msgrcv(msg_id, &m_rcvd, sizeof(m_rcvd), getpid(), 0);
        exit_on_error(status, "erro ao receber");
        printf("%s\n", m_rcvd.dados.local_encontro);
        exit(0);
    }
}