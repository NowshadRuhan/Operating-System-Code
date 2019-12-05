#include<stdio.h>
#include<stdlib.h>

typedef struct a
{
    int id;
    struct a *next, *prev;
}node;
typedef struct {
    node *head, *tail;
}List;


void push(List *list, int id){
    node *t = (node *) malloc (sizeof(node));
    t->id=id;
    t->next=t->prev=0;
    if(list->head==0){
        list->head = list->tail = t;
    }
    else{
        list->tail->next=t;
        t->prev = list->tail;
        list->tail=t;
    }
    printf("%d has been pushed\n", t->id);
}

int pop(List *list){
    if(list->tail==0)
    {
        printf("Stack Empty !\n");
        return -1;
    }
    int t = list->tail->id;
    list->tail=list->tail->prev;
    return t;
}
int deQueue(List *list){
    if(list->head==0)
    {
        printf("Queue Empty !\n");
        return -1;
    }
    int t = list->head->id;
    list->head=list->head->next;


    return t;

}


int main(){
    List *stack = (List *) malloc (sizeof(List));
    stack->head = stack->tail = 0;
    push(stack, 5);
    push(stack, 15);
    push(stack, 25);

    printf("\n\n");
    printf("%d has been popped\n", pop(stack));
    printf("%d has been popped\n", pop(stack));
    printf("%d has been popped\n", pop(stack));
   // printf("%d has been popped\n", pop(stack));

    printf("\n\n");
    printf("%d has been deQueue\n", deQueue(stack));
    printf("%d has been deQueue\n", deQueue(stack));
    printf("%d has been deQueue\n", deQueue(stack));
  //  printf("%d has been deQueue\n", deQueue(stack));

    return 0;

}
