#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    time_t start = clock();
    srand(time(NULL));
    int num_elements = 1000000;
    int array[1000000];
    for (int i=0; i < num_elements; i++) {
        array[i] = 1;
        //array[i] = rand()%2000 - 1000;
    }
    int sum = 0;
    for (int i=0; i<num_elements; i++) {
        sum += array[i];
    }
    int time = clock() - start;
    printf("sum: %d\ntime: %d\n", sum, time);
}
