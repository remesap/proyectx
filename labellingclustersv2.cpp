#include <iostream>
#include <random>
#include <Eigen/Dense>

//functions:

void set_M(Eigen::MatrixXi & M, double &prob); //fill the matrix
void scan1(Eigen::MatrixXi & M);
void scan2(Eigen::MatrixXi & M);
int main (void)
{
  const int L = 20;
  double p = 0.6;
  Eigen::MatrixXi MATRIX(L,L);

  set_M(MATRIX, p);
  std::cout << MATRIX << std::endl;

  scan1(MATRIX);//first scan
  std::cout << MATRIX << "\v" << std::endl;

  scan2(MATRIX);//second scan
  std::cout << MATRIX << "\v" << std::endl;
  
  
  return 0;
}



void set_M(Eigen::MatrixXi & M, double &prob)
{
  int SEED = 1;
  std::mt19937 gen(SEED);
  std::binomial_distribution<int> dis(1, prob);//(objs 0 or 1,success)

  for (int i = 0; i < M.cols(); ++i)
  {
    for (int j = 0; j < M.cols(); ++j)
      M(i, j) = dis(gen);
  }
}



void scan1(Eigen::MatrixXi & M)
{
  int largest_label = 1;  //label que se le irá asignando a los nuevos clusters

  //un for para la primera fila:
  for (int j = 1; j < M.cols(); ++j)
    {
      int left = M(0, j-1);
      
      if (M(0,j) == 1)
	{
	  if (left == 0)
	    {
	      largest_label = largest_label + 1;
	      M(0, j) = largest_label;
	    }

	  else    //union para la priemra fila
	    {
	      M(0, j) = left;
	    }
	}
      
    }
  
  

  //para el resto de la matriz
  for (int i = 1; i < M.cols(); ++i)
    {
      int up0 =  M(i-1,0); //variable que indica la celda de arriba para los elementos de la primera columna

      if ( M(i,0) ==1) //primero miramos cómo llenar los elementos pertenecientes a la primera columna
	{
	  if ( up0 == 0 )
	    {
	      largest_label = largest_label + 1;
	      M(i, 0) = largest_label;
	    }

	  else    //union para la priemra fila
	    M(i, 0) = up0;
	}
	
      
      for (int j = 1; j < M.cols(); ++j){
	
	int left = M(i, j-1), up = M(i-1,j);
	
	
	if (M(i, j) == 1)
	  { 
	    if ( left == 0 && up == 0)
	      {                              //ni la de la izq. ni la de arriba están ocupadas
		
		largest_label = largest_label + 1;
		M(i, j) = largest_label;
		
	      }
	    
	    else if ( left == 1 && up == 0) //izq. ocupada pero arriba no
	      M(i, j) = left;
	    
	    else if ( left == 0 && up == 1) //izq. vacía y arriba ocupada
	      M(i, j) = up;
	    
	    else
	      {                             //ni izq. ni arriba ocupadas
		
		if ( up > left )   //union
		  up = left;
		
		if ( left > up )
		  left = up;
		
		M(i, j) = left;
	  
	      }
	  
	  }
	
      }
    }
}

  

void scan2(Eigen::MatrixXi & M)
{

  for (int i = 1; i < M.cols(); ++i){
    
    for (int j = 1; j < M.cols(); ++j){

      int left = M(i, j-1), up = M(i-1,j);  //trabajar con las variables locales up y left 
       
      if (M(i, j) != 0 && (left != 0 && up !=0)) {
	
	if ( up > left )
	  {                 //primera unión posible
	    up = left;
	    M(i, j) = left;
	  }
	
	if ( left > up )
	  {                 //segunda unión posible
	    left = up;
	    M(i, j) = up;
	  }
	  
	M(i, j-1) = left; //left y up habían cambiado, pero no los elems de M, aquí se les reasignan valores.
	M(i-1,j) = up;
	
      }
      
    }
  }
}








