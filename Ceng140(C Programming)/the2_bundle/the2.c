#include <stdio.h>
#include <stdlib.h>
#include "the2.h"

void print_storage(int** storage, int IA_size, int* DA_sizes)
{
    int i,j;
	for(i=0;i<IA_size;i++)
	{
		printf("%d ->",i);
		for(j=0;j < DA_sizes[i];j++) printf(" %d",storage[i][j]);
		printf("\n");
	}
}


int** initialize_storage(int IA_size, int DA_size, int** DA_sizes)
{
	int **storage,i;
	storage = (int**) malloc(IA_size*sizeof(int*));
	for (i=0; i<IA_size; i++)
	{
	    storage[i]=(int *) calloc(DA_size, sizeof(int));
	}
	

	/*if(*/*DA_sizes =(int*) malloc(IA_size*sizeof(int)); /* )== NULL) printf("you didnt get the memory\n");*/
	/*else printf("you get the memory\n");*/

	for(i=0;i<IA_size;i++) *(*DA_sizes+i) = DA_size;

	return storage; 
}

int transform_name(char* name)
{
	int i=0,code=0;
	
	while(*(name+i) != '\0')
	{
		code += (i+1)*(i+1)*(*(name+i));
		i++;
	}
	return code;
}

void insert(int** storage, int IA_size, char* text, int* DA_sizes)
{
	int index,code,i,checker;
	code = transform_name(text);
	index = code % IA_size;
	
	checker=0;
	for(i=0;i<*(DA_sizes+index);i++)
	{
		if(storage[index][i]==0) 
		{
			storage[index][i]=code;
			checker=1;
			break;
		}
	}
	if(checker==0)
	{
		DA_sizes[index] = DA_sizes[index] * 2;
		storage[index] = (int*) realloc(storage[index],sizeof(int)*DA_sizes[index]);
		for(i=0;i<*(DA_sizes+index);i++)
		{
		if(storage[index][i]==0)
		{
			storage[index][i]=code;
			break;
		}

		}
	}

	

	
}

void resize_IA(int*** storage, int* IA_size, int DA_size, int** DA_sizes)
{
	int i,total_size=0;
	
	for(i=0;i<*IA_size;i++) total_size += *((*DA_sizes)+i);
	
	if((*IA_size)*DA_size*1.5 <= total_size)
	{	int j,new_IA=*IA_size*2,**old_storage,*old_da_sizes;
		
		old_storage = (int**) malloc(*IA_size*sizeof(int*));
		for(i=0;i<*IA_size;i++){
			old_storage[i] =(int*) malloc(sizeof(int)*(*((*DA_sizes)+i)));
		}
		
		for(i=0;i<*IA_size;i++)
		{
			for(j=0;j<*((*DA_sizes)+i);j++) old_storage[i][j]=(*storage)[i][j];
		}

		old_da_sizes = (int*) malloc(*IA_size*sizeof(int));

		for(i=0;i<*IA_size;i++) old_da_sizes[i]=*(*DA_sizes+i);
		
		*storage = initialize_storage(new_IA, DA_size, DA_sizes);

		fill_new_storage(old_storage,*IA_size,old_da_sizes,*storage,*DA_sizes);
		
        for(i=0;i<*IA_size;i++) free(old_storage[i]);
		free(old_da_sizes);
		free(old_storage);
		
		*IA_size = new_IA;
		
	}
}

void fill_new_storage(int** old_storage, int old_IA_size, int* old_DA_sizes, int** new_storage, int* new_DA_sizes)
{
	int i,j;
	
	for(i=0;i<old_IA_size;i++)
	{
		for(j=0;j<old_DA_sizes[i];j++)
		{
	        if(old_storage[i][j] != 0) insert2(new_storage,old_IA_size,old_storage[i][j],new_DA_sizes);
	    }
	}	
}

void insert2(int** storage, int IA_size, int name_code, int* DA_sizes)
{
	int index,checker=0,i;
	
	index = name_code % (IA_size*2);
	for(i=0;i<*(DA_sizes+index);i++)
	{
		if(storage[index][i]==0) 
		{	
			storage[index][i]=name_code;
			checker=1;
			break;
		}
	}
	
	if(checker==0)
	{
		DA_sizes[index] = DA_sizes[index] * 2;
		
		storage[index] = (int*) realloc(storage[index],sizeof(int)*DA_sizes[index]*2);
		for(i=DA_sizes[index]/2;i<DA_sizes[index];i++) storage[index][i]=0;
		
		for(i=0;i<*(DA_sizes+index);i++)
		{
		    if(storage[index][i]==0)
		    {
			    storage[index][i]=name_code;
			    break;
		    }
		}
	}

}


int main(){
    char names[][10] = {"John", "Sophia", "Evelyn", "Aaron", "Emily", 
                        "Russell", "April", "Patrick", "Eva", "Jesse"};  /* names to be added into storage */
    int i;              /* iterator */
    int IA_size = 3;    /* initial IndexArray size */
    int DA_size = 3;    /* default data array size */
    int** storage;      /* storage variable */
    int* DA_sizes;      /* data array sizes */
    
    storage = initialize_storage(IA_size, DA_size, &DA_sizes);  /* initialize the storage */
    print_storage(storage, IA_size, DA_sizes); 
    printf("-----------------------------------------\n"); 
    for (i = 0; i < 10; i++)  /* for each person name in the list */
    {
        insert(storage, IA_size, names[i], DA_sizes);       /* insert a person name into storage */
        print_storage(storage, IA_size, DA_sizes);          /* print storage */

        /* Check if need IndexArray extension. */
        /* Sent references of storage, current IndexArray size and data array sizes */
        /* to not lost their references while updating them in the implemented functions */
        resize_IA(&storage, &IA_size, DA_size, &DA_sizes);
        printf("-----------------------------------------\n");
    }
    

	return 0;
}