#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fenv.h>
#include <float.h>

#define _USE_MATH_DEFINES
#include <math.h>

/* Tipo Double_t:
 * Usado para representar o número Double de diferentes
 * maneiras, como inteiro de 64 bits e as partes do ponto
 * flutuante. */
typedef union
{
    int64_t i;
    double d;
    struct
    {   // Bitfields for exploration (64 bits = sign|exponent|mantissa)
        uint64_t mantissa : 52; // primeiros 52 bits (da direita para a esquerda)
        uint64_t exponent : 11; // próximos 11 bits
        uint64_t sign : 1;      // proximo bit (ou seja, o bit mais a esquerda)
    } parts;
} Double_t;

/* Retorna n! */
unsigned int fatorial(int n)
{
   if (n == 0 || n == 1) return 1;
   return n * fatorial(n-1);
}

/* Retorna x^e */
unsigned int potencia(int x, int e)
{
   if (e == 0) return 1;
   return x * potencia(x, e-1);
}

/* Calcula o somatório abaixo:
 * k=0 to n of (2^k * (k!)^2) / (2k + 1)! */
double somatorioPi(int n)
{
   unsigned int pot, fat, fat_impar;
   double resultado = 0;

   if (n == 0) return 1.0;

   for (int k = 0; k < n; ++k)
   {
      pot = potencia(2, k);
      fat = fatorial(k);
      fat_impar = fatorial(2*k + 1);
      resultado += fat * fat * (pot / (1.0 * fat_impar));
   }

   return resultado;
}

int AlmostEqualRelative(Double_t A, Double_t B)
{
    // Calculate the difference.
    Double_t diff, largest, relEpsilon;
    diff.d = fabs(A.d - B.d);
    A.d = fabs(A.d);
    B.d = fabs(B.d);
    // Find the largest
    largest.d = (B.d > A.d) ? B.d : A.d;
    relEpsilon.d = largest.d * DBL_EPSILON;
    
    if (diff.d <= relEpsilon.d)
        return 1;
    return 0;
}

/* Gera a aproximacao para o valor de pi */
void calculaAproximacao(double tolerancia, Double_t *aproximacao, Double_t *erro_aprox, 
                        int *iteracoes, long long int *num_flops)
{
   Double_t e, tol;
   double atual, anterior;
   anterior = somatorioPi(0);
   atual = somatorioPi(1);
   
   tol.d = tolerancia;
   e.d = fabs(atual - anterior);
   int k = 2;
   while(!AlmostEqualRelative(e, tol))
   {
      anterior = atual;
      atual = somatorioPi(k);
      e.d = fabs(atual - anterior);
      k++;
   }

   aproximacao->d = atual;
   erro_aprox->d = e.d;
   *iteracoes = k;
   *num_flops = 4*(k-1) + 1;
}

int main(int argc, char** argv)
{
   double tolerancia;
   scanf("%lf", &tolerancia);

   Double_t aproximacao, erro_aprox;
   Double_t aprox_baixo, aprox_cima;
   int iteracoes;
   long long int num_flops;

   // Processamento 1:
   // ARRENDODAMENTO PARA BAIXO
   fesetround(FE_DOWNWARD);
   calculaAproximacao(tolerancia, &aproximacao, &erro_aprox, &iteracoes, &num_flops);
   aprox_baixo = aproximacao;

   // Processamento 2:
   // ARRENDODAMENTO PARA CIMA
   fesetround(FE_UPWARD);
   calculaAproximacao(tolerancia, &aproximacao, &erro_aprox, &iteracoes, &num_flops);
   aprox_cima = aproximacao;

   Double_t pi;
   pi.d = M_PI;

   Double_t erro_abs;
   erro_abs.d = aprox_cima.d - pi.d;
   /* Modelo de Impressão:
    * <NÚMERO DE ITERAÇÕES>
    * <ERRO ABSOLUTO APROXIMADO> <ERRO ABSOLUTO APROXIMADO EM HEX>
    * <ERRO ABSOLUTO EXATO>      <ERRO ABSOLUTO EXATO EM HEX>
    * <APROXIMAÇÃO PARA BAIXO>   <APROXIMAÇÃO PARA BAIXO EM HEX>
    * <APROXIMAÇÃO PARA CIMA>    <APROXIMAÇÃO PARA CIMA EM HEX>
    * <DIFERENÇA DE ULPS DAS APROXIMAÇÕES> 
    * <NUMERO DE FLOPS> */
   printf("n = %d\n", iteracoes);
   printf("EA aprox = %.15e (%llX)\n", erro_aprox.d, erro_aprox.i);
   printf("EA exato = %.15e (%llX)\n", erro_abs.d, erro_abs.i);
   printf("PI'  = %.15e (%llX)\n", aprox_baixo.d, aprox_baixo.i);
   printf("PI'' = %.15e (%llX)\n", aprox_cima.d, aprox_cima.i);
   printf("ULPs = %d\n", abs(aprox_baixo.i - aprox_cima.i - 1));
   printf("FLOPs = %lld\n", num_flops);

   return 0;
}