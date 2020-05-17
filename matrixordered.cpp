#include <iostream>
#include <random>
#include <Eigen/Dense>

//Funciones

void set_M(Eigen::MatrixXf & M, double &prob); //Llena la matriz
//double probabilidad(int & l); //Varía la probabilidad con la que se llena la matriz
void cp(Eigen::MatrixXf & M); //Encuentra clusters percolantes

int main(void)
{
  const double step = 0.1;
  const int N = 3; //iteraciones
  const int L = 4;
  double p = 0.7;
  //probabilidad(L);
  Eigen::MatrixXf MATRIX(L, L);
  set_M(MATRIX, p);
  cp(MATRIX);
  std::cout << MATRIX << std::endl;
  return 0;
}


void set_M(Eigen::MatrixXf & M, double &prob)
{
  int SEED = 1;
  std::mt19937 gen(SEED);
  std::binomial_distribution<int> dis(1, prob);//(objs 0 or 1,success)

  for (int n = 0; n < M.cols(); ++n)
    {
      for (int m = 0; m < M.cols(); ++m)
      M(n, m) = dis(gen);
    }
}
void cp(Eigen::MatrixXf & M)
{

}
