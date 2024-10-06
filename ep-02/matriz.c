#include <stdio.h>
#include <stdlib.h>

double** alocaMatriz(unsigned int n)
{
   double **M = (double**) malloc(n * sizeof(double*));
   if (M == NULL) return NULL;

   for (int i = 0; i < n; ++i)
      M[i] = (double*) malloc(n * sizeof(double));

   return M;
}

void liberaMatriz(double **A, unsigned int n)
{
   for (int i = 0; i < n; ++i)
      if (A[i] != NULL) free(A[i]);
   free(A);
}

void imprimeMatriz(double **A, unsigned int n)
{
   for (int i = 0; i < n; ++i)
   {
      for (int j = 0; j < n; ++j)
         printf("%.15e ", A[i][j]);
      printf("\n");
   }
}