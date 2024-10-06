#ifndef __MATRIZ_H__
#define __MATRIZ_H__

// Biblioteca matriz.h
// Conteúdo: 09 funções

// Função alocaMatriz()
/* A função recebe a ordem/tamanho de uma matriz QUADRADA de doubles e, em 
 * seguida, aloca memória para a matriz. Retorna um ponteiro para a matriz.
 *
 * Parâmetros:
 * - unsigned int n: Ordem/tamanho da matriz a ser alocada
 */
double** alocaMatriz(unsigned int n);

// Função liberaMatriz()
/* A função recebe um ponteiro para matriz quadrada de doubles A[] e a 
 * ordem/tamanho da matriz. Em seguida, libera a memória alocada para cada
 * ponteiro armazenado A[0..n] e o próprio ponteiro A[].
 *
 * Parâmetros:
 * - double **A: Matriz quadrada que se deseja liberar a memória alocada
 * - unsigned int n: Ordem/tamanho da matriz A[]
 */
void liberaMatriz(double **A, unsigned int n);

// Função leMatriz()
/* A função recebe um ponteiro para matriz quadrada de doubles A[] e a 
 * ordem/tamanho da matriz. Em seguida, lê os valores da matriz através da
 * função scanf(), usando a stream padrão de dados stdin.
 * 
 * Parâmetros:
 * - double **A: Matriz quadrada que se deseja preencher com valores lidos do
 * teclado
 * - unsigned int n: Ordem/tamanho da matriz A[]
 */
void leMatriz(double **A, unsigned int n);

// Função imprimeMatriz()
/* A função recebe um ponteiro para matriz quadrada de doubles A[] e a
 * ordem/tamanho da matriz. Em seguida, imprime a matriz na tela usando
 * a função printf() de acordo com o modelo abaixo:
 * 
 * a11 a12 a13 ... a1n 
 * a21 a22 a23 ... a2n 
 * ... ... ... ... ...
 * an1 an2 an3 ... ann
 * 
 * Parâmetros:
 * - double **A: Matriz quadrada que se deseja imprimir na tela
 * - unsigned int n: Ordem/tamanho da matriz A[]
 */
void imprimeMatriz(double **A, unsigned int n);

// Função copiaMatriz()
/* A função recebe dois ponteiros para matriz quadrada de doubles, A[] e B[], 
 * e a ordem/tamanho das matrizes (Ordem(A) = Ordem(B)). Em seguida, copia o
 * conteúdo de A na matriz B, ou seja, B[i, j] := A[i, j], para i, j < n.
 * 
 * Parâmetros:
 * - double **A: Matriz quadrada a ser copiada A[]
 * - double **B: Matriz quadrada destino B[]
 * - unsigned int n: Ordem/tamanho das matrizes A e B
 */
void copiaMatriz(double **A, double **B, unsigned int n);

// Função geraIdentidade()
/* A função recebe um ponteiro para matriz quadrada de doubles I[] e a
 * ordem/tamanho da matriz. Em seguida, modifica o conteúdo de I[] para
 * armazenar a matriz Identidade I[n x n] dentro de I[], ou seja:
 *  - a diagonal principal de I[] := 1
 *  - elementos que não estão na diagonal principal := 0
 * 
 * Parâmetros:
 * - double **I: Matriz quadrada que se deseja armazenar a matriz Identidade
 * - unsigned int n: Ordem/tamanho da matriz I[]
 */
void geraIdentidade(double **I, unsigned int n);

// Função subtraiMatriz()
/* Recebe três ponteiros para matriz quadrada de doubles, A[], B[] e R[], e a
 * ordem/tamanho das matrizes (Ordem(A) = Ordem(B) = Ordem(R)). Em seguida,
 * efetua a subtração da matriz A pela B e armazena o resultado em R, ou seja,
 * A[i, j] - B[i, j] = R[i, j], para todo i, j < n.
 * 
 * Parâmetros:
 * - double **A: Matriz quadrada que serve como Minuendo
 * - double **B: Matriz quadrada que serve como Subtraendo
 * - double **R: Matriz quadrada que serve como a Diferença de A e B
 * - unsigned int n: Ordem/tamanho das matrizes A, B e R
 */
void subtraiMatriz(double **A, double **B, double **R, unsigned int n);

// Função multiplicaMatriz()
/* Recebe três ponteiros para matriz quadrada de doubles, A[], B[] e R[], e a
 * ordem/tamanho das matrizes (Ordem(A) = Ordem(B) = Ordem(R)). Em seguida,
 * efetua a multiplicação da matriz A pela B e armazena o resultado em R através
 * da mutiplicação padrão de matrizes.
 * 
 * Parâmetros:
 * - double **A: Matriz quadrada que serve como Fator número 1
 * - double **B: Matriz quadrada que serve como Fator número 2
 * - double **R: Matriz quadrada que serve como o Produto de A e B
 * - unsigned int n: Ordem/tamanho das matrizes A, B e R
 */
void multiplicaMatriz(double **A, double **B, double **R, unsigned int n);

// Função calculaNorma()
/* A função recebe um ponteiro para matriz quadrada de doubles A[] e a
 * ordem/tamanho da matriz. Em seguida, calcula a norma L2 para cada uma das
 * colunas de A[] usando a expressão abaixo:
 *  NormaL2(col, n) = sqrt(sum of i = 0 to n of (A[i][col])^2)
 * 
 * Após o cálculo da norma L2 de cada coluna, a função calcula e retorna a 
 * média simples das normas L2 calculadas.
 * 
 * Parâmetros:
 * - double **A: Matriz quadrada que se deseja calcular a média das normas L2
 * das colunas da matriz
 * - unsigned int n: Ordem/tamanho da matriz A[]
 */
double calculaNorma(double **A, unsigned int n);

#endif