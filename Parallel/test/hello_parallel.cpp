#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {

    int thread_count = atoi(argv[1]);
#pragma omp parallel num_threads(thread_count)
    {
        int my_id = omp_get_thread_num();

#pragma omp critical
        printf("Hello from %d\n", my_id);
        
    }
}
