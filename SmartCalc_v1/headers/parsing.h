#ifndef _SMART_CALC_PARSING_DATA_
#define _SMART_CALC_PARSING_DATA_

#include <math.h>
#include <stdio.h>

#include "stack.h"
#include "validation.h"

/**
 @brief Функия парсинга выражения в стек.
 @details в функции производится парсирование данных в два стека, символьный и
 числовой, с дальнейшим вычислением из них
 @param expression проверенное на валидность выражение
 @param x значение х для графика
 @return ответ на полученное выражение
*/
double isParsing(const char* expression, double x);

/**
 @brief Функия определяющая первый символ в названии фуннкции (sin, cos, ...)
 @param с символ из выражения
 @return 1/0 в случае найденног осовпадения/в случае неудачи
*/
int FirstCFun(char c);

/**
 @brief Функия вычисления основных операций. Работа калькулятора с данными из
 стека.
 @param с число из стека
 @param stack стек с числами
*/
void Calc(char c, Stack** stack);

/**
 @brief Функия вычисления операци с функциями (sin, cos, ...). Работа
 калькулятора с данными из стека.
 @param с первый символ названия функции
 @param stack стек с числами
*/
void CalcFunc(char c, Stack** stack);

/**
 @brief Функия конвертации названия функции (sin, cos, ...) в символ.
 @param function название функции
 @return символ определяющий функцию
*/
char getFun(char* function);

/**
 @brief Функия определения приоритета между операторами
 @param inС символ из выражения
 @param inSt символ из стека
 @return 1 в случае, если опертор из выражения имеет меньший или равный
 приоритет в сравнении с опреатором из стека. 0 в противном случае
*/
int checkPriority(char inC, char inSt);

/**
 @brief Функия определения приоритета оператора
 @param c оператор
 @return значение приоритета
*/
int getPriority(char c);

#endif  // _SMART_CALC_PARSING_DATA_