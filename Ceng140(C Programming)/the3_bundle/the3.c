#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student
{
    int id;
    char* name;
    int remaining_credit;
};

struct Request
{
    struct Student* student;
    int bid;
    struct Request* next;
};

struct Course
{
    int id;
    int capacity;
    struct Request* requests;
};

typedef struct Student Student;
typedef struct Request Request;
typedef struct Course Course;


Student* create_students(int ids[], int remaining_credits[], char* names[], int student_count)
{
    int i;
    struct Student* students;
    students = (struct Student*) malloc(sizeof(struct Student)*student_count);

    if(students)
    {
        for(i=0;i<student_count;i++)
        {   
            students[i].id = ids[i];
            students[i].remaining_credit = remaining_credits[i];
            students[i].name = names[i];
        }
    }
    return students;
}

Course* create_courses(int ids[], int capacities[], int course_count)
{
    int i;
    struct Course *courses;
    courses = (struct Course*) malloc(sizeof(struct Course)*course_count);
    if(courses)
    {
        for(i=0;i<course_count;i++)
        {
            courses[i].id = ids[i];
            courses[i].capacity = capacities[i];
            courses[i].requests = NULL;
        }
    }
    return courses;
}

void append(Request** requests, Student* student, int bid)
{ 
    struct Request* nr;
    nr = (struct Request*) malloc(sizeof(struct Request));
    if(nr)
    {
    nr->bid=bid;
    nr->student = student;
    nr-> next = NULL ;
    }
    
    if(nr)
    {   
        struct Request *curr,*prev;
        curr=*requests;
        prev=NULL;
        while(curr && bid <= curr->bid)
        { 
            prev=curr;
            curr=curr->next;
        }
        nr->next=curr;
        if(prev) prev->next=nr;
        else *requests=nr;
    }
    
}

void remove_req(Request** requests,Student* student)
{   

    struct Request *curr = *requests, *prev;    
    if (curr  && curr->student->name == student->name) 
    {
        *requests = curr->next; 
        free(curr); 
        return;
    }

    while (curr && curr->student->name != student->name)
    {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr) prev->next = curr->next;

    free(curr); 
}


void new_request(char* student_name, int course_id, int bid, Student* students, Course* courses, int student_count, int course_count)
{
    int i,j;
    struct Request *req;
    req = malloc(sizeof(struct Request));
    for(i=0;i<course_count;i++)
    {
        if(courses[i].id == course_id)  break;
    }

    for(j=0;j<student_count;j++)
    {
        if(!strcmp(student_name,students[j].name))  break;

    }
    req = courses[i].requests;
    while(req)
    {
        if(req->student->name==student_name){ 
        students[j].remaining_credit+= req->bid;
        break;
            
        }
        req=req->next;
    }
    
    if(bid>students[j].remaining_credit)
    {   
        printf("%s does not have enough credit to enroll Course %d.\n",students[j].name,courses[i].id);
    }
    else
    {
        remove_req(&(courses[i].requests),&(students[j]));
        append(&(courses[i].requests),&(students[j]),bid);
        students[j].remaining_credit-= bid;
        printf("%s is added to enrollment list of Course %d. Remaining credit: %d\n",(students[j]).name,courses[i].id,students[j].remaining_credit);
    }



}

void print_course_requests(Course* courses, int course_count, int stop_at_capacity)
{   
    int i,a;
    struct Request* req;
    for(i=0;i<course_count;i++)
    {   int j;
        printf("Course: %d\n",courses[i].id);
        printf("Student List:");
        req = courses[i].requests;
        a=1;j=0;
        while(req)
        {   
            if(stop_at_capacity && (courses[i].capacity == j)) break;
            a=0;
            printf(" %s(%d)",((req)->student)->name,(req)->bid);
            req = req->next;
            j++;
        }
        if(a) printf(" No students");
        printf("\n");
    }
}


int main()
{
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

    print_course_requests(courses, 3, 0);

    return 0;
}
