CXX = g++
CXXFLAGS = -O3 -std=c++11 -fsanitize=undefined -fsanitize=address -g

all : main_percolant-cluster.x run1 plot

main_percolant-cluster.x : set_M.o cluster_finder.o initialize.o set_labels.o Find.o Union.o percolant_cluster_finder.o main_percolant-cluster.o Matrix.o Probabilidad.o print_txt.o
	$(CXX)  $(CXXFLAGS) $^ -o $@

%.o : %.cpp   #de todos los archivos .cpp se crean los objetos .o  $< indica que hay una sola dependencia
	g++ -c $< 

run1 : main_percolant-cluster.x
	time ./$<

plot :
	gnuplot plot.gp

clean :
	rm *~ *# *.o *.x *.txt *.pdf
