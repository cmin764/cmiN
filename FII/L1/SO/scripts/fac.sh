#! /usr/bin/env bash


if [ $# -lt 1 ]
then
	echo "Parametri insuficienti"
	exit
fi

p=1


for x in `seq 1 $1`
do
	#let p=p*x
	let p*=x
done

echo "Factorial: $p"
