#!/bin/bash

separate() 
{
for i in 1 2 3
do    
  echo "****************************************"
done
}

echo "Benchmarking Scan R/W for 1 thread and 1 KB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 1 -p 1 -f Scan -M 4294967296 -S 1024 -s 1024 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 1 thread and 1 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 1 -p 1 -f Scan -M 4294967296 -S 1048576 -s 1048576 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 1 thread and 10 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 1 -p 1 -f Scan -M 4294967296 -S 10485760 -s 10485760 >> rws_pmbw.txt
separate >> rws_pmbw.txt 

echo "Benchmarking Scan R/W for 2 thread and 1 KB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 2 -p 2 -f Scan -M 4294967296 -S 1024 -s 1024 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 2 thread and 1 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 2 -p 2 -f Scan -M 4294967296 -S 1048576 -s 1048576 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 2 thread and 10 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 2 -p 2 -f Scan -M 4294967296 -S 10485760 -s 10485760 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 4 thread and 1 KB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 4 -p 4 -f Scan -M 4294967296 -S 1024 -s 1024 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 4 thread and 1 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 4 -p 4 -f Scan -M 4294967296 -S 1048576 -s 1048576 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 4 thread and 10 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 4 -p 4 -f Scan -M 4294967296 -S 10485760 -s 10485760 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 8 thread and 1 KB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 8 -p 8 -f Scan -M 4294967296 -S 1024 -s 1024 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 8 thread and 1 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 8 -p 8 -f Scan -M 4294967296 -S 1048576 -s 1048576 >> rws_pmbw.txt
separate >> rws_pmbw.txt

echo "Benchmarking Scan R/W for 8 thread and 10 MB block size:" >> rws_pmbw.txt
sudo nice -n -2 ./pmbw -P 8 -p 8 -f Scan -M 4294967296 -S 10485760 -s 10485760 >> rws_pmbw.txt
separate >> rws_pmbw.txt

