#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/time.h>

#include <pthread.h>
#include <stdatomic.h>

struct thread_info
{
    uint64_t n;
    uint64_t m;

    uint64_t n_start;
    uint64_t n_stop;

    uint64_t m_start;
    uint64_t m_stop;

    atomic_ulong *histo;
    void * picture;
};

void *compute(void *info) {
    // printf("running compute\n");
    struct thread_info *ti = (struct thread_info *) info;
    uint64_t n = ti->n;
    uint64_t m = ti->m;
    uint8_t(*picture)[n][m] = ti->picture;

    for (uint64_t in = ti->n_start; in < ti->n_stop; ++in) {
        for (uint64_t im = ti->m_start; im < ti->m_stop; ++im) {
            ++ti->histo[(*picture)[in][im]];
        }
    }
}

int main(int argc, char *argv[]){
    int32_t c;
    uint64_t n = 1;
    uint64_t m = 1;
    int32_t number_of_threads = 1;
    bool print = false;
    char *file_name = NULL;
    int multiply = 0;

    while((c = getopt(argc, argv, "n:m:p:rf:x:")) != -1) {
    switch (c)
    {   
        case 'n':
            n = strtoul(optarg, 0 ,10);
            break;

        case 'm':
            m = strtoul(optarg, 0, 10);
            break;

        case 'p':
            number_of_threads = atoi(optarg);
            break;

        case 'r':
            print = true;
            break;

        case 'f':
            file_name = optarg;
            break;

        case 'x':
            multiply = atoi(optarg);
            break;

        default:
            break;
        }
    }

    FILE *f;
    if (!(f = fopen(file_name, "r"))) {
        printf("unalbe to open %s", file_name);
        exit(1);
    }

    char format[2];
    unsigned imgw, imgh, maxv;

    if (fscanf(f, "%2s", format) != 1) exit; 
    if (format[0] != 'P' || format[1] != '2') {
        printf("only ASCII PGM input is supported");
        exit(1);
    }
    
    if (fscanf(f, "%u", &imgw) != 1 ||
        fscanf(f, "%u", &imgh) != 1 ||
        fscanf(f, "%u", &maxv) != 1) exit(1);
    
    if (imgw != n || imgh != m) {
        fprintf(stderr, "input data size (%ux%u) does not match cylinder size (%zux%zu)\n",
                imgw, imgh, n, m);
        exit(1);
    }
    
    if (multiply != 0) {
        n *= multiply;
        m *= multiply;
    }

    uint8_t *p = malloc(n * m * sizeof(uint8_t));

    if (p == NULL ) {
        printf("Not able to alloc\n");
        exit(1);
    }

    uint8_t v;
    uint64_t idx;
    for (idx = 0; idx < imgw * imgh; ++idx) {
        if (fscanf(f, "%hhu", &v) != 1) {
            printf("invalid data\n");
            exit(1);
        }
        p[idx] = v;
    } 

    uint64_t index = idx;
    for (uint32_t i = 1; i < multiply * multiply; ++i) {
        memcpy(&p[index], &p[0], imgw * imgh * sizeof(uint8_t));
        index += idx;
    }

    uint8_t(*restrict picture)[n][m] = (uint8_t(*)[n][m]) p;

    /* calculate histogram */    
    atomic_ulong hist[256];
    memset(hist, 0, 256 * sizeof(atomic_ulong));

    if (number_of_threads > n) {
        number_of_threads = n;
    }
    printf("number of threads %d\n", number_of_threads);

    pthread_t threads[number_of_threads];
    struct thread_info tis[number_of_threads];

    uint64_t start = 0;
    uint64_t size =  n / number_of_threads;
    uint64_t left_over = n % number_of_threads;

    // struct thread_info ti;
    tis[0].n = n;
    tis[0].m = m;
    tis[0].n_start = start;
    tis[0].n_stop = size + left_over;
    tis[0].m_start = 0;
    tis[0].m_stop = m;
    tis[0].histo = hist;
    tis[0].picture = (*picture);

    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    pthread_create(&threads[0],
                    NULL,
                    &compute,
                    &tis[0]);

    start = size + left_over;
    for (uint32_t idx = 1; idx < number_of_threads; ++idx) {
        tis[idx].n = n;
        tis[idx].m = m;
        tis[idx].n_start = start;
        tis[idx].n_stop = start + size;
        tis[idx].m_start = 0;
        tis[idx].m_stop = m;
        tis[idx].histo = hist;
        tis[idx].picture = (*picture);

        start += size;
        pthread_create(&threads[idx],
                        NULL,
                        &compute,
                        &tis[idx]);
    }

    for (uint32_t idx = 0; idx < number_of_threads; ++idx) {
        pthread_join(threads[idx], NULL);
    }

    struct timeval after;
	gettimeofday(&after, NULL);

    free(p);

    if(print) {
        uint64_t total = 0;
        for (uint8_t idx = 0; idx < 255; ++idx) {
            total += hist[idx];
            printf("hist %d: %lu\n", idx, hist[idx]);
        }
        printf("hist %d: %lu\n", 255, hist[255]);
        printf("total of %lu pixels\n" ,total + hist[255]);
    }

    double time = (double)(after.tv_sec - start_time.tv_sec) + 
		(double)(after.tv_usec - start_time.tv_usec) / 1e6;

	printf("Execution time: %1.6f seconds\n", time);
}
