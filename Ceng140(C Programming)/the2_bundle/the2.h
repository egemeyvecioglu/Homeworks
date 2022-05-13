#ifndef THE2_H
#define THE2_H

/* prints content of the storage */
void print_storage(int** storage, int IA_size, int* DA_sizes);

/* initialize a 2D dynamic array with given sizes, allocates an array 
   to keep data array sizes in the main function */
int** initialize_storage(int IA_size, int DA_size, int** DA_sizes);

/* transforms given person name to name code */
int transform_name(char* name);

/* inserts given person name into storage, extends corresponding data array if it is full.
   updates data sizes array in case. */
void insert(int** storage, int IA_size, char* name, int* DA_sizes);

/* chechs if need extending the storage. initialize a new one with doubled size in case.
   allocates a new data array sizes, fills new storage, updates data array sizes and
   frees old storage and data array sizes. */
void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes);

/* transfers all the content in the old storage to the new one using insert2 function. */
void fill_new_storage(int** old_storage, int old_IA_size, int* old_DA_sizes, int** new_storage, int* new_DA_sizes);

/* inserts given code name into storage, extends corresponding data array if it is full.
   updates data sizes array in case. */
void insert2(int** storage, int IA_size, int name_code, int* DA_sizes);

#endif