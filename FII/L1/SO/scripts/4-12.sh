#! /usr/bin/env bash


if [ $# -ne 1 ]
then
    echo "Usage: $0 LETTER"
    exit 1
fi


path="/etc/passwd"
letter=$1


for stud in $(cut $path -d : -f 1,4 | \
              grep -E "^$letter.+:202" | \
              cut -d : -f 1)
do
    dir="/fenrir/studs/$stud"

    if [ -f "$dir/html/index.htm" -o \
         -f "$dir/html/index.html" -o \
         -f "$dir/html/index.php" ]
    then
        echo $stud
    fi
done

