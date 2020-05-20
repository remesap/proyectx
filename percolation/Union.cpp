#include "percolant-cluster.h"

int Union(int x, int y)
{
  return labels[Find(x)] = Find(y);
}
