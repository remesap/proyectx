#include "percolant-cluster.h"

int main(void)
{
  const int L = 1000;
  double p = 0.8;
  Eigen::MatrixXi MATRIX(L, L);
  for(int u = 0; u < 20; ++u)
    {
      set_M(MATRIX, p, u);
      initialize(L*L/2);
      std::cout << "Número de clusters:" << cluster_finder(MATRIX, L) << std::endl;
      percolant_cluster_finder(MATRIX, L);
    }

  MATRIX.resize(0,0);
  
  return 0;
}
