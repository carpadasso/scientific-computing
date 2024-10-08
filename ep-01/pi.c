#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fenv.h>
#include <float.h>

#define _USE_MATH_DEFINES
#include <math.h>

/* Tipo Double_t:
 * Usado para representar o número Double de duas diferentes
 * maneiras: como ponto flutuante de precisão dupla e inteiro de
 * 64 bits. */
typedef union
{
    int64_t i;
    double d;
} Double_t;

/* >> Calcula o somatório abaixo:
 *     k=0 to n of (2^k * (k!)^2) / (2k + 1)! 
 * - Utiliza o valor da iteração anterior para reduzir FLOPs.
 * - Utiliza o resultado anterior de s(k) para reduzir FLOPs.
 * - Contabiliza o número de FLOPs nos cálculos. */
double somatorioPi(int n, double valor_anterior, double *expressao, long long int *num_flops)
{
   if (n == 0) return 1.0;

   // Calcula o próximo valor de s(k)
   (*expressao) = (n * (*expressao)) / (2*n + 1);

   // Adiciona a contagem de FLOPs
   // Cada iteração do somatório adiciona 3 FLOPs
   // (1 multiplicação, 1 divisão e 1 soma)
   *num_flops += 3;

   return (valor_anterior + (*expressao));
}

/* Calcula a aproximação para PI/2 baseada na tolerância dada. */
void calculaAproximacao(double tolerancia, double *aproximacao, double *erro_aprox, 
                        int *iteracoes, long long int *num_flops)
{
   double expressao = 1.0;

   // Primeira Iteração (k = 0)
   double anterior = somatorioPi(0, 0, &expressao, num_flops);

   // Segunda Iteração (k = 1)
   double atual = somatorioPi(1, anterior, &expressao, num_flops);

   // Erro Inicial
   double erro = fabs(atual - anterior);

   int k = 2;
   while(erro > tolerancia)
   {
      // Anterior recebe s(k-1)
      anterior = atual;

      // Calcula s(k) e joga em Atual
      atual = somatorioPi(k, anterior, &expressao, num_flops);
      
      // Calcula Erro
      erro = fabs(atual - anterior);
      k++;
   }

   *aproximacao = atual;
   *erro_aprox = erro;
   *iteracoes = k;
}

int main(int argc, char** argv)
{
   double tolerancia;
   scanf("%lf", &tolerancia);

   double aproximacao, erro_aprx;
   Double_t aprox_baixo, aprox_cima;

   int iteracoes;
   long long int num_flops;

   // Processamento 1:
   // ARRENDODAMENTO PARA BAIXO
   fesetround(FE_DOWNWARD);
   iteracoes = 0;
   num_flops = 0;
   calculaAproximacao(tolerancia, &aproximacao, &erro_aprx, &iteracoes, &num_flops);
   aprox_baixo.d = aproximacao;
   aprox_baixo.d = 2 * aprox_baixo.d;

   // Processamento 2:
   // ARRENDODAMENTO PARA CIMA
   fesetround(FE_UPWARD);
   iteracoes = 0;
   num_flops = 0;
   calculaAproximacao(tolerancia, &aproximacao, &erro_aprx, &iteracoes, &num_flops);
   aprox_cima.d = aproximacao;
   aprox_cima.d = 2 * aprox_cima.d;

   // Constante PI
   // Utilizada para calcular o Erro Exato
   Double_t pi;
   pi.d = M_PI;

   // Erro Absoluto APROXIMADO
   Double_t erro_aprox;
   erro_aprox.d = erro_aprx;

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