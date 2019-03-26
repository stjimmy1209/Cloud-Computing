all:spout dpout

spout: matrix_sp.o
	g++ matrix_sp.o -o spout -pthread

matrix_sp.o: matrix_sp.cpp
	g++ -c matrix_sp.cpp

dpout: matrix_dp.o
	g++ matrix_dp.o -o dpout -pthread

matrix_dp.o: matrix_dp.cpp
	g++ -c matrix_dp.cpp
clean:
	rm -rf *o spout dpout
