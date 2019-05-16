/* SpMV: this file contains the I/O functions used to read and write matrices
 * in the Market Matrix format(see
 * https://math.nist.gov/MatrixMarket/formats.html#MMformat), using the
 * functions in mmio.c in its turn.
 * A vector of the appropriate size is generated and multiplied with the matrix.
 * There are also functions to generate your own matrices.
 * The reading also supports the "is_pattern" flag from the Matrix Market format. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mmio.h"
#include "spmv_kernel.h"

#define N  512
#define M  512

#define REP 1000



void generate_mat(int m, int n, float *A) {
  int i;

  for (i=0; i<(m*n); i++) A[i] = 1; //i/10; 

}

void read_sparse(FILE *f, int m, int n, int nz, float *A, int is_pattern) {
  int i, row, col;
  float val;  
  printf("Sparce\n");
    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

    if (is_pattern) {
      printf("pattern\n");
        for (i=0; i<nz; i++)
        {
            if(!fscanf(f, "%d %d\n", &row, &col)){
              printf("read error\n");
              exit(1);
            }
            A[(row-1)*n+col-1] = 1.0f;   /* adjust from 1-based to 0-based */
        }
    }
    else {
      printf("no pattern\n");
      for (i=0; i<nz; i++)
      {
          if(!fscanf(f, "%d %d %f\n", &row, &col, &val)){
            printf("read error\n");
            exit(1);
          }
          A[(row-1)*n+col-1] = val;   /* adjust from 1-based to 0-based */
      }
    }
}

struct csr read_sparse_csr(FILE *f, int m, int n, int nz, int is_pattern) {
  int i, j;
  struct csr current_csr;

  printf("Sparce\n");
    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

    if (is_pattern) {
      printf("pat\n");
      current_csr.values = NULL;
      current_csr.column_indices = (int *) malloc(nz * sizeof(int));
      current_csr.row_offset = (int *) malloc((m + 1)  * sizeof(int));

      int *rows = (int *) malloc(nz * sizeof(int));
      int *cols = (int *) malloc(nz * sizeof(int));

      for (i = 0; i < nz; ++i)
      {
        if(!fscanf(f, "%d %d\n", &rows[i], &cols[i])){
          printf("read error\n");
          exit(1);
        }
      }

      int current_index = 0;

      for (i = 0; i < m; ++i) {
        current_csr.row_offset[i] = current_index;
        for (j = 0; j < nz; ++j) {
          if (rows[j] - 1 == i) {
            current_csr.column_indices[current_index++] = cols[j] - 1;
          }
        }
      }
      current_csr.row_offset[m] = nz;

      free(rows);
      free(cols);
    }
    else {
      current_csr.values = (float *) malloc(nz * sizeof(float));
      current_csr.column_indices = (int *) malloc(nz * sizeof(int));
      current_csr.row_offset = (int *) malloc((m + 1)  * sizeof(int));

      int *rows = (int *) malloc(nz * sizeof(int));
      int *cols = (int *) malloc(nz * sizeof(int));
      float *vals = (float *) malloc(nz * sizeof(float));

      for (i = 0; i < nz; ++i)
      {
        if(!fscanf(f, "%d %d %f\n", &rows[i], &cols[i], &vals[i])){
          printf("read error\n");
          exit(1);
        }
      }

      int current_index = 0;

      for (i = 0; i < m; ++i) {
        current_csr.row_offset[i] = current_index;
        for (j = 0; j < nz; ++j) {
          if (rows[j] - 1 == i) {
            current_csr.column_indices[current_index] = cols[j] - 1;
            current_csr.values[current_index++] = vals[j];
          }
        }
      }
      current_csr.row_offset[m] = nz;

      free(rows);
      free(cols);
    }
    return current_csr;
}

void write_sparse(FILE *f, int m, int p, const float *C) {
   int i, nz=0; 
   MM_typecode matcode;

   for (i=0; i<m*p; i++) if (C[i] != 0.0) nz++; 

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_coordinate(&matcode);
    mm_set_real(&matcode);

    mm_write_banner(f, matcode); 
    mm_write_mtx_crd_size(f, m, p, nz);

    for (i=0; i<m*p; i++) {
	if (C[i] != 0.0) 
          fprintf(f, "%d %d %f\n", i/p+1, i%p+1, C[i]);
    }

}

