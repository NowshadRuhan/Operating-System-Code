#define At_beg 10
#define At_after 20
#define At_end 30
#define At_befor 40

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct a{

    int id;
    char *name;

    struct a *next, *prev;
}node;

node *serchItem(node* location, int Id){

    while(location->id!=Id)location = location->next;

    return location;
}

void printLink_list(node *print_first_to_Last, node *print_Last_to_Start){

    if(print_first_to_Last != 0){

        while(print_first_to_Last != 0){
            printf("ID:%d Name:%s  %d>\n",print_first_to_Last->id, print_first_to_Last->name, print_first_to_Last);
            print_first_to_Last = print_first_to_Last->next;
        }
    }
    else{
        while(print_Last_to_Start != 0){
            printf(" %d < ID:%d Name:%s\n",print_Last_to_Start ,print_Last_to_Start->id, print_Last_to_Start->name);
            print_Last_to_Start = print_Last_to_Start->prev;
        }
    }

}
node* insertValue(node* location , int Position)
{
    node *item = (node *) malloc(sizeof(node));
    int Id;
    char *Name;
    scanf("%s %d", Name, &Id);
    item->name = strdup(Name);
    item->id = Id;


    switch(Position){

    case At_beg:
                if(location==0){
                    location = item;
                    location->next = location->prev = 0;
                }
                else{
                    location->prev = item;
                    item->prev =0;
                    item->next = location;
                }
                break;

    case At_end:
        while(location->next!=0)location = location->next;

        item->prev= location;
        item->next =0;
        location->next = item;

        break;

    case At_after:
                item->next = location->next;
                location->next = item;
                item->prev = location;
                break;

    default:
                item->prev = location->prev;
                location->prev->next = item;
                item->next = location;
                location->prev = item;

                break;
    }
    return item;
}
int ID(){
    int Idt;
    scanf("%d", &Idt);
    return Idt;
}
void deleteItem(node* location){

    if(location->prev ==0){
        location->id = location->next->id;
        location->name = location->next->name;
        location->next = location->next->next;
        location->next->next->prev = location;
    }
    else if(location->next !=0 && location->prev!=0){
        location->prev->next = location->next;
        location->next->prev = location->prev;
    }
    else{
        location->prev->next = 0;
    }
}
void updateItem(node* location){

    printf("What you want to update? \n Name or ID? \n Name and ID both? \n");
    printf("If want to update Name? \nInput Name \n\nOr if you want to update Id?\nInput Id \n\nIf you want to update both?\nInput Both\n");
    char *n;
    scanf("%s", n);
    //char *c =  strdup(n);
    if(strcmp(n,'Name') == 0){
        char *nm;
        printf("Input your updated Name you want: \n");
        scanf("%s", nm);
        location->name = strdup(nm);
    }
    else if(strcmp(n,'Id') == 0){
        int i;
        printf("Input your updated Id you want: \n");
        scanf("%d", &i);
        location->id = i;
    }
    else if(strcmp(n,'Both') == 0){
        char *nm;
        int i;
        printf("Input your updated Name and Id you want: \n");
        scanf("%s %d", nm, &i);
        location->id = i;
        location->name = strdup(nm);
    }

}
main(){

    node *start=0, *thenNext;
    printf("How many item you want in your Link list: \n");
    int n ;
    int i=1;
    scanf("%d", &n);
    printf("Enter Your Name & ID : \n");

    start = insertValue(start, At_beg);
    thenNext = start;

    while(i<=n-1){
        thenNext = insertValue(thenNext, At_end);
        i++;
    }
    printLink_list(start, 0);

    printf("\n\n");

   // printf("Which one you want to update?? \n Input its Id :\n");
   // updateItem(serchItem(start , ID()));

    printf("How many Item you want to delete?? : \n");
    int k, j=1;
    scanf("%d", &k);
    while(j<=k){
        printf("Which item you want to delete, input this ID : \n");
        deleteItem(serchItem(start , ID()));
        j++;
    }

    printf("\n\n");
    printLink_list(start, 0);




}





