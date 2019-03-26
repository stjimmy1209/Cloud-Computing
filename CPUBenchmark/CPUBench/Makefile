all:CPUBenchSPOut CPUBenchDPOut

CPUBenchSPOut: CPUBenchSP.o
	g++ CPUBenchSP.o -o CPUBenchSPOut -lpthread

CPUBenchSP.o: CPUBenchSP.cpp
	g++ -c CPUBenchSP.cpp

CPUBenchDPOut: CPUBenchDP.o
	g++ CPUBenchDP.o -o CPUBenchDPOut -lpthread

CPUBenchDP.o: CPUBenchDP.cpp
	g++ -c CPUBenchDP.cpp
clean:
	rm -rf *o CPUBenchSPOut CPUBenchDPOut
