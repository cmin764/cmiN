#! /usr/bin/env bash


function factorial() 
{
    if [ $1 -le 1 ]
    then
        echo $2
    else
        let prod=$2*$1
        let tmp=$1-1
        factorial $tmp $prod
    fi
}


function factorial2()
{
    if [ $1 -le 1 ]
    then
        return 1
    else
        let tmp=$1-1
        factorial2 $tmp
        let prod=$1*$?
        return $prod
    fi
}


if [ $# -ne 1 ]
then
    echo -n "nr="
    read nr
else
    nr=$1
fi

#factorial $nr 1

factorial2 $nr
echo $?
