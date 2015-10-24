#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Hashtable.h"
int main(){
    Hashtable* t = Hashtable_create(8);
    int i = 0;
    for(i = 0; i < 10; i++){
        Hashtable_insert(t, i*100, i);
    }
    
    Hashtable_print_int(t);
    for(i = 0; i< 10; i++){
        Hashtable_remove(t, i);
    }
    Hashtable_print_int(t);
    Hashtable_destroy(t);
    return 0;
}
