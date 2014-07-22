#! /bin/bash

A=0

for a in $(ls /bin/*)
do
  if [ -d $a ]
  then
    let A+=1
  fi
done

echo $#, $A
