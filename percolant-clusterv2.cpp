#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <vector>

void set_M(Eigen::MatrixXi & M, double &prob, int SEED);
int cluster_finder(Eigen::MatrixXi &  M, int L);
void initialize(int m_labels);
int set_labels(void);
int Find(int x);
int Union(int x, int y);
int percolant_cluster_finder(Eigen::MatrixXi & M, int size, struct data & dat);
int Matrix(int L, double p);

std::vector<int> labels{};
int n_labels = 0;


struct data
{
  int totalclusters; 
}  datos{0};



int main(void)
{
  const int L = 1000;
  double p = 0.59;
  //for(double p = 0.2; p < 1; p = p + 0.2)
  // {
      Matrix(L,p);
      // }
  return 0;
}

int Matrix(int L, double p)
{
  Eigen::MatrixXi MATRIX(L, L);
  for(int u = 0; u < 10; ++u)
    {
      set_M(MATRIX, p, u);
      initialize(L*L/2);
      std::cout << "Número de clusters:" << cluster_finder(MATRIX, L) << std::endl;
      //std::cout << MATRIX << std::endl;
      percolant_cluster_finder(MATRIX,L , datos);     
    }
  std::cout << "total:" << datos.totalclusters << std::endl;
  MATRIX.resize(0,0);
  return 0;
}




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



void initialize(int m_labels)
{
  n_labels = m_labels;
  labels.push_back(0);
  for(int i=1; i < n_labels; ++i)
    {
      labels.push_back(i);
    }
}


int set_labels(void)
{
  labels[0] = labels[0] + 1;   
  labels[labels[0]] = labels[0];
  return labels[0];
}

int Find(int x)
{
  int y = x;
  while (labels[y] != y)
    y = labels[y];
  
  while (labels[x] != x) {
    int z = labels[x];
    labels[x] = y;
    x = z;
  }
  return y; 
}

int Union(int x, int y)
{
  return labels[Find(x)] = Find(y);
}


int cluster_finder(Eigen::MatrixXi & M, int size)
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

int percolant_cluster_finder(Eigen::MatrixXi & M, int size, struct data & dat)
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
      
      //  for (int j = 0; j < prows2.size(); ++j)
      //	std::cout << prows2[j] << " prows2 ";  //*******
      }
  
      //else
      //std::cout << "nada de nada en las filas :'v ";

      //  std::cout << "\n\v";
  //hay percolantes en las columnas?
  
  if ( pcols1.size() > 0)
    {
      //eliminación de los elementos repetidos
      
      pcols2.push_back( pcols1[0] );
      
      for (int j = 1; j < pcols1.size(); ++j)
	{
	  if ( pcols1[j] != pcols2.back())  //comparando con el último elemento del vector 
	    pcols2.push_back( pcols1[j] );
	}
      
      // for (int j = 0; j < pcols2.size(); ++j)
      //std::cout << pcols2[j] << "  pcols2";
      }
  
      //else
      // std::cout << "nada de nada en las columnas :'v ";

  
  if ( prows2.size() > 0 || pcols2.size() > 0)
    {
      //hasta el momento tenemos los vectores prows2 y pcols2, los vamos a fusionar en el vector percolantes:
      prows2.insert( prows2.end(), pcols2.begin(), pcols2.end() );
      percolantes.push_back( prows2[0] );
      
      for (int i = 1; i < prows2.size(); ++i)
	{
	  if ( prows2[i] != percolantes.back()) 
	    percolantes.push_back( prows2[i] );
	}
      
      std::cout << "\n\vlos cluster percolantes son: \n\v";
      
      for (int j = 0; j < percolantes.size(); ++j)
	std::cout << percolantes[j] << "  ";
      
      std::cout << "\n\v";
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


  std::cout << "Tamaño: ";
  
  for (int i = 0; i < sizep.size(); ++i)
    std::cout << sizep[i] << std::endl;
  
  return 0;
 
} 
