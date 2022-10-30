#!/bin/bash

IFS=$'\n'
count=1
cat=0;
grep=0;

read -p "1. - cat  or  2. - grep  or  3. - cat and grep ?  -->  " answer
case $answer in
1)  cat=$(( $cat + 1))
    make cat;;
2)  grep=$(( $grep + 1))
    make grep
esac

if [[ $cat -eq 1 ]]
then
while [ $count -gt 0 ]
do
./cat_21 $@
count=$(( $count - 1 ))
done
fi

if [[ $grep -eq 1 ]]
then
while [ $count -gt 0 ]
do
./grep_21
count=$(( $count - 1 ))
done
fi