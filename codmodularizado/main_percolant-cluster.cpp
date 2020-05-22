#include "percolant-cluster.h"

data datos { 0, //totalclusters
	     {0}, //maxsize
};

  
int main(void)
{
  int SIZES[5] = {32,64,128,256,512};
  for(int v = 0; v < 5; v++)
    {
      int L = SIZES[v];
      //std::cout << L << "\n\v";
      
      std::vector<double> probs{};
      std::vector<double> PROBS{};
      std::vector<double> maxsz{};
      
      for(double p = 0.57; p < 0.65; p = p + 0.00125)
	{
	  
	  Matrix(L, p, datos);  //genera 20 matrices y saca los datos
	  probs.push_back(p);
	  //std::cout << p << "\t";
	  //std::cout << Probabilidad(L, p, datos) << "\t";
	  PROBS.push_back( Probabilidad(L, p, datos) );
	  int* i1;
	  i1 = std::max_element(datos.maxsize + 0, datos.maxsize + 19);
	  //std::cout << (*i1*(1.0)/(L*L))*100 << std::endl;
	  maxsz.push_back( (*i1*(1.0)/(L*L))*100 );
          datos.totalclusters = 0;
      
	  for(int u = 0; u < 20; u++){
	    datos.maxsize[u] = 0;}	    
    }

  print_txt( v, probs, PROBS, maxsz );
  
}

    return 0;
}

