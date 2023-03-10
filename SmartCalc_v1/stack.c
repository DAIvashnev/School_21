#include "headers/stack.h"

Stack *push_c(Stack **stack, char c) {
  Stack *value = malloc(sizeof(Stack));
  if (value == NULL) {
    exit(0);
  } else {
    value->next = *stack;
    value->c = c;
    *stack = value;
  }
  return value;
}

Stack *push_n(Stack **stack, double n) {
  Stack *value = malloc(sizeof(Stack));
  if (value == NULL) {
    exit(0);
  } else {
    value->next = *stack;
    value->n = n;
    *stack = value;
  }
  return value;
}

char pop_c(Stack **stack) {
  Stack *out;
  char c = '\0';
  if (*stack != NULL) {
    out = *stack;
    *stack = (*stack)->next;
    c = out->c;
    free(out);
  }
  return c;
}

double pop_n(Stack **stack) {
  Stack *out;
  double n = 0;
  if (*stack != NULL) {
    out = *stack;
    *stack = (*stack)->next;
    n = out->n;
    free(out);
  }
  return n;
}

char peek_c(const Stack *stack) { return stack != NULL ? stack->c : '\0'; }

size_t getSize(const Stack *stack) {
  size_t size = 0;
  while (stack) {
    size++;
    stack = stack->next;
  }
  return size;
}

void deletStack(Stack *stack) {
  Stack *tmp = stack;
  while (stack) {
    tmp = tmp->next;
    free(stack);
    stack = tmp;
  }
}
