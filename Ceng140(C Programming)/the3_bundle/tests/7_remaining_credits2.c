#include <stdio.h>
#include "the3.h"

int main()
{
    int i = 0;
    Course* courses;
    Student* students;

    int ids[] = {5710140, 5710477, 5710111};
    int capacities[] = {3, 5, 7};
    int s_ids[] = {1234567, 1234568, 1234569, 1234570};
    int remaining_credits[] = {7, 8, 9, 10}; 
    char* names[] = {"Ahmet", "Mehmet", "Ayse", "Fatma"};

    courses = create_courses(ids, capacities, 3);
    students = create_students(s_ids, remaining_credits, names, 4);

    new_request("Ahmet", 5710140, 5, students, courses, 4, 3);
    printf("------------------------------\n");
    new_request("Ahmet", 5710477, 3, students, courses, 4, 3);
    printf("------------------------------\n");
    new_request("Mehmet", 5710477, 2, students, courses, 4, 3);
    printf("------------------------------\n");
    new_request("Ayse", 5710477, 6, students, courses, 4, 3);
    printf("------------------------------\n");
    new_request("Mehmet", 5710477, 7, students, courses, 4, 3);
    printf("------------------------------\n");
    new_request("Fatma", 5710111, 10, students, courses, 4, 3);
    printf("------------------------------\n");

    for (i = 0; i < 4; i++)
    {
        printf("%s, remaining credit: %d\n", students[i].name, students[i].remaining_credit);
    }

    return 0;
}
