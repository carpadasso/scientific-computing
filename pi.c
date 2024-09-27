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
} Double_t;

/* Calcula n! de forma iterativa. */
double fatorial(int n)
{
   double produto = 1.0;
   long int valor = 1;

   if (n == 0) return produto;

   for (int i = 1; i <= n; ++i)
   {
      produto = produto * valor;
      valor = valor + 1;
   }

   return produto;
}

/* Calcula x^e de forma iterativa. */
long int potencia(double x, int e)
{
   long int produto = 1;

   if (e == 0) return produto;

   for (int i = 1; i <= e; ++i)
      produto = produto * x;

   return produto;
}

/* >> Calcula o somatório abaixo:
 *     k=0 to n of (2^k * (k!)^2) / (2k + 1)! 
 * - Utiliza o valor da iteração anterior para reduzir FLOPs.
 * - Contabiliza o número de FLOPs nos cálculos. */
double somatorioPi(int n, double valor_anterior, long long int *num_flops)
{
   double valor = 0;

   if (n == 0) return 1.0;

   valor = valor_anterior + (potencia(2, n) * ((fatorial(n) * fatorial(n)) / fatorial(2*n + 1)));
   *num_flops += 4*n + 5;

   return valor;
}

/* Calcula a aproximação para PI/2 baseada na tolerância dada. */
void calculaAproximacao(double tolerancia, Double_t *aproximacao, Double_t *erro_aprox, 
                        int *iteracoes, long long int *num_flops)
{
   double anterior = somatorioPi(0, 0, num_flops);
   double atual = somatorioPi(1, anterior, num_flops);

   double erro = fabs(atual - anterior);

   int k = 2;
   (*num_flops)++;
   while(erro > tolerancia)
   {
      anterior = atual;
      atual = somatorioPi(k, anterior, num_flops);
      erro = fabs(atual - anterior);
      k++;
      (*num_flops) += 1;
   }

   aproximacao->d = atual;
   erro_aprox->d = erro;
   *iteracoes = k;
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
   iteracoes = 0;
   num_flops = 0;
   calculaAproximacao(tolerancia, &aproximacao, &erro_aprox, &iteracoes, &num_flops);
   aprox_baixo = aproximacao;
   aprox_baixo.d = 2 * aprox_baixo.d;

   // Processamento 2:
   // ARRENDODAMENTO PARA CIMA
   fesetround(FE_UPWARD);
   iteracoes = 0;
   num_flops = 0;
   calculaAproximacao(tolerancia, &aproximacao, &erro_aprox, &iteracoes, &num_flops);
   aprox_cima = aproximacao;
   aprox_cima.d = 2 * aprox_cima.d;

   // Constante PI
   // Utilizada para calcular o Erro Exato
   Double_t pi;
   pi.d = M_PI;

   // Erro Absoluto EXATO
   Double_t erro_exato;
   erro_exato.d = fabs(aprox_cima.d - pi.d);

   /* Modelo de Impressão:
    * <NÚMERO DE ITERAÇÕES>
    * <ERRO ABSOLUTO APROXIMADO> <ERRO ABSOLUTO APROXIMADO EM HEX>
    * <ERRO ABSOLUTO EXATO>      <ERRO ABSOLUTO EXATO EM HEX>
    * <APROXIMAÇÃO PARA BAIXO>   <APROXIMAÇÃO PARA BAIXO EM HEX>
    * <APROXIMAÇÃO PARA CIMA>    <APROXIMAÇÃO PARA CIMA EM HEX>
    * <DIFERENÇA DE ULPS DAS APROXIMAÇÕES> 
    * <NUMERO DE FLOPS> */
   printf("%d\n", iteracoes);
   printf("%.15e %llX\n", erro_aprox.d, erro_aprox.i);
   printf("%.15e %llX\n", erro_exato.d, erro_exato.i);
   printf("%.15e %llX\n", aprox_baixo.d, aprox_baixo.i);
   printf("%.15e %llX\n", aprox_cima.d, aprox_cima.i);
   printf("%d\n", abs(aprox_baixo.i - aprox_cima.i - 1));
   printf("%lld\n", num_flops);

   return 0;
}