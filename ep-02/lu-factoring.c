#include <stdio.h>
#include <stdlib.h>

#include <fenv.h>

unsigned int encontraMax(double **A, unsigned int n, unsigned int i)
{
   unsigned int max = i;

   for (int j = max; j < n; ++j)
      if (A[j][i] > A[max][i]) max = j;
   
   return max;
}

void trocaLinha(double **L, double **U, unsigned int i, unsigned int iPivo)
{
   double *tmp_p;

   tmp_p = L[i];
   L[i] = L[iPivo];
   L[iPivo] = tmp_p;

   tmp_p = U[i];
   U[i] = U[iPivo];
   U[iPivo] = tmp_p;
}

void fatoracaoLU(double **L, double **U, double *x, unsigned int n)
{
   // Parte I: Cálculo das Matrizes L & U
   for (int i = 0; i < n; i++)
   {
      unsigned int iPivo = encontraMax(U, n, i);
      if (i != iPivo)
         trocaLinha(L, U, i, iPivo);
      
      for (int k = i + 1; k < n; ++k)
      {
         double m = U[k][i] / U[i][i];

         // Atualiza valores de L
         L[k][i] = m;

         // Atualiza valores de U
         U[k][i] = 0.0;
         for (int j = i + 1; j < n; ++j)
            U[k][j] -= U[i][j] * m;
      }
   }

   // Parte II: Cálculo da Inversa
}

int main()
{
   double **A, **L, **U, *x;
   unsigned int n;
   int i, j;

   // Lê a ordem da matriz A[n x n]
   scanf("%u", &n);
   if (n <= 0)
      return 1;

   // Lê a matriz a ser invertida:
   A = (double**) malloc(n*n*sizeof(double));
   for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
         scanf("%lf", &A[i][j]);

   L = (double**) malloc(n*n*sizeof(double));
   U = (double**) malloc(n*n*sizeof(double));

   // Arruma as matrizes L e U:
   // L -> Diagonal Principal = 1
   // U -> Cópia da matriz A
   for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
         L[i][j] = (i == j) ? 1 : 0;
   
   for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
         U[i][j] = A[i][j];

   // Execução do Método: FATORAÇÃO LU
   fesetround(FE_UPWARD);
   fatoracaoLU(L, U, x, n);
}