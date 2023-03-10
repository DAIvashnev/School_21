#include "headers/parsing.h"

double isParsing(const char *expression, double x) {
  Stack *num_st = NULL;
  Stack *char_st = NULL;
  char *chislo = calloc(strlen(expression), sizeof(char));
  int index = 0;
  int scoreNum = 0;
  char c;
  double res = 0;
  int chU = 0;
  while ((c = expression[index]) != '\0') {
    if (isX(c)) push_n(&num_st, x);
    if ((isOperation(c) || isPow(c) || c == 'm') && chU != 1 &&
        peek_c(char_st) != 'm') {
      chU = (checkUnar(expression[index + 1])) == 0 ? 0 : 1;
      if (peek_c(char_st) != '\0' && checkPriority(c, peek_c(char_st)) &&
          c != '^') {
        while (peek_c(char_st) != '\0' && checkPriority(c, peek_c(char_st))) {
          Calc(char_st->c, &num_st);
          pop_c(&char_st);
        }
        push_c(&char_st, c);
      } else if (index != 0 ||
                 (index == 0 && c == '-' && expression[index + 1] == '(')) {
        push_c(&char_st, c);
      }
    }
    if (isBracket(c)) {
      if (c == ')') {
        while (char_st != NULL && '(' != peek_c(char_st)) {
          Calc(char_st->c, &num_st);
          pop_c(&char_st);
        }
        pop_c(&char_st);
        if (getSize(char_st) && FirstCFun(peek_c(char_st))) {
          if (num_st->n < 0 && peek_c(char_st) == 'q') chU = -1;
          num_st->n *= chU == -1 ? -1 : 1;
          CalcFunc(char_st->c, &num_st);
          num_st->n *= chU == -1 ? -1 : 1;
          chU = 0;
          pop_c(&char_st);
        }
      } else {
        if (!(getSize(char_st) && FirstCFun(peek_c(char_st))))
          chU = (checkUnar(expression[index + 1])) == 0 ? 0 : 1;
        push_c(&char_st, c);
      }
    }
    if (FirstCFun(c)) {
      char func[5];
      int j = 0;
      while (expression[index] > 96) {
        func[j] = expression[index];
        index++;
        j++;
      }
      func[j] = '\0';
      index--;
      push_c(&char_st, getFun(func));
      memset(func, 0, 5);
    }
    if (isNum(c) || isPoint(c)) {
      scoreNum = (isNum(c) == 1 || isPoint(c) == 1) ? scoreNum : 0;
      chislo[scoreNum] = c;
      scoreNum++;
    }
    if (!(isNum(expression[index + 1]) || isPoint(expression[index + 1])) &&
        chislo[0] != 0) {
      chislo[scoreNum] = '\0';
      if (chU == -1 && expression[index + 1] != 'm') {
        push_n(&num_st, atof(chislo) * -1);
        if (expression[index - 1] == '+') num_st->n *= -1;
        chU = 0;
      } else {
        push_n(&num_st, atof(chislo));
        num_st->n *= (chU == -1 && expression[index - 1] != '+') ? -1 : 1;
      }
      scoreNum = 0;
      memset(chislo, 0, strlen(chislo));
    }
    if (chU == 1) {
      index++;
      chU = -1;
    }
    if (index == 0) chU = c == '-' ? -1 : 0;
    if (peek_c(char_st) == 'm' && c == '-') chU = -1;
    if (chU == -1 && expression[index + 1] == '-') {
      index += 2;
      chU = 0;
    } else
      index++;
  }
  while (char_st) {
    c = pop_c(&char_st);
    Calc(c, &num_st);
  }
  res = num_st->n;
  free(chislo);
  deletStack(char_st);
  deletStack(num_st);
  return res;
}

void Calc(char c, Stack **stack) {
  double n2 = pop_n(stack);
  double n1 = pop_n(stack);
  if (c == '+') push_n(stack, n1 + n2);
  if (c == '-') push_n(stack, n1 - n2);
  if (c == '*') push_n(stack, n1 * n2);
  if (c == '/') push_n(stack, n1 / n2);
  if (c == '^') push_n(stack, pow(n1, n2));
  if (c == 'm') {
    if (n1 < 0 && n2 > 0) {
      push_n(stack, n2 - fmod(n1 * -1, n2));
    } else if (n2 < 0 && n1 > 0) {
      push_n(stack, (n2 - fmod(n1 * -1, n2 * -1)));
    } else {
      push_n(stack, fmod(n1, n2));
    }
  }
}

void CalcFunc(char c, Stack **stack) {
  double n = pop_n(stack);
  if (c == 's') push_n(stack, sin(n));
  if (c == 'c') push_n(stack, cos(n));
  if (c == 't') push_n(stack, tan(n));
  if (c == 'S') push_n(stack, asin(n));
  if (c == 'C') push_n(stack, acos(n));
  if (c == 'T') push_n(stack, atan(n));
  if (c == 'l') push_n(stack, log(n));
  if (c == 'L') push_n(stack, log10(n));
  if (c == 'q') push_n(stack, sqrt(n));
}

int FirstCFun(char c) { return strchr("cstalSCTLq", c) == NULL ? 0 : 1; }

char getFun(char *function) {
  char c;
  if (!strcmp(function, "sin")) c = 's';
  if (!strcmp(function, "cos")) c = 'c';
  if (!strcmp(function, "tan")) c = 't';
  if (!strcmp(function, "asin")) c = 'S';
  if (!strcmp(function, "acos")) c = 'C';
  if (!strcmp(function, "atan")) c = 'T';
  if (!strcmp(function, "ln")) c = 'l';
  if (!strcmp(function, "log")) c = 'L';
  if (!strcmp(function, "sqrt")) c = 'q';
  return c;
}

int checkPriority(char inC, char inSt) {
  return getPriority(inC) <= getPriority(inSt);
}

int getPriority(char c) {
  int result = 0;
  if (c == 'm') result = 1;
  if (c == '*' || c == '/') result = 2;
  if (isPow(c)) result = 3;
  if (FirstCFun(c)) result = 4;
  if (isBracket(c)) result = -1;
  return result;
}
