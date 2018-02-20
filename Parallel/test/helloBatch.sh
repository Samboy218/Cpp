#! /bin/bash

#SBATCH --nodes=1 --ntasks=10 -time=10
./hello_parallel.exe 10
