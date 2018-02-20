#!/bin/bash
#SBATCH --nodes=1 --ntasks=28 --time 600
./mat_mul.exe 10000 28
