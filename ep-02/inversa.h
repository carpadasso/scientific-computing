// Biblioteca inversa.h
// Conteúdo: 02 funções

// Função fatoracaoLU()
/* Início: Recebe duas matrizes quadradas pré-processadas, L e U, e realiza
 * o método de fatoração LU de uma matriz A, ou seja, a eliminação gaussiana em
 * cima de A. Inicialmente a diagonal principal de L deve ser 1 e U = A.
 * 
 * Final: L contém a matriz diagonal inferior da fatoração, armazenando
 * os coeficientes da eliminação gaussiana, e U contém a matriz diagonal
 * superior da fatoração, armazenando a matriz resultante da eliminação
 * gaussiana.
 * 
 * Parâmetros:
 * - double **L: Matriz previamente alocada e processada L
 * - double **U: Matriz previamente alocada e processada U
 * - unsigned int n: Ordem/tamanho das matrizes L e U 
 */
void fatoracaoLU(double **L, double **U, unsigned int n);

// Função calculaInversa()
/* Início: Recebe duas matrizes quadradas resultantes da fatoração LU, as 
 * matrizes L e U, além de uma terceira matriz quadrada Inv, que armazenará
 * os valores da inversa de outra matriz A = L x U. A função então processa
 * as matrizes da seguinte forma:
 * 
 * Final: Inv contém os valores de A^-1, a inversa de A.
 * 
 * Parâmetros:
 * - double **L: Matriz resultante da fatoração LU, L
 * - double **U: Matriz resultante da fatoração LU, U
 * - double **Inv: Matriz previamente alocada que armazenará os valores da
 * matriz inversa de A
 * - unsigned int n: Ordem/tamanho das matrizes L, U e Inv
 */
void calculaInversa(double **L, double **U, double **Inv, unsigned int n);