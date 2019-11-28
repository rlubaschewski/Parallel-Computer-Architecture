#!/bin/bash

#SBATCH --job-name=pca_ex03
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=3:00:00
#SBATCH --output=outLast1.txt
#module purge > /dev/null 2>&1

module load cmake
module load gcc

./PCA_03 10000 3500 127.0
