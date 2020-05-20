#include "percolant-cluster.h"

void set_M(Eigen::MatrixXi & M, double &prob, int SEED)
{
  std::mt19937 gen(SEED);
  std::binomial_distribution<int> dis(1, prob);//(objs 0 or 1,success)
  
  for (int i = 0; i < M.cols(); ++i)
    {
      for (int j = 0; j < M.cols(); ++j)
	M(i, j) = dis(gen);
    }
}
