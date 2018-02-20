#! /bin/bash

for ((j=1; j < 10; j++))
do
    for ((i=0; i < 10; i++))
    do
        ./testpar.exe ${j}
    done
    mv timing.txt timing${j}.txt
done

