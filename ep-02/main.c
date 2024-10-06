#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>

#include "inversa.h"
#include "matriz.h"

int main()
{
   double **A = NULL, **L = NULL, **U = NULL, **Inv = NULL;
   unsigned int n, i, j;

   // Lê a ordem da matriz A[n x n]
   scanf("%u", &n);
   if (n == 0) return 1;

   // Alocação de Dados (Matrizes)
   A   = alocaMatriz(n);
   L   = alocaMatriz(n);
   U   = alocaMatriz(n);
   Inv = alocaMatriz(n);

   if (A == NULL || L == NULL || U == NULL || Inv == NULL)
   {
      if (A != NULL)   liberaMatriz(A, n);
      if (L != NULL)   liberaMatriz(L, n);
      if (U != NULL)   liberaMatriz(U, n);
      if (Inv != NULL) liberaMatriz(Inv, n);
      return 1;
   }

   // Lê a matriz a ser invertida:
   for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
         scanf("%lf", &A[i][j]);

   // Arruma as matrizes L e U:
   // L -> Diagonal Principal = 1
   // U -> Cópia da matriz A
   for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
         L[i][j] = ((i == j) ? 1 : 0);
   
   for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
         U[i][j] = A[i][j];

   fesetround(FE_DOWNWARD);
   fatoracaoLU(L, U, n);
   calculaInversa(L, U, Inv, n);

   printf("\nRESULTADO DE L:\n");
   imprimeMatriz(L, n);

   printf("\n");
   
   printf("RESULTADO DE U:\n");
   imprimeMatriz(U, n);

   printf("\n");

   printf("RESULTADO DE INV:\n");
   imprimeMatriz(Inv, n);

   if (A != NULL)   liberaMatriz(A, n);
   if (L != NULL)   liberaMatriz(L, n);
   if (U != NULL)   liberaMatriz(U, n);
   if (Inv != NULL) liberaMatriz(Inv, n);
   return 0;
}