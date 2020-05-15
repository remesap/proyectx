//visualizando los clusters
#include <iostream>
#include <random>
#include <Eigen/Dense>

void set_M(Eigen::MatrixXf & M, double &prob);
void see_M(Eigen::MatrixXf & M);

int main(void)
{
  const int SIZE = 20;
  const double step = 0.1;
  const int N = 3; //iteraciones
  
  for (int ii = 0; ii*0.1 <= 1.0 ; ++ii){
  Eigen::MatrixXf MATRIX(SIZE, SIZE);
  double p = ii*0.1;
  set_M(MATRIX, p);
  //std::cout << MATRIX << "\v" << std::endl;
  std::cout << "p = " << p << std::endl; 
  see_M(MATRIX);
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

void see_M(Eigen::MatrixXf & M)
{
  int size = M.cols() - 1;
  char Mestrellita[size][size];

  //llenando el char
  for (int n = 0; n < M.cols(); ++n){
    for (int m = 0; m < M.cols(); ++m){
      if ( M(n, m) == 1 ) Mestrellita[n][m] = '*';
      if ( M(n, m) == 0 ) Mestrellita[n][m] = ' ';
    }
  }

  for (int n = 0; n < M.cols(); ++n){
    for (int m = 0; m < M.cols(); ++m){
      printf("%c ", Mestrellita[n][m]);
    }
    std::cout << "\n";
  }

  std::cout << "\v \v" ;
  
  
}
