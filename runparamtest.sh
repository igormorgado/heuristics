#!/bin/bash

SIZES=( "0010" "0100" "1000" "2500" "5000" )

echo berlin
./alpha data/berlin52.mtx 0 > logs/berlin_alpha.txt
./iter data/berlin52.mtx 0 >  logs/berlin_iter.txt
./eps data/berlin52.mtx 0 >   logs/berlin_eps.txt

for x in ${SIZES[@]}
do
	echo ${x}
	echo alpha
	./alpha random 0 ${x} > logs/random_${x}_alpha.txt
	echo iter
	./iter random 0 ${x}  > logs/random_${x}_iter.txt
	echo eps
	./eps random 0 ${x}   > logs/random_${x}_eps.txt
done

