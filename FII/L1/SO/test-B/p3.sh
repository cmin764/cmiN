#!/bin/bash

#######################################################################################################
# Enunt a treia problema:
#
# Sa se scrie un script bash care sa calculeze recursiv urmatoarea formula
# F(n) = n +(n-1)*2 + (n-2)*3 + ..... 1*n
#
#
#######################################################################################################


if [ $# -ne 1 ]
then
    echo "Usage: "$0" NUMBER"
    exit 1
fi

result=0
factor=1
nr=$1


function func()
{
    if [ $1 -eq 0 ]
    then
        return
    fi

    local var
    let var=$1*$factor
    let result+=var

    let factor+=1
    func $(expr $1 - 1)
}


func $nr
echo $result

exit 0
