#!/bin/bash

IFS=$'\n'
count=1

while [ $count -gt 0 ]
do
    mkdir cat_test

    ./s21_cat $@ > cat_test/1-my_no_flags_test.txt
    cat $@ > cat_test/1-cat_no_flags_test.txt
    diff cat_test/1-my_no_flags_test.txt cat_test/1-cat_no_flags_test.txt

    ./s21_cat -b $@ > cat_test/2-b_test.txt
    cat -b $@ > cat_test/2-cat_b_test.txt
    diff cat_test/2-b_test.txt cat_test/2-cat_b_test.txt

    ./s21_cat -n $@ > cat_test/3-n_test.txt
    cat -n $@ > cat_test/3-cat_n_test.txt
    diff cat_test/3-n_test.txt cat_test/3-cat_n_test.txt

    ./s21_cat -s $@ > cat_test/4-s_test.txt
    cat -s $@ > cat_test/4-cat_s_test.txt
    diff cat_test/4-s_test.txt cat_test/4-cat_s_test.txt

    ./s21_cat -e $@ > cat_test/5-e_test.txt
    cat -e $@ > cat_test/5-cat_e_test.txt
    diff cat_test/5-e_test.txt cat_test/5-cat_e_test.txt

    ./s21_cat -v $@ > cat_test/6-v_test.txt
    cat -v $@ > cat_test/6-cat_v_test.txt
    diff cat_test/6-v_test.txt cat_test/6-cat_v_test.txt

    ./s21_cat -t $@ > cat_test/7-t_test.txt
    cat -t $@ > cat_test/7-cat_t_test.txt
    diff cat_test/7-t_test.txt cat_test/7-cat_t_test.txt

    ./s21_cat --number-nonblank $@ > cat_test/8---number-nonblank_test.txt
    cat --number-nonblank $@ > cat_test/8-cat_--number-nonblank_test.txt
    diff cat_test/8---number-nonblank_test.txt cat_test/8-cat_--number-nonblank_test.txt

    ./s21_cat --show-nonprinting $@ > cat_test/9---show-nonprinting_test.txt
    cat --show-nonprinting $@ > cat_test/9-cat_--show-nonprinting_test.txt
    diff cat_test/9---show-nonprinting_test.txt cat_test/9-cat_--show-nonprinting_test.txt

    ./s21_cat --show-ends $@ > cat_test/10---show-ends_test.txt
    cat --show-ends $@ > cat_test/10-cat_--show-ends_test.txt
    diff cat_test/10---show-ends_test.txt cat_test/10-cat_--show-ends_test.txt

    ./s21_cat --number $@ > cat_test/11---number_test.txt
    cat --number $@ > cat_test/11-cat_--number_test.txt
    diff cat_test/11---number_test.txt cat_test/11-cat_--number_test.txt

    ./s21_cat --squeeze-blank $@ > cat_test/12---squeeze-blank_test.txt
    cat --squeeze-blank $@ > cat_test/12-cat_--squeeze-blank_test.txt
    diff cat_test/12---squeeze-blank_test.txt cat_test/12-cat_--squeeze-blank_test.txt

    ./s21_cat --show-tabs $@ > cat_test/13---show-tabs_test.txt
    cat --show-tabs $@ > cat_test/13-cat_--show-tabs_test.txt
    diff cat_test/13---show-tabs_test.txt cat_test/13-cat_--show-tabs_test.txt

    ./s21_cat -E $@ > cat_test/14-E_test.txt
    cat -E $@ > cat_test/14-cat_E_test.txt
    diff cat_test/14-E_test.txt cat_test/14-cat_E_test.txt

    ./s21_cat -T $@ > cat_test/15-T_test.txt
    cat -T $@ > cat_test/15-cat_T_test.txt
    diff cat_test/15-T_test.txt cat_test/15-cat_T_test.txt
    
count=$(( $count - 1 ))
done