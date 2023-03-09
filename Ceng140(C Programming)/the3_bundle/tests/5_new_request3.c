#include <stdio.h>
#include "the3.h"

int main(int argc, char const *argv[])
{
    Course* courses;
    Student* students;

    int ids[] = {5710140};
    int capacities[] = {3};
    int s_ids[] = {1234567};
    int remaining_credits[] = {7}; 
    char* names[] = {"Ahmet"};

    courses = create_courses(ids, capacities, 1);
    students = create_students(s_ids, remaining_credits, names, 1);

    new_request("Ahmet", 5710140, 5, students, courses, 1, 1);
    new_request("Ahmet", 5710140, 6, students, courses, 1, 1);

    printf("Course first request: %s(%d)\n", courses[0].requests->student->name, courses[0].requests->bid);

    return 0;
}
