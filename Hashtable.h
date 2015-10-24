#ifndef Hashtable_h
#define Hashtable_h
#include "SLList.h"
typedef struct Hashtable{
    int tableSize,a,b,prime,count;
    SLList **table;
} Hashtable;
Hashtable *Hashtable_create();
void Hashtable_destroy(Hashtable* table);
void Hashtable_copy(Hashtable* LHS, Hashtable* RHS);
int Hashtable_hash(Hashtable* table,int key);
void Hashtable_insert(Hashtable* table, int keyValue,int key);
void Hashtable_remove(Hashtable* table, int key);
node *Hashtable_search(Hashtable* table, int key);
Hashtable* Hashtable_resize(Hashtable* table, double factor);
void Hashtable_print_int(Hashtable* ht);
Hashtable *Hashtable_create(const int default_table_size){
    srand((unsigned)time(NULL));
    Hashtable *newHashtable = calloc(1,sizeof(Hashtable));
    newHashtable->tableSize=default_table_size;
    newHashtable->a=rand()%10000;
    newHashtable->b=rand()%10000;
    newHashtable->prime=19;
    newHashtable->count=0;
    int i=0;
    newHashtable->table = calloc(newHashtable->tableSize,sizeof(SLList*));
    for (i = 0; i < newHashtable->tableSize;i++){
        newHashtable->table[i]=SLList_create();
    }
    return newHashtable;
}
void Hashtable_destroy(Hashtable* htable){
   int i = 0;
    Hashtable* temp = htable;
    for( i = 0; i < htable->tableSize ; i++){
        SLList_destroy(temp->table[i]);
    }
   
    free(temp->table);
    free(temp);
}

void Hashtable_copy(Hashtable* LHS, Hashtable* RHS){
    LHS->tableSize = RHS->tableSize;
    LHS->a = RHS->a;
    LHS->b = RHS->b;
    LHS->count = RHS->count;
    LHS->prime = RHS->prime;
    LHS->table = calloc(LHS->tableSize,sizeof(SLList*));
    int i = 0;
    for (i=0; i<LHS->tableSize; i++) {
        LHS->table[i]=SLList_create();
    }
    for (i = 0; i<LHS->tableSize; i++) {
        node* walker = RHS->table[i]->head;
        SLList* temp=SLList_create();
        while(walker!=NULL) {
            SLList_insert(temp,walker->item, walker->key);
            walker=walker->next;
        }
        walker=temp->head;
        while (walker!=NULL) {
            SLList_insert(LHS->table[i], walker->item, walker->key);
            walker=walker->next;
        }
        SLList_destroy(temp);
    }
}

Hashtable* Hashtable_resize(Hashtable* htable, double factor){
    SLList *temp=SLList_create();
    int newSize = (int)(htable->tableSize*factor);
    Hashtable *newTable = Hashtable_create(newSize);
    int i = 0;
    for(i=0;i<htable->tableSize;i++){
        node *walker = htable->table[i]->head;
        while(walker!=NULL){
            SLList_insert(temp, walker->item, walker->key);
            walker=walker->next;
        }
    }
    newTable->count = htable->count;
    newTable->tableSize = newSize;
    newTable->a = rand()%10000;
    newTable->b = rand()%10000;
    node* walker = temp->head;
    for (i = 0; i < temp->count; i++) {
        int slot = Hashtable_hash(newTable, walker->key);
        SLList_insert(newTable->table[slot],walker->item,walker->key);
        walker=walker->next;
    }
    
    for (i = 0; i < newTable->tableSize; i++) {
        if(newTable->table[i]->count > newTable->tableSize/2){
            Hashtable* RHS = Hashtable_resize(newTable,1.0);
            Hashtable_copy(newTable,RHS);
            Hashtable_destroy(RHS);
        }
    }
    SLList_destroy(temp);
    return newTable;
}
int Hashtable_hash(Hashtable* htable,int key){
    return (((htable->a*key)+htable->b)%htable->prime)%htable->tableSize;
}
void Hashtable_insert(Hashtable *htable,int keyValue,int key){
    int slot = Hashtable_hash(htable, key);
    SLList_insert(htable->table[slot],keyValue,key);
    htable->count++;
    if(htable->table[slot]->count>(htable->tableSize/2)){
        Hashtable* RHS = Hashtable_resize(htable,2.0);
        Hashtable_copy(htable,RHS);
        Hashtable_destroy(RHS);
    }
}
void Hashtable_remove(Hashtable *htable,int key){
    int slot = Hashtable_hash(htable, key);
    node *node_to_remove = Hashtable_search(htable, key);
    SLList_remove(htable->table[slot],node_to_remove);
    htable->count--;
    if(htable->count<htable->tableSize/4){
        Hashtable* RHS = Hashtable_resize(htable,.50);
        Hashtable_copy(htable,RHS);
        Hashtable_destroy(RHS);
    }
}
node *Hashtable_search(Hashtable *htable,int key){
    int slot = Hashtable_hash(htable, key);
    return SLList_search_key(htable->table[slot], key);
}
void Hashtable_print_int(Hashtable* ht){
    int i =0;
    for (i = 0;i<ht->tableSize; i++) {
        printf("[");
        SLList_print_int(ht->table[i]);
        printf("]\n");
    }
    printf("\n");
}

#endif /* Hashtable_h */
