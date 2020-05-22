#include "percolant-cluster.h"

void print_txt ( int n, std::vector <double> & V1, std::vector <double> & V2, std::vector <double> & V3 )
{
  std::string fname = "data-" + std::to_string(n+1) + ".txt";  
  std::ofstream fout(fname, std::ofstream::out);
  fout.precision(8); fout.setf(std::ios::fixed);

  for ( int ii = 0; ii < V1.size(); ++ii) {
    fout << V1[ii] << "\t" << V2[ii] << "\t" << V3[ii] << "\n";
  }
  fout.close();
  
}
