#include<stdio.h>
#include<stdlib.h>


#define P_NORMAL 5
#define P_HIGH 1
#define P_LOW 10


int CLOCK = 0;
int PID = 1;
double TotalWaitingTime = 0;
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

    newProcess->wTime=-1;
    newProcess->tTime=-1;
    newProcess->eTime=-1;

    int i =0;
    while(loc!=0){
        if(burst < loc->bTime){
            i=1;
            break;
        }
        else{
            loc=loc->next;
        }
    }
    if(q->head==0){
        q->head=q->tail=newProcess;
    }
    else if(loc==q->head){
        newProcess->next = q->head;
        q->head->prev = newProcess;
        q->head = newProcess;
    }
    else if(i ==0 ){
        q->tail->next=newProcess;
        newProcess->prev= q->tail;
        q->tail = newProcess;
    }
    else{
        newProcess->next = loc;
        newProcess->prev=loc->prev;
        loc->prev->next=newProcess;
        loc->prev= newProcess;
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

process(Queue *Q){
    PCB *Ps = Q->head;



    printf("PID\t CPUBurst\t Arrival\t Waiting\t Ends\t @Address\n");
    while(Ps!=0)
        {
            waitingTime = (CLOCK - Ps->aTime);
            CLOCK = (CLOCK + Ps->bTime);
            TotalWaitingTime = (TotalWaitingTime + waitingTime);
            printf("%3d %8d %15d %15d %15d @%10d >\n",Ps->pid, Ps->bTime, Ps->aTime, waitingTime,CLOCK,Ps  );
            Ps= Ps->next;
        }
        printf("All process Ends Time = %d\n", CLOCK);

        printf("Total Process = %d\n", PID-1);

        printf("Avarage Waiting Time = %lf\n" , TotalWaitingTime/(PID-1));

}



int main()
{
    Queue *readyQ = (Queue *) malloc (sizeof(Queue));
    readyQ->head=readyQ->tail=0;

//insertProcess(Queue *q , int burst )
    int i=1;
    insertProcess(readyQ, 10, P_NORMAL );
    insertProcess(readyQ, 20, P_NORMAL );
    insertProcess(readyQ, 2, P_NORMAL);
    process(readyQ);


    printf("\n\n");

    return 0;
}


