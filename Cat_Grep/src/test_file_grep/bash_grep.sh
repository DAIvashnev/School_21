#!/bin/bash

DIR="test_grep.txt"
DIR_EM="empty_file.txt"
F1="f.txt"
F2="ff.txt"
SUCCESS=0
FAIL=0

array=(-i -v -c -l -n -h -s -o)
arrayE=(-e)
arrayF=(-f)

mkdir grep_test

#ТЕСТ БЕЗ ОПЦИЙ
echo "Test no option in: s21_grep seven $DIR $DIR_EM $DIR "
./s21_grep seven $DIR $DIR_EM $DIR > grep_test/my_test.txt
grep seven $DIR $DIR_EM $DIR > grep_test/test.txt
NAME=$(diff grep_test/test.txt grep_test/test.txt)
if [[ -z $NAME ]]
then
    SUCCESS=$(($SUCCESS + 1))
    echo -e "SUCCESS\n" 
else
    FAIL=$(($FAIL + 1))
    echo -e "FAIL\n"
fi

#ТЕСТ С ОДНОЙ ОПЦИЕЙ
for item in ${array[*]}
do
    echo "Test $item option in: s21_grep seven $DIR $DIR_EM $DIR "
    ./s21_grep seven $item $DIR $DIR_EM $DIR > grep_test/my_test.txt
    grep seven $item $DIR $DIR_EM $DIR > grep_test/test.txt
    NAME=$(diff grep_test/test.txt grep_test/my_test.txt)
    if [[ -z $NAME ]]
    then
        SUCCESS=$(($SUCCESS + 1))
        echo -e "SUCCESS\n" 
    else
        FAIL=$(($FAIL + 1))
        echo -e "FAIL\n"
    fi
done

#ТЕСТ С ДВУМЯ ОПЦИЯМИ
for item in ${array[*]}
do
    for item2 in ${array[*]}
    do
        if [[ "$item" != "$item2" ]]
        then
            echo "Test $item $item2 option in: s21_grep seven $DIR $DIR_EM $DIR "
            ./s21_grep seven $item $item2 $DIR $DIR_EM $DIR > grep_test/my_test.txt
            grep seven $item $item2 $DIR $DIR_EM $DIR > grep_test/test.txt
            NAME=$(diff grep_test/test.txt grep_test/my_test.txt)
            if [[ -z $NAME ]]
            then
                SUCCESS=$(($SUCCESS + 1))
                echo -e "SUCCESS\n" 
            else
                FAIL=$(($FAIL + 1))
                echo -e "FAIL\n"
            fi
        fi
    done
done

#ТЕСТ С ДВУМЯ ОПЦИЯМИ (-е)
for item in ${arrayE[*]}
do
    for item2 in ${array[*]}
    do
        echo "Test $item \\^ $item ^h $item 3$ $DIR $DIR_EM $DIR $item 4\\$ $item2"
        ./s21_grep $item \\^ $item ^h $item 3$ $DIR $DIR_EM $DIR $item 4\\$ $item2 > grep_test/my_test.txt
        grep $item \\^ $item ^h $item 3$ $DIR $DIR_EM $DIR $item 4\\$ $item2 > grep_test/test.txt
        NAME=$(diff grep_test/test.txt grep_test/my_test.txt)
        if [[ -z $NAME ]]
        then
            SUCCESS=$(($SUCCESS + 1))
            echo -e "SUCCESS\n" 
        else
            FAIL=$(($FAIL + 1))
            echo -e "FAIL\n"
        fi
    done
done

#ТЕСТ С ДВУМЯ ОПЦИЯМИ (-f)
for item in ${arrayF[*]}
do
    for item2 in ${array[*]}
    do
        echo "Test $item $F1 $item $DIR_EM $item $F2 $DIR $DIR_EM $DIR $item $F1 $item2"
        ./s21_grep $item $F1 $item $DIR_EM $item $F2 $DIR $DIR_EM $DIR $item $F1 $item2 > grep_test/my_test.txt
        grep $item $F1 $item $DIR_EM $item $F2 $DIR $DIR_EM $DIR $item $F1 $item2 > grep_test/test.txt
        NAME=$(diff grep_test/test.txt grep_test/my_test.txt)
        if [[ -z $NAME ]]
        then
            SUCCESS=$(($SUCCESS + 1))
            echo -e "SUCCESS\n" 
        else
            FAIL=$(($FAIL + 1))
            echo -e "FAIL\n"
        fi
    done
done

#ТЕСТ С ДВУМЯ ОПЦИЯМИ (-e-f)
echo "Test -e-project -e \"Hello World ! ! !\" test_grep.txt empty_file.txt test_grep.txt -f ff.txt "
./s21_grep -e-project -e "Hello World ! ! !" test_grep.txt empty_file.txt test_grep.txt -f ff.txt > grep_test/my_test.txt
grep -e-project -e "Hello World ! ! !" test_grep.txt empty_file.txt test_grep.txt -f ff.txt > grep_test/test.txt
NAME=$(diff grep_test/test.txt grep_test/my_test.txt)
if [[ -z $NAME ]]
then
    SUCCESS=$(($SUCCESS + 1))
    echo -e "SUCCESS\n" 
else
    FAIL=$(($FAIL + 1))
    echo -e "FAIL\n"
fi

#ТЕСТ С ТРЕМЯ ОПЦИЯМИ (-e-f -*)
for item in ${array[*]}
do
    echo "Test -e-project -e \"Hello World ! ! !\" test_grep.txt empty_file.txt test_grep.txt -f ff.txt " $item
    ./s21_grep -e-project -e "Hello World ! ! !" test_grep.txt empty_file.txt test_grep.txt -f ff.txt $item > grep_test/my_test.txt
    grep -e-project -e "Hello World ! ! !" test_grep.txt empty_file.txt test_grep.txt -f ff.txt $item > grep_test/test.txt
    NAME=$(diff grep_test/test.txt grep_test/my_test.txt)
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

#ТЕСТЫ УТЕЧЕК
for item in ${array[*]}
do
    echo -e "\nTest $item option in: s21_grep seven $DIR $DIR_EM $DIR \n"
    valgrind ./s21_grep seven $item $DIR $DIR_EM $DIR > grep_test/valgrind.txt

done

valgrind ./s21_grep -e-project -e "Hello World ! ! !" test_grep.txt empty_file.txt test_grep.txt -f ff.txt -o

valgrind ./s21_grep -e \\^ -e ^h -e 3$ test_grep.txt empty_file.txt test_grep.txt -e 4\\$ -o

valgrind ./s21_grep -f f.txt -f empty_file.txt -f ff.txt test_grep.txt empty_file.txt test_grep.txt -f f.txt -o