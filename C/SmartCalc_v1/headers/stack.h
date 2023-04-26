#ifndef _SMART_CALC_STACK_DATA_
#define _SMART_CALC_STACK_DATA_

#include <stdio.h>
#include <stdlib.h>

/**
 @brief Структура стека
 @details Структура необходима для парсирования введенных данных.
 @param c символ оператора
 @param d числовое значение
 @param next указатель на следующий узел стека
*/
typedef struct Stack {
  char c;
  double n;
  struct Stack *next;
} Stack;

/**
 @brief Функция добавления символа в новый элемент стека
 @param c символ оператора
 @return указатель на стек
*/
Stack *push_c(Stack **stack, char c);

/**
 @brief Функция добавления числового значения в новый элемент стека
 @param n числовое значение
 @return указатель на стек
*/
Stack *push_n(Stack **stack, double n);

/**
 @brief Функция получения символа из вершины стека. Вершина стека удаляется
 @param stack указатель на стек
 @return символ оператора
*/
char pop_c(Stack **stack);

/**
 @brief Функция получения числа из вершины стека. Вершина стека удаляется
 @param stack указатель на стек
 @return число
*/
double pop_n(Stack **stack);

/**
 @brief Функция получения символа из вершины стека. Вершина стека сохраняется
 @param stack указатель на стек
 @return символ
*/
char peek_c(const Stack *stack);

/**
 @brief Функция получения количества узлов стека
 @param stack указатель на стек
 @return размер стека
*/
size_t getSize(const Stack *stack);

/**
 @brief Функция для удаления стека
 @param stack указатель на стек
*/
void deletStack(Stack *stack);

#endif  // _SMART_CALC_STACK_DATA_