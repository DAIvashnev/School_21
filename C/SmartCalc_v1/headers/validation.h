#ifndef _SMART_CALC_VALIDATION_DATA_
#define _SMART_CALC_VALIDATION_DATA_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 @brief Структура для упрощения работы с данными, при их валидации
 @param index индексный счетчик для поступившей строки
 @param num строка с числами и 'x'
*/
typedef struct valid_s {
  int index;
  char *num;
} valid_t;

/**
 @brief Главная функция определения валидности выражения
 @details В функции агрегируются все посимвольные проверки.
 @param str строка с выражением
 @return 1/0 в случае успеха/неудачи
*/
int isValidation(const char *str);

/**
 @brief Функция проверки цифры
 @param str символ из строки
 @return 1/0 в случае успеха/неудачи
*/
int isNum(char c);

/**
 @brief Функция проверки точки
 @param str символ из строки
 @return 1/0 в случае успеха/неудачи
*/
int isPoint(char c);

/**
 @brief Функция проверки операторов +/-*
 @param str символ из строки
 @return 1/0 в случае успеха/неудачи
*/
int isOperation(char c);

/**
 @brief Функция проверки скобки
 @param str символ из строки
 @return 1/0 в случае успеха/неудачи
*/
int isBracket(char c);

/**
 @brief Функция проверки оператора возведения в степень
 @param str символ из строки
 @return 1/0 в случае успеха/неудачи
*/
int isPow(char c);

/**
 @brief Функция проверки х
 @param str символ из строки
 @return 1/0 в случае успеха/неудачи
*/
int isX(char c);

/**
 @brief Функция проверки оператора остатка от деления
 @param str выражение
 @param str индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int isMod(const char *str, valid_t *val);

/**
 @brief Функция проверки функции (sin, cos, ...)
 @param str выражение
 @param str индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int isFunc(const char *str, valid_t *val);

/**
 @brief Функция проверки валидности точки
 @param str выражение
 @param val индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int checkPoint(const char *str, valid_t *val);

/**
 @brief Функция проверки валидности операторов +/-*
 @param str выражение
 @param val индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int checkOperation(const char *str, valid_t *val);

/**
 @brief Функция проверки валидности скобок
 @param str выражение
 @param val индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int checkBracket(const char *str, valid_t *val);

/**
 @brief Функция проверки валидности оператора возведения в степень
 @param str выражение
 @param val индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int checkPow(const char *str, valid_t *val);

/**
 @brief Функция проверки валидности х
 @param str выражение
 @param val индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int checkX(const char *str, valid_t *val);

/**
 @brief Функция проверки валидности оператора остатка от деления
 @param str выражение
 @param val индекс строки
 @return 1/0 в случае успеха/неудачи
*/
int checkMod(const char *str, valid_t *val);

/**
 @brief Функция проверки валидности функции (sin, cos, ...)
 @param str выражение
 @param val индекс строки
 @param func переменная определяющая посимвольный размер функции
 @return 1/0 в случае успеха/неудачи
*/
int checkFunc(const char *str, valid_t *val, int *func);

/**
 @brief Функция проверки валидности унарного знака +-
 @param с символ для проверки
 @return 1/0 в случае успеха/неудачи
*/
int checkUnar(char c);

#endif  // _SMART_CALC_VALIDATION_DATA_