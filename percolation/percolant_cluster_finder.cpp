#include "percolant-cluster.h"

int percolant_cluster_finder(Eigen::MatrixXi & M, int size, struct data & dat, int n)
{
  std::vector<int> rowlabels0{};
  std::vector<int> rowlabelsL{};
  std::vector<int> collabels0{};
  std::vector<int> collabelsL{};
  std::vector<int> prows1{};
  std::vector<int> prows2{};
  std::vector<int> pcols1{};
  std::vector<int> pcols2{};
  std::vector<int> percolantes{};

  
  //extracción de los elementos de los extremos
  for (int j = 0; j < M.cols(); ++j)
    {
      //filas 
      if(M(0, j) != 0)
	rowlabels0.push_back(M(0,j));
      
      if(M(size-1, j) != 0)
	rowlabelsL.push_back(M(size-1,j));

      //columnas 
      if(M(j, 0) != 0)
	collabels0.push_back(M(j, 0));
      
      if(M(j, size-1) != 0)
	collabelsL.push_back(M(j, size-1));

    }

  //emparejamiento (no elimina elementos repetidos)
  
  for (int i = 0; i < rowlabels0.size(); ++i)
    for (int j = 0; j < rowlabelsL.size(); ++j)
      {
	if ( rowlabels0[i] == rowlabelsL[j] )
	  prows1.push_back(rowlabels0[i]);
      }

  
  for (int i = 0; i < collabels0.size(); ++i)
    for (int j = 0; j < collabelsL.size(); ++j)
      {
	if ( collabels0[i] == collabelsL[j] )
	  pcols1.push_back(collabels0[i]);
      }
  
  //hay percolantes en las filas?
  
  if ( prows1.size() > 0)
    {
      //eliminación de los elementos repetidos
      
      prows2.push_back( prows1[0] );
      
      for (int j = 1; j < prows1.size(); ++j)
	{
	  if ( prows1[j] != prows2.back())  //comparando con el último elemento del vector 
	    prows2.push_back( prows1[j] );
	}
      
      }
  
  
  if ( pcols1.size() > 0)
    {
      //eliminación de los elementos repetidos
      
      pcols2.push_back( pcols1[0] );
      
      for (int j = 1; j < pcols1.size(); ++j)
	{
	  if ( pcols1[j] != pcols2.back())  //comparando con el último elemento del vector 
	    pcols2.push_back( pcols1[j] );
	}
      
      }
  
  if ( prows2.size() > 0 || pcols2.size() > 0)
    {
      prows2.insert( prows2.end(), pcols2.begin(), pcols2.end() );
      percolantes.push_back( prows2[0] );
      
      for (int i = 1; i < prows2.size(); ++i)
	{
	  if ( prows2[i] != percolantes.back()) 
	    percolantes.push_back( prows2[i] );
	}
    }
    
  std::vector<int> sizep{};
  for (int j = 0; j < percolantes.size(); ++j)
    sizep.push_back(0);  

  int cont = 0;
  for (int i = 0; i < M.cols(); ++i)
    for (int j = 0; j < M.cols(); ++j)
      {
	if (M(i, j) != 0)
	  {
	  for ( int n = 0; n < percolantes.size() ; ++n)
	    if ( M(i, j) == percolantes[n] )
	      {
		sizep[n]++;
	      }
	  }
      }
  
  if(percolantes.size() != 0)
    {
      dat.totalclusters++;
    }

  if (sizep.size() > 0)
    dat.maxsize[n] = sizep[0];
			      
  return 0;
 
} 
