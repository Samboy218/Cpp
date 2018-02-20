#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
    time_t start = clock();
    srand(time(NULL));
    int num_elements = 100000000;
    double* array = (double*)malloc(sizeof(double) * num_elements);
    if (!array) {
        printf("Malloc failed!\n");
        return 1;
    }
    for (int i=0; i < num_elements; i++) {
        array[i] = 1;
        //array[i] = rand()%2000 - 1000;
    }
    double sum = 0;
    int thread_count = atoi(argv[1]);
#pragma omp parallel num_threads(thread_count)
    {
        double my_sum = 0;
        int my_id = omp_get_thread_num();

#pragma omp critical
        printf("Hello from %d\n", my_id);
        
        int size = num_elements/thread_count;
        int start = my_id*size;
        int end;
        if (my_id == thread_count-1) {
            end = num_elements;
        }
        else {
            end = start+size;
        }
        for (int i=start; i<end; i++) {
            my_sum += array[i];
        }
#pragma omp atomic
        sum += my_sum;
    }
    double time = (double)(clock() - start)/CLOCKS_PER_SEC;
    FILE * file;
    file = fopen("timing.txt", "a");
    fprintf(file, "%f\n", time);
    printf("Sum: %f\ntime: %f\n", sum, time);
    fclose(file);
    free(array);
}
