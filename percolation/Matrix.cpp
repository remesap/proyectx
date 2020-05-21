#include "percolant-cluster.h"

int Matrix(int L, double p)
{
  Eigen::MatrixXi MATRIX(L, L);
  for(int u = 0; u < 20; ++u)
    {
      set_M(MATRIX, p, u);
      initialize(L*L/2);
      //std::cout << "Número de clusters:" << cluster_finder(MATRIX, L) << std::endl;
      cluster_finder(MATRIX, L);
      percolant_cluster_finder(MATRIX,L ,datos, u);     
    }
  std::cout << "total:" << datos.totalclusters << "\v\n";

  MATRIX.resize(0,0);
  return 0;
}
