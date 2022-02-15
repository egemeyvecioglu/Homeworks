#include <stdio.h>
#include "the2.h"

int main(){
    char names[][20] = {"John", "Patrick", "Evelyn", "Aaron", "Emily"};  /* names to be added into storage */
    int i;              /* iterator */
    int IA_size = 3;    /* initial IndexArray size */
    int DA_size = 3;    /* default data array size */
    int** storage;      /* storage variable */
    int* DA_sizes;      /* data array sizes */

    storage = initialize_storage(IA_size, DA_size, &DA_sizes);  /* initialize the storage */
    
    for (i = 0; i < 5; i++)  /* for each person name in the list */
    {
        insert(storage, IA_size, names[i], DA_sizes);       /* insert a person name into storage */
        print_storage(storage, IA_size, DA_sizes);          /* print storage */
        printf("-----------------------------------------\n");
    }

	return 0;
}
