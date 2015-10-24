#ifndef SLList_h
#define SLList_h
#include <stdlib.h>
struct node;
typedef struct node{
    struct node* next;
    int key;
    int item;
}node;
typedef struct SLList{
    int count;
    node* head;
}SLList;
SLList *SLList_create();
void SLList_destroy(SLList *list);
void SLList_clear(SLList *list);
void SLList_clear_destroy(SLList *list);
void SLList_insert(SLList *list,int item,int key);
void SLList_remove(SLList *list,node *node_to_remove);
node* SLList_search(SLList *list,int item);
node* SLList_search_key(SLList *list, int key);
void SLList_print_int(SLList *list);
SLList *SLList_create(){
    SLList* newList = calloc(1,sizeof(SLList));
    newList->head=NULL;
    newList->count=0;
    return newList;
}
void SLList_destroy(SLList *list){
    if(list->head!=NULL){
        node *walker=NULL, *temp=NULL;
        walker = list->head;
        while(walker!=NULL){
            temp=walker->next;
            free(walker);
            walker=temp;
        }
    }
    free(list);
}
void SLList_insert(SLList *list,int item,int key){
    node *newNode = calloc(1,sizeof(node));
    if (list->head==NULL) {
        newNode->item=item;
        newNode->key=key;
        list->head=newNode;
    }else{
        newNode->item=item;
        newNode->key=key;
        newNode->next=list->head;
        list->head=newNode;
    }
    list->count++;
}
void SLList_remove(SLList *list, node *node_to_remove){
    node *walker = list->head;
    if(node_to_remove==list->head){
        list->head = list->head->next;
    }else{
        while (walker->next!=node_to_remove){
            walker=walker->next;
        }
        walker->next=node_to_remove->next;
    }
    list->count--;
    free(node_to_remove);
}
node* SLList_search(SLList *list,int item){
    node *walker = list->head;
    while (walker!=NULL) {
        if(walker->item==item){
            return walker;
        }
        walker=walker->next;
    }
    return NULL;
}
node* SLList_search_key(SLList *list, int key){
    node *walker = list->head;
    while (walker!=NULL) {
        if(walker->key==key){
            return walker;
        }
        walker=walker->next;
    }
    return NULL;
}
void SLList_print_int(SLList *list){
    node *walker= list->head;
    while (walker!=NULL){
        printf("[%d]->",walker->item);
        walker=walker->next;
    }
    printf("///");
}
#endif /* SLList_h */
