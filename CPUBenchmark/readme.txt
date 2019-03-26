TODO: write readme

1. CPUBench:

Just run script CPUBench.sh with number of threads you want to use.
For example:
sh CPUBench.sh 4

2. MatrixBench:

Run script matrix_sp.sh / matrix_dp.sh for single and double precision with number of threads you want to run.
For example:

sh matrix_sp.sh 2
sh matrix_dp.sh 1

3. HPLBench:

options file has been set with libblas3 library.
run sudo apt-install libblas3
HPL.data file has been tuned for the specific requirement for this benchmark.
run shpl/xhpl with:

mpirun -np 4 shpl /
mpirun -np 4 xhpl

Since I am extremely short of time for this homework, I did not tested for very large size of matrix for part 2. And the result table is yet to finish.
