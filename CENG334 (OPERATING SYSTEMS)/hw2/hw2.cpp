extern "C" {
  #include "./hw2_output.h"
};

#include<iostream>
#include<semaphore.h>
using std::cin, std::cout, std::endl, std::cerr;

sem_t* semJ;
sem_t* semL;
sem_t mutex1;
sem_t mutex2;
int *columns;

unsigned matrix_id = 0;
int **A,**B,**C,**D, **J, **L, **K;
int rowl1, rowl2, coll1, coll2;

void construct_matrices()
{
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);


    int rl,cl;
    
    cin >> rl >> cl;
    rowl1  = rl;
    coll1 = cl;

    A = new int*[rl];
    for(int i=0;i<rl;i++)
    {
        A[i] = new int[cl];
        for(int j=0;j<cl;j++)
        {
            cin >> A[i][j];
        }
    }

    cin >> rl >> cl;
    B = new int*[rl];
    for(int i=0;i<rl;i++)
    {
        B[i] = new int[cl];
        for(int j=0;j<cl;j++)
        {
            cin >> B[i][j];
        }
    }

    J = new int*[rl];
    for(int i=0;i<rl;i++)
    {
        J[i] = new int[cl];
    }
    
    semJ = new sem_t[rl];
    for (int i = 0; i < rl; i++) {
        sem_init(&semJ[i], 0, 0);
    }


    K = new int*[rl];



    cin >> rl >> cl;

    rowl2 = rl;
    coll2 = cl;

    columns = new int[cl];
    for(int i=0;i<cl;i++)
    {
        columns[i]  = 0;
    }

    C = new int*[rl];
    for(int i=0;i<rl;i++)
    {
        C[i] = new int[cl];
        for(int j=0;j<cl;j++)
        {
            cin >> C[i][j];
        }
    }

    cin >> rl >> cl;
    D = new int*[rl];
    for(int i=0;i<rl;i++)
    {
        D[i] = new int[cl];
        for(int j=0;j<cl;j++)
        {
            cin >> D[i][j];
        }
    }

    L = new int*[rl];
    for(int i=0;i<rl;i++)
    {
        L[i] = new int[cl];
    }
    semL = new sem_t[cl];
    for (int i = 0; i < cl; i++) {
        sem_init(&semL[i], 0, 0);
    }


    for(int i=0;i<rowl1;i++)
    {
        K[i] = new int[cl];
        for(int j=0;j<cl;j++)
        {
            K[i][j] = 0;
        }
    }


}

void delete_matrices()
{

    for(int i=0;i<rowl1;i++)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] J[i];
        delete[] K[i];
    }
    delete[] A;
    delete[] B;
    delete[] J;
    delete[] K;
    delete[] semJ;


    for(int i=0;i<rowl2;i++)
    {
        delete[] C[i];
        delete[] D[i];
        delete[] L[i];
    }

    delete[] C;
    delete[] D;
    delete[] L;
    delete[] semL;

}

void *add1_row(void *arg)
{
    int i = *((int *) arg);
    
    for(int j=0;j<coll1;j++)
    {
        J[i][j] = A[i][j] + B[i][j];
        hw2_write_output(0, i+1, j+1, K[i][j]);
    }
    sem_post(&semJ[i]);
    return 0;
}

void *add2_row(void *arg)
{
    int i = *((int *) arg);

    for(int j=0;j<coll2;j++)
    {
        L[i][j] = C[i][j] + D[i][j];
        hw2_write_output(1, i+1, j+1, K[i][j]);
        sem_wait(&mutex2);
        columns[j]++;
        if(columns[j] == rowl2)
        {
            for(int m = 0 ; m < rowl1; m++) sem_post(&semL[j]);
        }
        sem_post(&mutex2);


    }
    return 0;
}


void *multiply(void *arg)
{
    int i = *((int *) arg);
    sem_wait(&semJ[i]);
    for(int j=0;j<coll2;j++)
    {           
        
        for(int k=0;k<rowl2;k++)
        {
            sem_wait(&semL[j]);
            K[i][j] += J[i][k] * L[k][j];
            sem_post(&semL[j]);
        }
        hw2_write_output(2, i+1, j+1, K[i][j]);

        
    }
    sem_post(&semJ[i]);
    return 0;
}

int main()
{
    construct_matrices();
    hw2_init_output();

    pthread_t a_plus_b[rowl1], c_plus_d[rowl2], j_times_l[rowl1];
    int p_add1[rowl1], p_add2[rowl2], p_mul[rowl1];

    for (int i = 0; i < rowl1; i++) {
        p_add1[i] = i;
        p_mul[i] = i;
    }    

    for (int i = 0; i < rowl2; i++) {
        p_add2[i] = i;
    }    


    for (int i = 0; i < rowl1; i++) {
        pthread_create(&a_plus_b[i], NULL, add1_row, &p_add1[i]);
    }

    for (int i = 0; i < rowl2; i++) {
        pthread_create(&c_plus_d[i], NULL, add2_row, &p_add2[i]);
    }

    for (int i = 0; i < rowl1; i++) {
        pthread_create(&j_times_l[i], NULL, multiply, &p_mul[i]);
    }


    for (int i = 0; i < rowl1; i++) {
        pthread_join(a_plus_b[i], NULL);
    }

    for (int i = 0; i < rowl2; i++) {
        pthread_join(c_plus_d[i], NULL);
    }

    for (int i = 0; i < rowl1; i++) {
        pthread_join(j_times_l[i], NULL);
    }

    for(int i=0;i<rowl1;i++)
    {
        for(int j=0;j<coll2;j++)
        {
            cout << K[i][j];
            cout << " ";
        }
        cout << endl;
    }


    delete_matrices();

    return 0;
}
