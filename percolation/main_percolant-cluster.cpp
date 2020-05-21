#include "percolant-cluster.h"

data datos { 0,
	     {0},
};

int main(void)
{
  int SIZES[5] = {32,64,128,256,512};
  for(int v = 0; v < 5; v++)
      {
	int L = SIZES[v];
	std::cout << L << "\n\v";
	for(double p = 0.57; p < 0.65; p = p + 0.00125)
	  {
	    Matrix(L, p, datos);
	    std::cout << p << "\t";
	    std::cout << Probabilidad(L, p, datos) << "\t";
	    int* i1;
	    i1 = std::max_element(datos.maxsize + 0, datos.maxsize + 19);
	    std::cout << (*i1*(1.0)/(L*L))*100 << std::endl;
	    datos.totalclusters = 0;
	    for(int u = 0; u < 20; u++){
	      datos.maxsize[u] = 0;}	    
	 }
      }
  return 0;
}
