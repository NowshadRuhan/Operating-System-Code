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
    int id;
    struct a *next, *prev;
} node;
typedef struct
{
    node *head, *tail;
} List;
push(List *list, int id)
{
    node *t = (node *) malloc (sizeof(node));
    t->id = id;
    t->next = t->prev = 0;

    if(list->head==0)
    {
        list->head = list->tail = t;
    }
    else
    {
        list->tail->next =t;
        t->prev = list->tail;
        list->tail =t;
    }
    printf(" %d has been added \n ",t->id);
}
int  pop(List *list)
{
    if(list->tail==0)
    {
        printf(" Stack underflow !");
        return -1;
    }
    node *t = list->tail;
    list->tail = list->tail->prev;
    //t->next = t->prev->next= t->prev =0;
    return  list->tail->id;
}
enQueue(List *list, int id)
{
    push(list, id);
}
int deQueue(List *list)
{
    if(list->head==0)
    {
        printf(" Queue is empty !");
        return -1;
    }
    node *t = list->head;
    list->head = list->head->next;

    return list->head->id;
}
main()
{
//    Stack implemented with linked list
    List  *stack = (node *) malloc (sizeof(node));;
    stack->head =  stack->tail = 0;
    push(stack, 5);
    push(stack, 15);
    push(stack, 25);
    printf("\n\n");
    printf(" %d has been popped\n ",pop(stack));
    printf(" %d has been popped\n ",pop(stack));


//    Queue implemented with linked list

    List  *queue = (node *) malloc (sizeof(node));;
    queue->head =  queue->tail = 0;
    push(queue, 5);
    push(queue, 15);
    push(queue, 25);
    printf("\n\n");

    printf(" %d has been deQueued\n ",deQueue(queue));
    printf(" %d has been deQueued\n ",deQueue(queue));
    printf(" %d has been deQueued\n ",deQueue(queue));
    printf(" %d has been deQueued\n ",deQueue(queue));



}

