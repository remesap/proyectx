#include <iostream>
#include <random>

int main(void)
{
  std::cout.precision(5);
  std::cout.setf(std::ios::fixed);
  const int N = 204446; //numero de muestras
  const int SEED = 1;
  const double XMIN = 1, XMAX = 50;

  std::mt19937 gen(SEED);
  std::binomial_distribution<int> dis(50, 0.95);//(objs,success)

  int counter = 0;
  for (int ii = 1; ii <= N; ii++)
    {
      int n = dis(gen);
      if ( n == 48)
	counter += 1;
      
    }
  
  std::cout << 1.0*counter/N << "\n";
  
  return 0;
}
