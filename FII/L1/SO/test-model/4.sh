#! /usr/bin/env bash

if [ $# -ne 1 ]
then
    echo "Usage: "$0" N"
    exit 1
else
    nr=$1
fi

# parameters ok

function func()
{
    if [ $1 -eq 0 ]
    then
        return 0
    elif [ $1 -eq 1 ]
    then
        return 1
    fi

    local a
    local b

    let a=$1-1
    let b=$1-2

    func $a
    let a=3*$?

    func $b
    let b=2*$?

    #echo $a $b

    return $(expr $a - $b)
}

func $nr
echo $?

exit 0


# in python
# f = lambda n: n if n in (0, 1) else 3*f(n-1) - 2*f(n-2)
