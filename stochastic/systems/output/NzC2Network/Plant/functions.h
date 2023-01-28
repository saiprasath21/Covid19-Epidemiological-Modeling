# include<stdio.h>
# include<stdlib.h>
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
  //printf("Weibull value: %lf \n", 1-exp(-x));
  return 1 - exp(-x);
}

double poisson(double x)
{
  double    poi_value;             // Computed Poisson value to be returned
  double t_sum;                 // Time sum value

  // Loop to generate Poisson values using exponential distribution
  poi_value = 0.0;
  t_sum = 0.0;
  while(1)
  {
    t_sum = t_sum + exponential(x);
    if (t_sum >= 1.0) break;
    poi_value += 1.0;
  }

  return(poi_value);
}

double gamma_sampling(double a, double b)
{
  // valid only for integer "a" --> has to be modified later for including other values for this parameter
  // here b is theta 
  double sum=0;
  for(int i=0; i< (int)a; i++)
  {
    sum += exponential(1/b);
  }
  
  return sum;
}

double subclinical_calc(double prob)
{
  //printf("Finding subclinical \n");
  double x = rand()/(double)RAND_MAX;
  if(x<prob)return 1.0;
  else return 0.0;

}


double hosp_calc(double prob)
{
  double x = rand()/(double)RAND_MAX;
  if(x<0.0525)return 1.0;
  else return 0.0;

}

double isolated_calc(double t, double t_iso, double c_iso)
{

  if(t - t_iso >= 0) return c_iso;
  else return 1.0;

}

double lambda_calc(double Ro, double Ni, double population, double t, double t_iso, double t_exp, double c_iso, double g_shape, double g_scale, double ce)
{
  //printf("Computing Lambda: \n");
 // printf("%lf %lf %lf %lf %lf %lf \n", Ro, (1-(Ni/population)), ce, isolated_calc(t, t_iso, c_iso), (cumu_weibull(g_shape, g_scale, t-t_exp+1) - cumu_weibull(g_shape, g_scale, t-t_exp)), ce);
  return Ro * (1-(Ni/population)) * Ro/2.5 * isolated_calc(t, t_iso, c_iso) * (cumu_weibull(g_shape, g_scale, t-t_exp+1) - cumu_weibull(g_shape, g_scale, t-t_exp));
  //return (1-(Ni/population)) * Ro/10.0 * isolated_calc(t, t_iso, c_iso);

}


