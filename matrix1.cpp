#include <iostream>
#include <random>
#include <Eigen/Dense>

void set_M(Eigen::MatrixXf & M, double &prob);


int main(void)
{
  const int SIZE = 10;
  const double step = 0.1;
  const int N = 3; //iteraciones
  
  for (int ii = 0; ii*0.1 <= 1.0 ; ++ii){
  Eigen::MatrixXf MATRIX(SIZE, SIZE);
  double p = ii*0.1;
  set_M(MATRIX, p);
  std::cout << MATRIX << "\v" << std::endl;
  }
  return 0;
}

void set_M(Eigen::MatrixXf & M, double &prob)
{
  int SEED = 1;
  std::mt19937 gen(SEED);
  std::binomial_distribution<int> dis(1, prob);//(objs 0 or 1,success)

  for (int n = 0; n < M.cols(); ++n){
    for (int m = 0; m < M.cols(); ++m)
      M(n, m) = dis(gen);
  }
}

