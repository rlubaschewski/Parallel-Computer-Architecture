#!/bin/bash

#SBATCH --job-name=ex01
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --time=00:50:00
#SBATCH --output=out.txt

#module purge > /dev/null 2>&1

module load cmake
module load gcc

./a.out 10 10 olumnWise
