#include <stdio.h>
#include "the3.h"

int main(int argc, char const *argv[])
{
    int ids[] = {1234567, 1234568, 1234569, 1234570};
    int remaining_credits[] = {7, 8, 9, 10};
    char* names[] = {"Ahmet", "Mehmet", "Ayse", "Fatma"};
    Student* s = create_students(ids, remaining_credits, names, 4);
    
    if ((s[0].id = 1234567) && (s[0].remaining_credit == 7)){
        printf("Student: %s, Id: %d, Remaining Credit: %d\n", s[0].name, s[0].id, s[0].remaining_credit);
    }

    return 0;
}
