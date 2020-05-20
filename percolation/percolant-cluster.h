#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <vector>

extern std::vector<int> labels;
extern int n_labels;

void set_M(Eigen::MatrixXi & M, double &prob, int SEED);
int cluster_finder(Eigen::MatrixXi &  M, int L);
void initialize(int m_labels);
int set_labels(void);
int Find(int x);
int Union(int x, int y);
int percolant_cluster_finder(Eigen::MatrixXi & M, int size);
