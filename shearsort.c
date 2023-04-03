#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>

#define THREAD_NUM 4

sem_t semaphore;

// array to sort 
int numArray[4][4];



void* row(void* a) {
    sem_wait(&semaphore);

    int rowNum = *(int*)a;
    // pull out row into new array
    int rowArr[4];
    int i;
    for (i = 0; i < 4; i++) {
        rowArr[i] = numArray[rowNum][i];
    }

    // sort row
    int j, swap;
    for (i = 0 ; i < 4 - 1; i++)
    {
        for (j = 0 ; j < 4 - i - 1; j++)
        {
        if (rowArr[j] > rowArr[j+1]) 
            {
            swap = rowArr[j];
            rowArr[j] = rowArr[j+1];
            rowArr[j+1] = swap;
            }
        }
    }

    // if even, place into original array in ascending order
    if ( rowNum % 2 == 0) {
        for (i = 0; i < 4; i++) {
            numArray[rowNum][i] = rowArr[i];
        }

    }

    // if odd, place into original array in descending order
    if ( rowNum% 2 != 0) {
        for (i = 3, j = 0; i >=0; i--, j++) {
            numArray[rowNum][i] = rowArr[j];
        }
        
    }
       
    sem_post(&semaphore);
    free(a);
    return 0;
}


void* col(void* a) {
    sem_wait(&semaphore);

    int numCol = *(int*)a;

    // pull out col into new array
    int newArr[4];
    int i;
    for (i = 0; i < 4; i++) {
        newArr[i] = numArray[i][numCol];
    }

    // sort column
    int j, swap;
    for (i = 0 ; i < 4 - 1; i++)
    {
        for (j = 0 ; j < 4 - i - 1; j++)
        {
        if (newArr[j] > newArr[j+1]) 
            {
            swap = newArr[j];
            newArr[j] = newArr[j+1];
            newArr[j+1] = swap;
            }
        }
    }

    // place into original array in ascending order
    for (i = 0; i < 4; i++) {
        numArray[i][numCol] = newArr[i];
    }
       
    sem_post(&semaphore);
    free(a);
    return 0;
}




int main(int argc, char *argv[]) {


    // prompt for integers and set up array

    printf("Enter 16 integers: ");
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            int num;
            scanf("%d", &num);
            numArray[i][j] = num;
        }
    }
    printf("\n");

    // print out original array 
    printf("Original: \n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", numArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    // specify number of iterrations for shearsort 
    int count = 1; // keep track of even/odd 
    int n = 4; // size of array
    int numIter = log2(n) + 1;
    numIter *= 2;  // row and col are separate iterations


    // create and join threads 
    while (count <= numIter) {

        pthread_t th[THREAD_NUM];
        sem_init(&semaphore, 0, 1);

        // if even, sort columns
        if (count % 2 == 0) {
            
            int i;
            for (i = 0; i < THREAD_NUM; i++) {
                int* a = malloc(sizeof(int));
                *a = i; // number of col
                if (pthread_create(&th[i], NULL, &col, (void*) a) != 0) {
                    perror("Failed to create thread");
                }
            }

            for (i = 0; i < THREAD_NUM; i++) {
                if (pthread_join(th[i], NULL) != 0) {
                    perror("Failed to join thread");
                }
            }

        }

        // if odd sort rows 
        if (count % 2 != 0) {

            int i;
            for (i = 0; i < THREAD_NUM; i++) {
                int* a = malloc(sizeof(int));
                *a = i; // number of row
                if (pthread_create(&th[i], NULL, &row, (void*) a) != 0) {
                    perror("Failed to create thread");
                }
            }

            for (i = 0; i < THREAD_NUM; i++) {
                if (pthread_join(th[i], NULL) != 0) {
                    perror("Failed to join thread");
                }
            }

        }

        count++;
    }

    // print out sorted array
    printf("Sorted: \n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", numArray[i][j]);
        }
        printf("\n");
    }

   
    return 0;
}


