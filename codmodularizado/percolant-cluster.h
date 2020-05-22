 #include <iostream>
#include <random>
#include <Eigen/Dense>
#include <vector>
#include <fstream>

extern std::vector<int> labels;
extern int n_labels;


struct data
{
  int totalclusters;
  int maxsize[20];
};


void set_M(Eigen::MatrixXi & M, double &prob, int SEED);
int cluster_finder(Eigen::MatrixXi &  M, int L);
void initialize(int m_labels);
int set_labels(void);
int Find(int x);
int Union(int x, int y);
int percolant_cluster_finder(Eigen::MatrixXi & M, int size, struct data & dat, int n);
int Matrix(int L, double p, struct data & dat);
double Probabilidad(int L, double p, struct data & dat);
void print_txt ( int n, std::vector <double> & V1, std::vector <double> & V2, std::vector <double> & V3 );
