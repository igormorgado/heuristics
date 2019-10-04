#!/bin/bash

SIZES=( "00010" "00100" "01000" "02000" "05000" "10000" )

echo ex
./maximize data/ex.mtx 0 > logs/ex_maximize.txt
echo berlin
./maximize data/berlin52.mtx 0 > logs/berlin_maximize.txt

for x in ${SIZES[@]}
do
	echo ${x}
	./maximize random 0 ${x} > logs/random_${x}_maximize.txt
done

