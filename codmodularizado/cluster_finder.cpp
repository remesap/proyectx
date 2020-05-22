#include "percolant-cluster.h"

int cluster_finder(Eigen::MatrixXi & M, int L)
{
  for (int i = 0; i < M.cols(); ++i)
    {
      for (int j = 0; j < M.cols(); ++j)
	{
	  if(M(i,j) !=0){
	    int up = (i==0 ? 0 : M(i-1,j));   
	    int left = (j==0 ? 0 :M(i,j-1));
	    
	    switch (!!up + !!left) {
	      
	    case 0:
	      M(i,j) = set_labels();    
	      break;
	      
	    case 1:                              
	      M(i,j) = std::max(up,left);       
	      break;
	      
	    case 2:                              
	      M(i,j) = Union(up, left);
	      break;
	    }
	  }
	}
    }
  
  std::vector<int> newlabels{};
  for(int i=0; i < n_labels; ++i)
    {
      newlabels.push_back(0);
    }
  
  for (int i = 0; i < M.cols(); ++i)
    {
      for (int j = 0; j < M.cols(); ++j)
	{
	  if(M(i,j) != 0){
	    int x = Find(M(i,j));
	    if(newlabels[x] == 0){
	      newlabels[0] = newlabels[0] + 1;
	      newlabels[x] = newlabels[0];
	    }
	    
	    M(i,j) = newlabels[x];
	  }
	}
    }
  int clusters = newlabels[0];
  newlabels.clear();
  newlabels.shrink_to_fit();
  labels.clear();
  labels.shrink_to_fit();
  return clusters;
}
