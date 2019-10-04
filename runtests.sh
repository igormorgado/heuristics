#!/bin/bash

START=$(date)
SIZES=( "00010" "00100" "01000" "02000" "05000" "10000" "20000" "30000" )

rm logs/*

echo ex
./maximize data/ex.mtx 0 > logs/ex_maximize.txt
./minimize data/ex.mtx 0 > logs/ex_minimize.txt

echo berlin
./alpha    data/berlin52.mtx 0 > logs/berlin_alpha.txt
./iter     data/berlin52.mtx 0 > logs/berlin_iter.txt
./eps      data/berlin52.mtx 0 > logs/berlin_eps.txt
./minimize data/berlin52.mtx 0 > logs/berlin_minimize.txt
./maximize data/berlin52.mtx 0 > logs/berlin_maximize.txt

for x in ${SIZES[@]}
do
	echo ${x}
	echo alpha
	./alpha    random 0 ${x} > logs/random_${x}_alpha.txt
	echo iter
	./iter     random 0 ${x} > logs/random_${x}_iter.txt
	echo eps
	./eps      random 0 ${x} > logs/random_${x}_eps.txt
	echo maximize
	./maximize random 0 ${x} > logs/random_${x}_maximize.txt
	echo minimize
	./minimize random 0 ${x} > logs/random_${x}_minimize.txt
done
FINISH=$(date)

echo "Start  ${START}"
echo "Finish ${FINISH}"
