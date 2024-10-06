#include <stdio.h>
#include <stdlib.h>

#include <math.h>

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

void leMatriz(double **A, unsigned int n)
{
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         scanf("%lf", &A[i][j]);
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

void copiaMatriz(double **A, double **B, unsigned int n)
{
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         B[i][j] = A[i][j];
}

void geraIdentidade(double **I, unsigned int n)
{
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         I[i][j] = (i == j) ? 1.0 : 0.0;
}

void subtraiMatriz(double **A, double **B, double **R, unsigned int n)
{
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         R[i][j] = A[i][j] - B[i][j];
}

void multiplicaMatriz(double **A, double **B, double **R, unsigned int n)
{
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
      {
         R[i][j] = 0.0;
         for (int k = 0; k < n; ++k)
            R[i][j] += A[i][k] * B[k][j];
      }
}

double calculaNorma(double **A, unsigned int n)
{
   double norma, normaColuna;

   norma = 0.0;
   for (int i = 0; i < n; ++i)
   {
      normaColuna = 0.0;
      for (int j = 0; j < n; ++j)
         normaColuna += A[j][i] * A[j][i];
      norma += sqrt(normaColuna);
   }
   norma = norma / n;
   
   return norma;
}