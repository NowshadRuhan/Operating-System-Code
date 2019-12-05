#include<stdio.h>
#include<stdlib.h>


#define P_1 1
#define P_2 2
#define P_3 3


#define QUANTUM 5

int PID = 100, CLOCK = 0, TotalWaitingTime=0;
int cp=0;
typedef struct a
{
    int pid, priority;
    int bTime, aTime, wTime, tTime, eTime, lastSeen;
    // registers, PC etc...

    struct a *next, *prev;
} PCB ;

typedef struct
{
    PCB *head, *tail;
} Queue ;

//Queue *plog;
PCB* searchLocById(PCB* loc, int id )
{

    while(loc->pid!=id)
    {
        loc=loc->next;
        if (loc->next == 0) return loc;
    }
    return loc;

}
void printPCB(PCB *x){
    printf("\n\n");
      printf("PID\t CPUBurst\t Arrival\t Waiting\t Ends\t priority\n");
     printf("%3d %8d %15d %15d %15d %10d >\n",
               x->pid,
               x->bTime,
               x->aTime,
               x->wTime,
               x->eTime,
               x->priority  );
               printf("\n\n");
}
void  printQueue(Queue *q )
{
    PCB *pn = q->head;
    printf("PID\t CPUBurst\t Arrival\t Waiting\t Ends\t priority\n");
    while(pn!=0)
    {
        printf("%3d %8d %15d %15d %15d @%10d >\n",pn->pid, pn->bTime, pn->aTime, pn->wTime, pn->eTime,pn->priority  );
        pn= pn->next;
    }

}

void insertProcess(Queue *q , int burst,  int priority )
{


    PCB *newProcess = (PCB *) malloc( sizeof(PCB));
    newProcess->next = newProcess->prev = 0;// Link Reset

    newProcess->pid = ++PID;
    newProcess->aTime = CLOCK;
//    newProcess->lastSeen= newProcess->aTime;
    newProcess->bTime = burst;
    newProcess->priority=priority;
    //init
    newProcess->wTime=-1;
    newProcess->tTime=-1;
    newProcess->eTime=-1;
    newProcess->lastSeen=-1;



    switch(priority){

        case P_1:

            if(q->head==0)
            {
                q->head = q->tail = newProcess;
            }
            else{

                q->head->prev = newProcess;
                newProcess->next = q->head;
                q->head = newProcess;
            }

            break;

        case P_2 :

            if(q->head==0)
            {
                q->head = q->tail = newProcess;
            }
            else
            {
                q->tail->next =newProcess;
                newProcess->prev = q->tail;
                q->tail =newProcess;
            }
            break;

        case P_3 :

            if(q->head==0)
            {
                q->head = q->tail = newProcess;
            }
            else
            {
                q->tail->next =newProcess;
                newProcess->prev = q->tail;
                q->tail =newProcess;
            }
            break;

    }



}

PCB deQueue(Queue *list)
{
    PCB t;
    t.pid=0;
    if(list->head==0)
    {
        printf(" Queue is empty !");
        return t;
    }
     t = *list->head;
    list->head = list->head->next;

    return t;
}
void executeProcess(Queue *rq){


     while(!rq->head==0){
         PCB r = deQueue(rq);
         printf("\n\n\nProcess %d is being executed ... \n",r.pid);//         printPCB(&r);
         r.wTime = CLOCK- r.aTime;
         TotalWaitingTime += r.wTime;
         CLOCK+= r.bTime;
         printf("\nWaitingTime for Process%d =%d ...priority = %d \n",r.pid, r.wTime, r.priority);
         printf("\nAfter completion, CLOCK =%d, TWT=%d....\n",CLOCK,TotalWaitingTime);
         cp++;
     }
     printf(" \nAverage Wating = %f", (float) TotalWaitingTime/cp) ;
}

void re_addPCB( Queue *q,  PCB r){
   /// printPCB(&r);
    PCB *p = (PCB *) malloc(sizeof(PCB));

    // copy values of r int p
    p->next = 0;// Link Reset
    p->pid = r.pid;
    p->aTime = r.lastSeen;
    p->bTime = r.bTime;
    p->priority=r.priority;
    p->wTime=r.wTime;
    p->tTime=r.tTime;
    p->eTime=r.eTime;
    p->lastSeen=r.lastSeen;

    q->tail->next = p;
    p->prev = q->tail;
    q->tail =p;


    if(q->head == 0) q->head=q->tail;

}
void executeProcessRR(Queue *rq){

     while(!rq->head==0){
         PCB r = deQueue(rq);
         printf("\n\n\nProcess %d [%d]is being executed ...\n",r.pid,&r);//         printPCB(&r);

         // update waiting time
             if(r.lastSeen==-1){
                 r.wTime = CLOCK- r.aTime;
                 TotalWaitingTime +=CLOCK- r.aTime;
             }else{
                 r.wTime += CLOCK- r.lastSeen;
                 TotalWaitingTime +=  CLOCK- r.lastSeen;
             }

         if(r.bTime<= QUANTUM) { //process & release PCB
             // update CLOCK , incr CP (finished Process) & Say Bye
             CLOCK+= r.bTime;
             cp++;

         }else{ // process & add to the rear of RQ again
             CLOCK+= QUANTUM;
             r.bTime-=QUANTUM;
             r.lastSeen=CLOCK;

             re_addPCB(rq, r);
             //printQueue(rq);


         }
         printf("\nWaitingTime for Process%d =%d ... \n",r.pid, r.wTime);
         printf("\nAfter completion, CLOCK =%d, TWT=%d....\n",CLOCK,TotalWaitingTime);
     }
     printf(" \nAverage Wating = %f", (float) TotalWaitingTime/cp) ;
}

main()
{
//    plog = (Queue *) malloc (sizeof(Queue));
//    plog->head=plog->tail=0;

    Queue *readyQ = (Queue *) malloc (sizeof(Queue));
    readyQ->head=readyQ->tail=0;

//insertProcess(Queue *q , ,int pid, int arrival, int burst.....

    insertProcess(readyQ, 4,  P_3 );

    insertProcess(readyQ, 8,  P_2 );
//    printQueue(readyQ);
    insertProcess(readyQ, 7,  P_1);
//    printQueue(readyQ);
    insertProcess(readyQ, 5,  P_2 );
    insertProcess(readyQ, 3,  P_3);
        printQueue(readyQ);
    executeProcessRR(readyQ);
//    printQueue(readyQ);
//    executeProcess(readyQ);



    printf("\n\n");

}




