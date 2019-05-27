#include <thread>
#include <iostream>
#include <sys/time.h>

#define AMOUNT 600000000

unsigned int *generate_intput(const unsigned int start, const unsigned int stop) {
    unsigned int *values = new unsigned int[stop - start];

    unsigned int number = start;
    for(unsigned int idx = 0; idx < stop - start; ++idx) {
        values[idx] = number++;
    }

    return values;
}

unsigned int *generate_intput(const unsigned int amount) {
    unsigned int *values = new unsigned int[amount];

    for(unsigned int idx = 0; idx < amount; ++idx) {
        values[idx] = idx;
    }

    return values;
}

void add(const unsigned int *A, const unsigned int *B, unsigned int *C, const unsigned int start, const unsigned int stop) {
    for (unsigned int idx = start; idx < stop; ++idx) {
        C[idx] = A[idx] + B[idx];
    }
}

void generate_and_add(const unsigned int start, const unsigned int stop, const unsigned int work, double *time) {
    timeval before, after;

    unsigned int *A = generate_intput(start, stop);
    unsigned int *B = generate_intput(start, stop);
    unsigned int *C = new unsigned int[stop - start];

    gettimeofday(&before, NULL); 
    add(A, B, C, 0, work);
    gettimeofday(&after, NULL);

    *time = (after.tv_sec + (after.tv_usec / 1000000.0)) -(before.tv_sec + (before.tv_usec / 1000000.0));

    delete[] A;
    delete[] B;
    delete[] C;
}

int main(void) {

    const unsigned int work = AMOUNT / 4;

    double time1 = 0, time2 = 0, time3 = 0, time4 = 0;

    std::thread t1 (generate_and_add, 0, work, work, &time1);
    std::thread t2 (generate_and_add, work, work * 2, work, &time2);
    std::thread t3 (generate_and_add, work * 2, work * 3, work, &time3);
    std::thread t4 (generate_and_add, work * 3, AMOUNT, work, &time4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    // add(A, B, C, 0, AMOUNT);
    

    std::cout << "time: " << time1 + time2 + time3 + time4 << std::endl;

    return 0;
}