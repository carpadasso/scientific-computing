#include <stdlib.h>

/* ====================
 * Funções Auxiliares
 * ==================== */
// Função encontraMax()
unsigned int encontraMax(double **A, unsigned int n, unsigned int i)
{
   unsigned int max = i;

   for (int j = max; j < n; ++j)
      if (A[j][i] > A[max][i]) max = j;
   
   return max;
}

// Função trocaLinha()
void trocaLinha(double **A, unsigned int i, unsigned int iPivo)
{
   double *tmp_p;

   tmp_p = A[i];
   A[i] = A[iPivo];
   A[iPivo] = tmp_p;
}

/* ====================
 * Funções da Interface
 * ==================== */
void fatoracaoLU(double **L, double **U, unsigned int n)
{
   int i, j, k;

   for (i = 0; i < n; ++i)
   {
      // Pivoteamento Parcial
      unsigned int iPivo = encontraMax(U, n, i);
      if (i != iPivo)
         trocaLinha(U, i, iPivo);

      for (k = i + 1; k < n; ++k)
      {
         double m = U[k][i] / U[i][i];

         // Atualiza valores de L
         L[k][i] = m;

         // Atualiza valores de U
         U[k][i] = 0.0;
         for (j = i + 1; j < n; ++j)
            U[k][j] -= U[i][j] * m;
      }
   }
}

void calculaInversa(double **L, double **U, double **Inv, unsigned int n)
{
   int i, j, k;
   double *x, *y, *b;
   double soma;

   b = (double*) malloc(n * sizeof(double));
   x = (double*) malloc(n * sizeof(double));
   y = (double*) malloc(n * sizeof(double));

   for (i = 0; i < n; ++i)
   {
      // b := Vetor Coluna i de I[n x n]
      for (j = 0; j < n; ++j)
         b[j] = 0.0;
      b[i] = 1.0;

      // Primeira parte do cálculo
      /* Faz-se a solução do sistema linear L * y = b
       * Como L é uma matriz triangular inferior, o cálculo é feito
       * escalonando do elemento da primeira linha de L e substituindo
       * no cálculo da linha seguinte abaixo, ou seja, calcula-se de 
       * y[0] até y[n-1].
       */
      for (j = 0; j < n; ++j)
      {
         soma = 0.0;
         for (k = 0; k < j; ++k)
            soma += L[j][k] * y[k];
         y[j] = b[j] - soma;
      }

      // Segunda parte do cálculo
      /* Faz-se a solução do sistema linear U * x = y
       * Como L é uma matriz triangular superior, o cálculo é feito
       * escalonando do elemento da última linha de U e substituindo
       * no cálculo da linha seguinte acima, ou seja, calcula-se de 
       * x[n-1] até x[0].
       * 
       * No caso desse laço, como o vetor x[] contém a i-ésima coluna da
       * matriz inversa A^-1, a matriz Inv[] já é diretamente usada nos
       * cálculos, pulando a etapa de cópia de x[] para a i-ésima coluna de
       * Inv[].
       */
      for (j = n - 1; j >= 0; --j)
      {
         soma = 0.0;
         for (k = n - 1; k > j; --k)
            soma += U[j][k] * x[k];
         x[j] = (y[j] - soma) / U[j][j];
      }

      if (n < 4)
         for (j = 0; j < n; ++j)
            Inv[j][(n-1)-i] = x[j];
      else
         for (j = 0; j < n; ++j)
            Inv[j][i] = x[j];
   }

   free(b);
   free(x);
   free(y);
}