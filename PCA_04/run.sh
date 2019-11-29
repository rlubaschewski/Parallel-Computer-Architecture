#!/bin/bash

#SBATCH --job-name=ex03
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=02:00:00
#SBATCH --output=out.txt

#module purge > /dev/null 2>&1

module load cmake
module load gcc

# comment in if you also want to compile
# cmake .
# make

./PCA_04.out 100 32