// Biblioteca matriz.h

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
double** alocaMatriz(unsigned int n);

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
void liberaMatriz(double **A, unsigned int n);

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
void imprimeMatriz(double **A, unsigned int n);