#include <stdio.h>
#include "the2.h"

int main(){
    int IA_size = 3;    /* initial IndexArray size */
    int DA_size = 3;    /* default data array size */
    int** storage;      /* storage variable */
    int* DA_sizes;      /* data array sizes */

    storage = initialize_storage(IA_size, DA_size, &DA_sizes);  /* initialize the storage */
    storage[0][0] = 9;
    storage[0][1] = 12;
    storage[1][0] = 4;

    print_storage(storage, IA_size, DA_sizes);          /* print storage */

	return 0;
}