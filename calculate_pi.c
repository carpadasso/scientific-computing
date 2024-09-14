#include <stdio.h>
#include <fenv.h>

#define _USE_MATH_DEFINES
#include <math.h>

int fatorial(int n)
{
   if (n == 0 || n == 1) return 1;
   return n * fatorial(n-1);
}

int potencia(int x, int e)
{
   if (e == 0) return 1;
   return x * potencia(x, e-1);
}

double somatorioPi(int k)
{
   if (k == 0) return 1.0;

   double exprSomatorio = (potencia(2, k) * (fatorial(k)*fatorial(k)) / 1.0 * fatorial(2*k + 1));
   return exprSomatorio + somatorioPi(k-1);
}

int main(int argc, char** argv)
{
   fesetround(FE_DOWNWARD);

   double pi_atual, pi_anterior;
   double tolerancia;
   int k = 1;

   pi_atual = somatorioPi(0);
   do
   {
      pi_anterior = pi_atual;
      pi_atual = somatorioPi(k);
      tolerancia = pi_atual - pi_anterior;
      k += 1;
   }
   while (tolerancia > 1e-15);

   pi_atual = 2*pi_atual;
   printf("VALOR DA CONSTANTE: %.15e %x\n", M_PI, M_PI);
   printf("\nVALOR ENCONTRADO: %.15e %x\n", pi_atual, pi_atual);
   printf("\nNUMERO DE ITERACOES: %d\n", k);
}