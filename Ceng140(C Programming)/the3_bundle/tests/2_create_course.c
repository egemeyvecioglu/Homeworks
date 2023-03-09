#include <stdio.h>
#include "the3.h"

int main(int argc, char const *argv[])
{
    int ids[] = {5710140, 5710477, 5710111};
    int capacities[] = {3, 5, 7};
    Course* c = create_courses(ids, capacities, 3);
    
    if ((c[0].id = 5710140) && (c[0].capacity == 3) && (c[0].requests == NULL)){
        printf("Course: %d, Capacity: %d\n", c[0].id, c[0].capacity);
    }

    return 0;
}
