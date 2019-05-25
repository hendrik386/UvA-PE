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

void generate_and_add(const unsigned int start, const unsigned int stop, const unsigned int work) {
    unsigned int *A = generate_intput(start, stop);
    unsigned int *B = generate_intput(start, stop);
    unsigned int *C = new unsigned int[stop - start];

    add(A, B, C, 0, work);

    delete[] A;
    delete[] B;
    delete[] C;
}

int main(void) {
    timeval before, after;

    // unsigned int *A = generate_intput(AMOUNT);
    // unsigned int *B = generate_intput(AMOUNT);
    // unsigned int *C = new unsigned int[AMOUNT];

    const unsigned int work = AMOUNT / 4;

    gettimeofday(&before, NULL); 

    // std::thread t1 (add, A, B, C, 0, work);
    // std::thread t2 (add, A, B, C, work, work * 2);
    // std::thread t3 (add, A, B, C, work * 2, work * 3);
    // std::thread t4 (add, A, B, C, work * 3, AMOUNT);
    std::thread t1 (generate_and_add, 0, work, work);
    std::thread t2 (generate_and_add, work, work * 2, work);
    std::thread t3 (generate_and_add, work * 2, work * 3, work);
    std::thread t4 (generate_and_add, work * 3, AMOUNT, work);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    // add(A, B, C, 0, AMOUNT);
    gettimeofday(&after, NULL);

    std::cout << "time: " << (after.tv_sec + (after.tv_usec / 1000000.0)) -(before.tv_sec + (before.tv_usec / 1000000.0)) << std::endl;

    return 0;
}