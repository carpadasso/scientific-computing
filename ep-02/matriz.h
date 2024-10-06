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

// Função fatoracaoLU()
/* 
 * Parâmetros:
 * - double **L: Matriz previamente alocada e processada L
 * - double **U: Matriz previamente alocada e processada U
 * - unsigned int n: Ordem/tamanho das matrizes L e U 
 */
void subtraiMatriz(double **A, double **B, double **R, unsigned int n);

// Função fatoracaoLU()
/* 
 * Parâmetros:
 * - double **L: Matriz previamente alocada e processada L
 * - double **U: Matriz previamente alocada e processada U
 * - unsigned int n: Ordem/tamanho das matrizes L e U 
 */
void multiplicaMatriz(double **A, double **B, double **R, unsigned int n);

// Função fatoracaoLU()
/* 
 * Parâmetros:
 * - double **L: Matriz previamente alocada e processada L
 * - double **U: Matriz previamente alocada e processada U
 * - unsigned int n: Ordem/tamanho das matrizes L e U 
 */
double calculaNorma(double **A, unsigned int n);

#endif