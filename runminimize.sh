#!/bin/bash

SIZES=( "00010" "00100" "01000" "02000" "05000" "10000" )
#SIZES=( "10" "100" )

echo ex
./minimize data/ex.mtx 0 > logs/ex_minimize.txt
echo berlin
./minimize data/berlin52.mtx 0 > logs/berlin_minimize.txt

for x in ${SIZES[@]}
do
	echo ${x}
	./minimize random 0 ${x} > logs/random_${x}_minimize.txt
done

