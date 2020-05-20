#include "percolant-cluster.h"

std::vector<int> labels {};
int n_labels = 0;
void initialize(int m_labels)
{
  n_labels = m_labels;
  labels.push_back(0);
  for(int i=1; i < n_labels; ++i)
    {
      labels.push_back(i);
    }
}
