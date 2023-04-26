#!/bin/bash

DIR_EM="empty_file.txt"
IFS=$'\n'
count=1
SUCCESS=0
FAIL=0
array=(-b -e -n -s -t)

mkdir cat_test

echo "Test no option in s21_cat $@ "
./s21_cat $@ > cat_test/my_test.txt
cat $@ > cat_test/test.txt
NAME=$(diff cat_test/my_test.txt cat_test/test.txt)
if [[ -z $NAME ]]
then
    SUCCESS=$(($SUCCESS + 1))
    echo -e "SUCCESS\n" 
else
    FAIL=$(($FAIL + 1))
    echo -e "FAIL\n"
fi

echo "Test empty_file in s21_cat $DIR_EM "
./s21_cat $DIR_EM > cat_test/my_test.txt
cat $DIR_EM > cat_test/test.txt
NAME=$(diff cat_test/my_test.txt cat_test/test.txt)
if [[ -z $NAME ]]
then
    SUCCESS=$(($SUCCESS + 1))
    echo -e "SUCCESS\n" 
else
    FAIL=$(($FAIL + 1))
    echo -e "FAIL\n"
fi

for item in ${array[*]}
do
    echo "Test $item option in s21_cat $@ "
    ./s21_cat $item $@ > cat_test/my_test.txt
    cat $item $@ > cat_test/test.txt
    NAME=$(diff cat_test/my_test.txt cat_test/test.txt)
    if [[ -z $NAME ]]
    then
        SUCCESS=$(($SUCCESS + 1))
        echo -e "SUCCESS\n" 
    else
        FAIL=$(($FAIL + 1))
        echo -e "FAIL\n" 
    fi
done

echo -e "\nSUCCESS" - $SUCCESS
echo -e "FAIL"    - $FAIL

echo -e "\n"
for item in ${array[*]}
do
    echo -e "\nTest $item option in s21_cat $@ \n"
    valgrind ./s21_cat $item $@ > cat_test/valgrind.txt
    echo -e "\n"
done