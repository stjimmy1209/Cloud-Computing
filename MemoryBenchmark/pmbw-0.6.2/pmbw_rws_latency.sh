#!/bin/bash

separate() 
{
for i in 1 2 3
do    
  echo "***************************************************************************************"
done
}

echo "Benchmarking Scan R/W for 1 thread and 1024 B block size:"
sudo nice -n -2 ./pmbw -P 1 -p 1 -f Scan -M 1073741824 -S 1024 -s 1024
separate

echo "Benchmarking Scan R/W for 2 thread and 1024 B block size:"
sudo nice -n -2 ./pmbw -P 2 -p 2 -f Scan -M 1073741824 -S 1024 -s 1024
separate

echo "Benchmarking Scan R/W for 4 thread and 1024 B block size:"
sudo nice -n -2 ./pmbw -P 4 -p 4 -f Scan -M 1073741824 -S 1024 -s 1024
separate

echo "Benchmarking Scan R/W for 8 thread and 1024 B block size:"
sudo nice -n -2 ./pmbw -P 8 -p 8 -f Scan -M 1073741824 -S 1024 -s 1024
separate
