#ifndef SRC_TESTS_UNIT_H
#define SRC_TESTS_UNIT_H

#include <check.h>

#include "../headers/parsing.h"

/**
 @brief функция тестов валидации
*/
Suite* suite_validation();

/**
 @brief функция тестов калькулятора
*/
Suite* suite_parsing();

#endif  //  SRC_TESTS_UNIT_H
