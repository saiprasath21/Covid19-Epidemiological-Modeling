# include<stdio.h>
# include <stdlib.h>
# include<math.h>
# include<time.h>


double exponential(double lambda)
{
  // generating a random number from a unifrom random number generator
  double x = rand()/(double)RAND_MAX;
  //printf("Random value generated is: %lf", x);
  return -1/lambda * log(x);
}

double cumu_weibull(double lambda, double k, double t)
{
  double x = pow(t/lambda, k);
  return 1 - exp(-x);
}

double poisson(double x)
{
  int    poi_value;             // Computed Poisson value to be returned
  double t_sum;                 // Time sum value

  // Loop to generate Poisson values using exponential distribution
  poi_value = 0.0;
  t_sum = 0.0;
  while(1)
  {
    t_sum = t_sum + exponential(x);
    if (t_sum >= 1.0) break;
    poi_value++;
  }

  return(poi_value);
}

double gamma_sampling(double a, double b)
{
  // code not available in the internet
  return 0;
}

int main()
{
double sum = 0;
int a[10] = {0};
for(int i=0; i<1000 ; i++){
printf("Print: %lf \n", poisson(2.5));
a[(int)poisson(2.5)] += 1;
}
for(int i=0;i<10;i++)
{
printf("%0.3f", (double)a[i]/1000);
for(int j=0;j<((double)a[i]/1000)*100;j++)printf(".");
printf("\n");
}
printf("Sum = %lf \n", sum);
return 0;
}
