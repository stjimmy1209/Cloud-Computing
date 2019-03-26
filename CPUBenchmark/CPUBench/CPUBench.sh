#!/bin/bash

make
echo "Benchmarking Single Precision..."
./CPUBenchSPOut $1
echo "Benchmarking Double Precision..."
./CPUBenchDPOut $1
make clean
