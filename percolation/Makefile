all : main_percolant-cluster.x

main_percolant-cluster.x : set_M.o cluster_finder.o initialize.o set_labels.o Find.o Union.o percolant_cluster_finder.o main_percolant-cluster.o datos.o Matrix.cpp 

	g++ -std=c++17 $^ -o $@

%.o : %.cpp   #de todos los archivos .cpp se crean los objetos .o 
	g++ -c $< # "$<" indica que hay una única dependencia

clean :
	rm *~ *#
