#include<stdio.h>
#include<stdlib.h>


#define P_NORMAL 5
#define P_HIGH 1
#define P_LOW 10


int CLOCK = 0;
int PID = 1, TotalWaitingTime = 0;
int waitingTime = 0;
typedef struct a
{
    int pid, priority;
    int bTime, aTime, wTime, tTime, eTime;
    // registers, PC etc...

    struct a *next, *prev;
} PCB ;

typedef struct
{
     PCB *head, *tail;
} Queue ;

PCB* searchLocById(PCB* loc, int id ){

      while(loc->pid!=id){loc=loc->next; if (loc->next == 0) return loc;}
      return loc;

}
void  printQueue(Queue *q )
{
     PCB *pn = q->head;

     printf("PID\t CPUBurst\t Arrival\t Waiting\t Ends\t @Address\n");
        while(pn!=0)
        {
            printf("%3d %8d %15d %15d %15d @%10d >\n",pn->pid, pn->bTime, pn->aTime, pn->wTime, pn->eTime,pn  );
            pn= pn->next;
        }

}

void insertProcess(Queue *q ,  int burst,  int priority )
{

    PCB *loc = q->head;
    PCB *newProcess = (PCB *) malloc( sizeof(PCB));

    newProcess->next = newProcess->prev = 0;

    newProcess->pid = PID++;
    newProcess->aTime = CLOCK;
    newProcess->bTime = burst;
    newProcess->priority=priority;
     //init
     newProcess->wTime=-1;
     newProcess->tTime=-1;
     newProcess->eTime=-1;


     // setup links
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


     //eof setups


    if(0){
        printf("%d %d %d %d %d @ %d>\n",
            newProcess->pid,
            newProcess->bTime,
            newProcess->aTime,
            newProcess->wTime,
            newProcess->eTime,
            newProcess  );

       printf("After Insertion  RQ:: head =%d & tail=%d \n", q->head, q->tail);

    }

    //return newProcess;
}
PCB deQueue(Queue *list){

    PCB t;
    t.pid=0;
    if(list->head==0){
        printf("Queue Empty!");

    }
    t = *list->head;
    list->head = list->head->next;
    return t;
}


void executeProcess(Queue *rq){

    int cp = 0;
    while(1){
        PCB r = deQueue(rq);
        printf("\n\n Process %d is being executed.... \n", r.pid);
        TotalWaitingTime += CLOCK - r.aTime;
        CLOCK += r.bTime;
        printf("\n\nAfter completion , CLOCK =%d, TWT =%d....\n",CLOCK, TotalWaitingTime);
        cp++;
        if(rq->head==0){
            printf("Nothing to be executed ! \n");
            break;

        }
    }
    printf("\n Average Waiting = %f", (float) TotalWaitingTime/cp);

}




int main()
{
    Queue *readyQ = (Queue *) malloc (sizeof(Queue));
    readyQ->head=readyQ->tail=0;

//insertProcess(Queue *q , int burst )
    insertProcess(readyQ, 10, P_NORMAL );
    insertProcess(readyQ, 20, P_NORMAL);
    insertProcess(readyQ, 2, P_NORMAL);


    printQueue(readyQ);
    printf("\n\n");

    executeProcess(readyQ);


    printf("\n\n");

    return 0;
}

