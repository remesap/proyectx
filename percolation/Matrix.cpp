#include "percolant-cluster.h"

int Matrix(int L, double p, struct data & dat)
{
  Eigen::MatrixXi MATRIX(L, L);
  for(int u = 0; u < 20; ++u)
    {
      set_M(MATRIX, p, u);
      initialize(L*L/2);
      cluster_finder(MATRIX, L);
      percolant_cluster_finder(MATRIX, L, dat, u);     
    }
  MATRIX.resize(0,0);
  return 0;
}
