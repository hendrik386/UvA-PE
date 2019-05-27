#include <thread>
#include <iostream>
#include <sys/time.h>

#define AMOUNT 600000000

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

int main(void) {
    timeval before, after;

    unsigned int *A = generate_intput(AMOUNT);
    unsigned int *B = generate_intput(AMOUNT);
    unsigned int *C = new unsigned int[AMOUNT];

    gettimeofday(&before, NULL); 

    unsigned int work = AMOUNT / 4;

    std::thread t1 (add, A, B, C, 0, work);
    std::thread t2 (add, A, B, C, work, work * 2);
    std::thread t3 (add, A, B, C, work * 2, work * 3);
    std::thread t4 (add, A, B, C, work * 3, AMOUNT);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    // add(A, B, C, 0, AMOUNT);
    gettimeofday(&after, NULL);

    std::cout << "time: " << (after.tv_sec + (after.tv_usec / 1000000.0)) -(before.tv_sec + (before.tv_usec / 1000000.0)) << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}