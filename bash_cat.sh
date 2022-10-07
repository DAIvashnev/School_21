#!/bin/bash

IFS=$'\n'
count=1

while [ $count -gt 0 ]
do
./cat_21 $@ > my_test.txt
cat $@ > cat_test.txt
diff my_test.txt cat_test.txt
count=$(( $count - 1 ))
done