all:rws rwr

rws: rws_memo_multithread.o
	g++ rws_memo_multithread.o -o rws -pthread -std=c++11

rws_memo_multithread.o: rws_memo_multithread.cpp
	g++ -c rws_memo_multithread.cpp -std=c++11

rwr: rwr_memo_multithread.o
	g++ rwr_memo_multithread.o -o rwr -pthread -std=c++11

rwr_memo_multithread.o: rwr_memo_multithread.cpp
	g++ -c rwr_memo_multithread.cpp -std=c++11
clean:
	rm -rf *o rws rwr