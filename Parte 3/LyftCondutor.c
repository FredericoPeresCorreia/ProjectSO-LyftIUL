#include "funcgerais.h"

int msg_length = 250;
int msg_id;
int status;
int nmr;

int alterar_valores(int i) {
   int id = shmget(condutores_shm_key, numeroLinhas(fnameCondutores) * sizeof(Tcondutor), IPC_CREAT | 0700);
   exit_on_error(id, "Erro ao aceder a memoria partilhada");

   Tcondutor* c = (Tcondutor *)shmat(id, 0, 0);
   exit_on_null(c, "Tcondutor nulo");

   for(int j = 0; j < nCondutores; j++){
      if(c[j].numero == i){
         c[j].activo = 1;
         c[j].disponivel_desde = (int)time(NULL);
         c[j].PID = getpid();
      }
   }
  
}

void processo_condutor() {
   
   //Condutor <- Servidor
   MsgViagem msg;

   msg_id = msgget(msgq_key, 0700);
   exit_on_error(msg_id, "Erro da fila de mensagens");

   status = msgrcv(msg_id, &msg, sizeof(MsgViagem), getpid(), 0);
   exit_on_error(status, "Erro na receção");

   printf("PID do passageiro: %d\n", msg.dados.pid_passageiro);
   
   //Condutor -> Passageiro
   MsgViagem newMsg;
   newMsg.tipo = msg.dados.pid_passageiro;
   newMsg.dados.pid_condutor = getpid();

   printf("Onde está?\n");
   scanf("%s", &newMsg.dados.local_encontro);

   status = msgsnd(msg_id, &newMsg, sizeof(newMsg), 0);

   //Simulacao da viagem
   srand(time(NULL));
   int r = (1 + (rand() % 19));
   sleep(r);
   
   //Condutor -> Servidor
   MsgViagem new_message; 

   printf("Introduza o valor: ");
   scanf("%f", &new_message.dados.valor);

   printf("Introduza a pontuação: ");
   scanf("%d", &new_message.dados.pontos);

   new_message.tipo = 1;
   new_message.dados.pid_condutor = getpid();
   new_message.dados.pid_passageiro = msg.dados.pid_passageiro;

   status = msgsnd(msg_id, &new_message, sizeof(MsgViagem),0);

   
}




void trata_sinal() {
   int id = shmget(condutores_shm_key, numeroLinhas(fnameCondutores) * sizeof(Tcondutor), IPC_CREAT | 0700);
   exit_on_error(id, "Erro ao aceder a memoria partilhada");

   Tcondutor* c = (Tcondutor *)shmat(id, 0, 0);
   exit_on_null(c, "Tcondutor nulo");

   for(int i = 0; i < nCondutores; i++) {
      if(c[i].numero = nmr) {
         c[i].activo = 0;
         exit(0);
      }
   }
}

int main() {
   signal(SIGINT, trata_sinal);
   nCondutores = numeroLinhas(fnameCondutores);

   printf("Insira o número do Condutor: ");
   scanf("%d", &nmr);

   int existe = confirmar_condutor(nmr);

   if(existe == 1){
      alterar_valores(nmr);
      processo_condutor();   
   }
}