#include <stdio.h>
#include "the3.h"

int main()
{
    Course* courses;
    Student* students;

    int ids[] = {5710140, 5710477, 5710111, 5710315, 5710232};
    int capacities[] = {2, 3, 1, 6, 5};
    int s_ids[] = {1234567, 1234568, 1234569, 1234570, 1234571, 1234572, 1234573, 1234574, 1234575, 1234576};
    int remaining_credits[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; 
    char* names[] = {"Ahmet", "Mehmet", "Ayse", "Fatma", "Ali", "Veli", "Kubra", "Busra", "Mustafa", "Merve"};

    courses = create_courses(ids, capacities, 5);
    students = create_students(s_ids, remaining_credits, names, 10);

    new_request("Ahmet", 5710140, 5, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Ahmet", 5710477, 3, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Mehmet", 5710477, 2, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Ayse", 5710477, 6, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Mehmet", 5710477, 7, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Fatma", 5710111, 10, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Fatma", 5710477, 3, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Ali", 5710111, 5, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Veli", 5710140, 7, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Veli", 5710111, 2, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Veli", 5710315, 1, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Kubra", 5710111, 2, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Kubra", 5710140, 3, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Busra", 5710315, 6, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Mustafa", 5710477, 8, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Mustafa", 5710140, 1, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Mustafa", 5710315, 1, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Merve", 5710140, 6, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Merve", 5710477, 9, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Ali", 5710315, 4, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Ali", 5710111, 7, students, courses, 10, 5);
    printf("------------------------------\n");
    new_request("Fatma", 5710315, 3, students, courses, 10, 5);
    printf("------------------------------\n");

    print_course_requests(courses, 5, 0);

    return 0;
}
