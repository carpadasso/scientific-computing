#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>

#include "inversa.h"
#include "matriz.h"
#include "utils.h"

int main()
{
   double **A = NULL, **L = NULL, **U = NULL, **Inv = NULL;
   double **I = NULL, **Mult = NULL, **R = NULL;
   double tempo, norma;
   unsigned int n, i, j;

   // Lê a ordem da matriz A[n x n]
   scanf("%u", &n);
   if (n == 0) return 1;

   // Alocação de Dados (Matrizes)
   A   = alocaMatriz(n);
   L   = alocaMatriz(n);
   U   = alocaMatriz(n);
   Inv = alocaMatriz(n);

   I = alocaMatriz(n);
   Mult = alocaMatriz(n);
   R = alocaMatriz(n);

   // Caso não seja possível alocar espaço para uma das matrizes,
   // libera as matrizes já alocadas e retorna.
   if (A == NULL || L == NULL || U == NULL || Inv == NULL || 
       I == NULL || Mult == NULL || R == NULL)
   {
      if (A != NULL)   liberaMatriz(A, n);
      if (L != NULL)   liberaMatriz(L, n);
      if (U != NULL)   liberaMatriz(U, n);
      if (Inv != NULL) liberaMatriz(Inv, n);

      if (I != NULL)    liberaMatriz(I, n);
      if (Mult != NULL) liberaMatriz(Mult, n);
      if (R != NULL)    liberaMatriz(R, n);
      return 1;
   }

   // Lê a matriz a ser invertida, A[]
   leMatriz(A, n);

   // Gera a matriz Identidade I[]
   geraIdentidade(I, n);

   // Pré-processamento das matrizes L[] e U[]
   /* Copia a matriz A para U e a matriz identidade I para L */
   copiaMatriz(A, U, n);
   copiaMatriz(I, L, n);

   // Parte I: Cálculo da Inversa
   /* Primeiro, define-se o arrendodamento da máquina para baixo,
    * depois se efetua a fatoração da matriz A em L e U e em seguida
    * calcula-se a matriz inversa A^-1 a partir de L e U. */
   fesetround(FE_DOWNWARD);

   tempo = timestamp();
   fatoracaoLU(L, U, n);
   calculaInversa(L, U, Inv, n);
   tempo = timestamp() - tempo;

   // Parte II: Cálculo do Resíduo + Média das Normas
   /* Multiplica-se a matriz A[] com sua inversa A^-1[] calculada no passo
    * anterior, e em seguida subtrai o resultado com a Identidade I[] para
    * resultar na matriz Resíduo R[]. Então calcula-se a norma L2 de cada
    * coluna de R, e faz-se a média simples. */
   multiplicaMatriz(A, Inv, Mult, n);
   subtraiMatriz(Mult, I, R, n);
   norma = calculaNorma(R, n);

   // Impressão dos Dados
   /* <ORDEM DA MATRIZ DE ENTRADA>
    * <IMPRESSÃO DA MATRIZ INVERSA>
    * <NORMA L2 DO RESÍDUO>
    * <TEMPO EM MILISEGUNDOS NO CÁLCULO DA INVERSA> */
   printf("%u\n", n);
   imprimeMatriz(Inv, n);
   printf("%.15e\n", norma);
   printf("%.8e\n", tempo);

   // Libera a memória alocada pelas Matrizes
   liberaMatriz(A, n);
   liberaMatriz(L, n);
   liberaMatriz(U, n);
   liberaMatriz(Inv, n);

   liberaMatriz(I, n);
   liberaMatriz(Mult, n);
   liberaMatriz(R, n);

   return 0;
}