void write_vector(FILE* f, int m, const float* C) {
  int i;

  for (i=0; i<m; i++) {
      fprintf(f, "%f\n", C[i]);
  }
}

void read_dense(FILE *f, int m, int n, float *A) {
  printf("Dense\n");
  int row, col;

  for(row=0; row<m; row++) { 
     for (col=0; col<n; col++) {
        if(!fscanf(f, "%f ", &A[row*n+col])){
          printf("read error\n");
          exit(1);
        }
//	printf("%20.19f \n", A[row*(*n)+col]);
     }
  } 
}


int read_mat(int *m, int *n, int *nzA, FILE* fa, int *is_pattern) {
  MM_typecode ta;
  int ret_code; 

  if (mm_read_banner(fa, &ta) != 0)
    {
        printf("Could not process Matrix Market banner for A.\n");
        return -3;
    }

  if (mm_is_pattern(ta)) *is_pattern = 1;

  if (mm_is_complex(ta)) return -6;

  if (mm_is_matrix(ta) && mm_is_sparse(ta))
    {
        if ((ret_code = mm_read_mtx_crd_size(fa, m, n, nzA)) !=0)
           return -10;
    }
  else if (mm_is_matrix(ta) && mm_is_array(ta)) {
	*nzA = 0;
        if ((ret_code = mm_read_mtx_array_size(fa, m, n)) !=0)
           return -11;

    }
  else return -8; 

  return 0;
}

int main (int argc, char** argv) {
 float *B, *C;
 struct timeval before, after;
 int r, m, n, err;
 int nzA=0, is_pattern = 1;
 FILE *fa, *fc; 
 
#ifdef GENERATE 
 m=M; n=N;
#else 
 if (argc < 2) {
    fprintf(stderr, "Usage: %s [matrix-market-filename] [result-vector-filename]\n", argv[0]);
    exit(1);
 }
 else {
    if ((fa = fopen(argv[1], "rt")) == NULL) exit(1);
    err = read_mat(&m, &n, &nzA, fa, &is_pattern);    
    printf("n: %d, m: %d, nzA: %d\n", n, m, nzA);
    if (err == -15) {
	printf("Matrices are incompatible! \n");
	fclose(fa); 
	exit(1);
    }
 }
#endif

//  A = (float *)calloc(m*n,sizeof(float));
//  if (A==NULL) {printf("Out of memory A! \n"); exit(1);}
 B = (float *)calloc(m,sizeof(float));
 if (B==NULL) {printf("Out of memory B! \n"); exit(1);} 

#ifdef GENERATE
   generate_mat(m,n,A);
   generate_mat(n,1,B);
#else 
    struct csr current_csr;
    if (nzA>0) {
	  // read_sparse(fa, m,n,nzA, A, is_pattern);
      current_csr = read_sparse_csr(fa, m, n ,nzA, is_pattern);
    }
    else {
      printf("Dense not working at the moment\n");
      exit(0);
	    //read_dense(fa, m,n, A);
    }
    generate_mat(n,1,B);
    fclose(fa);
    
#endif

 C = (float *)calloc(m,sizeof(float));
 if (C==NULL) {printf("Out of memory C1! \n"); exit(1);}

//naive implementation 
#ifdef TIMING
  gettimeofday(&before, NULL); 
#endif

for (r=0; r<REP; r++) 
 /* Call the SpMV kernel. */
//  spmv(m,n,A,B,C);
spmv_csr(m, n, nzA, &current_csr, B, C);

#ifdef TIMING
  gettimeofday(&after, NULL);
  printf("Reference code: %10.10f seconds \n", ((after.tv_sec + (after.tv_usec / 1000000.0)) -
            (before.tv_sec + (before.tv_usec / 1000000.0)))/REP);

#endif

 if ((fc = fopen(argv[2], "wt")) == NULL) exit(3);    
// write_sparse(fc,n,m,C);
 write_vector(fc,m,C);
 fclose(fc);  

//  free(A);
 free(B); 
 free(C);

 free(current_csr.column_indices);
 free(current_csr.row_offset);
 if (current_csr.values != NULL) free(current_csr.values);

}

