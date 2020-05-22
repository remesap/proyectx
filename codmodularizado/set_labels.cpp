#include "percolant-cluster.h"

int set_labels(void)
{
  labels[0] = labels[0] + 1;   
  labels[labels[0]] = labels[0];
  return labels[0];
}
