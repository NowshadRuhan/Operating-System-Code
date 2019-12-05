#include<stdio.h>
#include<stdlib.h>


#define AT_BEG 10
#define AT_END 40
#define AFTER  30
#define BEFORE 20

#define P_NORMAL 5
#define P_HIGH 1
#define P_LOW 10

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

PCB* insertProcess(Queue *q , int POS ,int pid, int arrival, int burst,  int priority )
{

    PCB *loc = q->head;
    PCB *newProcess = (PCB *) malloc( sizeof(PCB));

    newProcess->pid = pid;
    newProcess->aTime = arrival;
    newProcess->bTime = burst;
     //init
     newProcess->wTime=-1;
     newProcess->tTime=-1;
     newProcess->eTime=-1;
     newProcess->priority=5;


    switch(POS)
    {
    case AT_BEG:

        if(loc==0)
        {
            loc= q->head = newProcess;
            loc->next=loc->prev=0;

            q->tail=newProcess;
        }
        else
        {
            loc->prev= newProcess;
            newProcess->prev=0;
            newProcess->next=loc;

        }

        break;


    case AT_END:
        //while(loc->next!=0)loc=loc->next;
        loc = q->tail;
        newProcess->prev= loc;
        newProcess->next =0;
        loc->next = newProcess;
        q->tail = newProcess;


        break;
    case AFTER:


        newProcess->prev= loc;
        newProcess->next =loc->next;
        loc->next = newProcess;


        break;

    default: // case BEFORE:

        newProcess->prev= loc->prev;
        newProcess->next =loc;
        loc->prev = newProcess;


        break;

    }

    return newProcess;
}
main()
{
    Queue *readyQ = (Queue *) malloc( sizeof(Queue));;

    readyQ->head=0;

//insertProcess(Queue *q , int POS ,int pid, int arrival, int burst )
    insertProcess(readyQ, AT_BEG, 1, 0, 10, P_NORMAL );
    insertProcess(readyQ, AT_END, 2, 0, 20, P_NORMAL);


   printQueue(readyQ);


    printf("\n\n");
}


