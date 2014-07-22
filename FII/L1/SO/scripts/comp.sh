#! /usr/bin/env bash


function compile()
{
    out=$(basename $1 .cpp)
    g++ -Wall -o "$path/$out" $1
}


if [ $# -ne 1 ]
then
    echo -n "Path: "
    read path
else
    path=$1
fi


for fname in $(find $path -maxdepth 1 -name "*.cpp")
do
    compile $fname
done
