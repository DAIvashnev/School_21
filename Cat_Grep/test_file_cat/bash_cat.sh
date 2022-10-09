#!/bin/bash

IFS=$'\n'
count=1

while [ $count -gt 0 ]
do
    mkdir cat_test

    ./cat_21 $@ > cat_test/1-my_no_flags_test.txt
    cat $@ > cat_test/1-cat_no_flags_test.txt
    diff cat_test/1-my_no_flags_test.txt cat_test/1-cat_no_flags_test.txt

    ./cat_21 $@ -b > cat_test/2-b_test.txt
    cat $@ -b > cat_test/2-cat_b_test.txt
    diff cat_test/2-b_test.txt cat_test/2-cat_b_test.txt

    ./cat_21 $@ -n > cat_test/3-n_test.txt
    cat $@ -n > cat_test/3-cat_n_test.txt
    diff cat_test/3-n_test.txt cat_test/3-cat_n_test.txt

    ./cat_21 $@ -s > cat_test/4-s_test.txt
    cat $@ -s > cat_test/4-cat_s_test.txt
    diff cat_test/4-s_test.txt cat_test/4-cat_s_test.txt

    ./cat_21 $@ -e > cat_test/5-e_test.txt
    cat $@ -e > cat_test/5-cat_e_test.txt
    diff cat_test/5-e_test.txt cat_test/5-cat_e_test.txt

    ./cat_21 $@ -v > cat_test/6-v_test.txt
    cat $@ -v > cat_test/6-cat_v_test.txt
    diff cat_test/6-v_test.txt cat_test/6-cat_v_test.txt

    ./cat_21 $@ -t > cat_test/7-t_test.txt
    cat $@ -t > cat_test/7-cat_t_test.txt
    diff cat_test/7-t_test.txt cat_test/7-cat_t_test.txt
count=$(( $count - 1 ))
done