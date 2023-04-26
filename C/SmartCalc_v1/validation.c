#include "headers/validation.h"

int isValidation(const char *str) {
  valid_t val;
  val.index = 0;
  val.num = "0123456789x";
  int result = 0;
  int status = 0;
  int func = 0;
  while (str != NULL && str[val.index] != '\0' && str[val.index] != ' ') {
    status += isNum(str[val.index]);
    status += (isPoint(str[val.index]) + checkPoint(str, &val));
    status += (isOperation(str[val.index]) + checkOperation(str, &val));
    status += (isBracket(str[val.index]) + checkBracket(str, &val));
    status += (isPow(str[val.index]) + checkPow(str, &val));
    status += (isX(str[val.index]) + checkX(str, &val));
    if (isMod(str, &val)) {
      status += checkMod(str, &val) + 3;
      val.index += 2;
    }
    func = isFunc(str, &val);
    if (func) {
      status += isNum(str[val.index - 1]);
      status += checkFunc(str, &val, &func) + func;
      val.index += func - 1;
    }
    val.index++;
  }
  result = (status == (int)strlen(str)) ? 1 : 0;
  return result;
}

int isNum(char c) { return c >= '0' && c <= '9'; }

int isPoint(char c) { return c == '.'; }

int isOperation(char c) { return strchr("+-*/", c) == NULL ? 0 : 1; }

int isBracket(char c) { return c == '(' || c == ')'; }

int isPow(char c) { return c == '^'; }

int isX(char c) { return c == 'x'; }

int isMod(const char *str, valid_t *val) {
  return strncmp("mod", str + val->index, 3) == 0 ? 1 : 0;
}

int isFunc(const char *str, valid_t *val) {
  int res = 0;
  char *functions[9] = {"sqrt", "cos",  "sin", "tan", "acos",
                        "asin", "atan", "ln",  "log"};
  for (int i = 0; i < 9 && res == 0; i++) {
    res = strncmp(functions[i], str + val->index, strlen(functions[i])) == 0
              ? strlen(functions[i])
              : 0;
  }
  return res;
}

int checkOperation(const char *str, valid_t *val) {
  int res = 0;
  int check = 0;
  int lenght = strlen(str);
  res = strchr("+-", str[val->index]) == NULL ? 0 : 1;
  if (res) {
    check +=
        val->index == 0 && ((str[val->index] != '+' && str[val->index] != '-'))
            ? 1
            : 0;
    check += val->index == lenght - 1 ? 1 : 0;
    if (strchr(val->num, str[val->index + 1]) == NULL) {
      if (str[val->index + 1] < 97 || str[val->index + 1] == 109) {
        check += str[val->index] == '-' && str[val->index + 1] == '-' &&
                         strchr(val->num, str[val->index + 2]) != NULL
                     ? 0
                     : 1;
        check += str[val->index] == '+' && str[val->index + 1] == '+' &&
                         strchr(val->num, str[val->index + 2]) != NULL
                     ? 1
                     : 0;
      }
    } else {
      check += (str[val->index] == '+' || str[val->index] == '-') &&
                       strchr(val->num, str[val->index + 1]) != NULL
                   ? 0
                   : 1;
    }
    check -= (str[val->index] == '+' || str[val->index] == '-') &&
                     str[val->index + 1] == '('
                 ? 1
                 : 0;
    res = check;
  }
  if (strchr("*/", str[val->index]) != NULL) {
    check += val->index == 0 ? 1 : 0;
    check += val->index == lenght - 1 ? 1 : 0;
    check += str[val->index] == '/' && str[val->index + 1] == '0' ? 1 : 0;
    check += strchr("/*)", str[val->index + 1]) != NULL ||
                     strchr("/*(", str[val->index - 1]) != NULL
                 ? 1
                 : 0;
    res = check;
  }
  return res;
}

int checkPoint(const char *str, valid_t *val) {
  int res = 0;
  int check = 0;
  int lenght = strlen(str);
  int i = val->index + 1, j = 0;
  char ch[256] = {0};
  res = strchr(".", str[val->index]) == NULL ? 0 : 1;
  if (res) {
    check += val->index == 0 || val->index == lenght - 1 ? 1 : 0;
    check += strchr(val->num, str[val->index + 1]) != NULL &&
                     strchr(val->num, str[val->index - 1]) != NULL
                 ? 0
                 : 1;
    while (str[i] != '\0' && check == 0) {
      if (str[i] == '.') {
        check += strpbrk(ch, "+-/*()") == NULL ? 1 : 0;
      }
      ch[j] = str[i];
      j++;
      i++;
    }
    res = check;
    ch[0] = '\0';
  }
  return res;
}

int checkBracket(const char *str, valid_t *val) {
  int res = 0;
  int check = 0;
  int lenght = strlen(str);
  res = strchr("()", str[val->index]) == NULL ? 0 : 1;
  if (res) {
    check += val->index == 0 && str[val->index] == ')' ? 1 : 0;
    check += val->index == lenght - 1 && str[val->index] == '(' ? 1 : 0;
    check += str[val->index] == '(' && str[val->index + 1] == ')' ? 1 : 0;
    check += str[val->index] == '(' && str[val->index - 1] == '+' &&
                     strchr("/*", str[val->index - 2]) != NULL
                 ? 1
                 : 0;
    check += val->index != 0 && str[val->index] == '(' &&
                     strchr(val->num, str[val->index - 1]) != NULL
                 ? 1
                 : 0;
    if (check == 0) {
      int i = 0;
      int open = 0, close = 0;
      while (str[i] != '\0') {
        open += str[i] == '(' ? 1 : 0;
        close += str[i] == ')' ? 1 : 0;
        i++;
      }
      check = open == close ? 0 : 1;
    }
    res = check;
  }
  return res;
}

int checkPow(const char *str, valid_t *val) {
  int res = 0;
  int check = 0;
  int lenght = strlen(str);
  res = strchr("^", str[val->index]) == NULL ? 0 : 1;
  if (res) {
    check += val->index == 0 || val->index == lenght - 1 ? 1 : 0;
    check += str[val->index + 1] == '^' || str[val->index - 1] == '^' ? 1 : 0;
    check += str[val->index + 1] == '+' ? 1 : 0;
    check += str[val->index - 1] == '(' ? 1 : 0;
    res = check;
  }
  return res;
}

int checkMod(const char *str, valid_t *val) {
  int res = 0;
  int check = 0;
  res = strncmp("mod", str + val->index, 3) == 0 ? 1 : 0;
  if (res) {
    check += val->index == 0 || val->index + 2 == (int)strlen(str) - 1 ? 1 : 0;
    res = check;
  }
  return res;
}

int checkFunc(const char *str, valid_t *val, int *func) {
  int res = 0;
  int check = 0;
  check += val->index + res == (int)strlen(str) ? 1 : 0;
  check += strchr("+-/*)", str[val->index + *func]) == NULL ? 0 : 1;
  check += str[val->index + *func] == '(' ? 0 : 1;
  res = check;
  return res;
}

int checkX(const char *str, valid_t *val) {
  int res = 0;
  int check = 0;
  res = isX(str[val->index]);
  if (res) {
    check += (isNum(str[val->index + 1]) + isNum(str[val->index - 1]));
    check += (isX(str[val->index + 1]) + isX(str[val->index - 1]));
    check += (isPoint(str[val->index + 1]) + isPoint(str[val->index - 1]));
    check += (isPoint(str[val->index + 1]) + isPoint(str[val->index - 1]));
    res = check;
  }
  return res;
}

int checkUnar(char c) { return strchr("+-", c) == NULL ? 0 : 1; }
