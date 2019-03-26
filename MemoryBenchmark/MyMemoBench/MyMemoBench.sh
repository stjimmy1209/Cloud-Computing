#!/bin/bash

make all
echo "Benchmarking..."
./rws 1 1024 >> rws.txt
./rws 1 1048576 >> rws.txt
./rws 1 10485760 >> rws.txt

./rws 2 1024 >> rws.txt
./rws 2 1048576 >> rws.txt
./rws 2 10485760 >> rws.txt

./rws 4 1024 >> rws.txt
./rws 4 1048576 >> rws.txt
./rws 4 10485760 >> rws.txt

./rws 8 1024 >> rws.txt
./rws 8 1048576 >> rws.txt
./rws 8 10485760 >> rws.txt

./rwr 1 1024 >> rwr.txt
./rwr 1 1048576 >> rwr.txt
./rwr 1 10485760 >> rwr.txt

./rwr 2 1024 >> rwr.txt
./rwr 2 1048576 >> rwr.txt
./rwr 2 10485760 >> rwr.txt

./rwr 4 1024 >> rwr.txt
./rwr 4 1048576 >> rwr.txt
./rwr 4 10485760 >> rwr.txt

./rwr 8 1024 >> rwr.txt
./rwr 8 1048576 >> rwr.txt
./rwr 8 10485760 >> rwr.txt
