#! /bin/bash
#SBATCH --nodes=1 --ntasks=1 --time 600
#srun mat_mul.exe 1000 1


for i in $( echo '1 2 4 8 16 28' ); do
    for j in $(echo '1000 2000 5000 7000 10000' ); do
        printf "#!/bin/bash\n#SBATCH --nodes=1 --ntasks=$i --time 600\n./mat_mul.exe $j $i\n" > currBatch.sh
        sbatch currBatch.sh
    done
done
