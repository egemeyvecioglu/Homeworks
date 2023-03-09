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


/*
Create a student instance
*/
Student* create_students(int ids[], int remaining_credits[], char* names[], int student_count);

/*
Create a course instance
*/
Course* create_courses(int ids[], int capacities[], int course_count);

/*
Appends a bid to a linked list of bids ordered by bids descendingly.
*/
void append(Request** requests, Student* student, int bid);

/*
Add news bid to the course. If student do not have enough bid, do not update course candidate student list.
*/
void new_request(char* student_name, int course_id, int bid, Student* students, Course* courses, int student_count, int course_count);

/*
Prints accepted student list for the course.
*/
void print_course_requests(Course* courses, int course_count, int stop_at_capacity);




