#include "model.h"

namespace s21 {
void Model::InputNewExpression(string expression) noexcept {
  expression_ = move(expression);
  lenExp_ = expression_.size();
  status_ = true;
}

void Model::validation() noexcept {
  status_ = vLen();
  if (status_) status_ = vData();
  if (status_) status_ = vBrackets();
  if (status_) status_ = vOperation();
  if (status_) status_ = vNumber();
  if (status_) status_ = vMod();
  if (status_) status_ = vFunc();
}

bool Model::vLen() const noexcept { return lenExp_ <= 255; }

bool Model::vData() noexcept {
  string inputData = ".0123456789x()+-*/^%~acgilnoqrstmd";
  for (char c : expression_) {
    if (inputData.find(c) == string::npos) status_ = false;
  }
  return status_;
}

bool Model::vBrackets() noexcept {
  stack<char> checkEquilBracket;
  string checkCorrect[4] = {".)0123456789x", ".)+-*/^%", ".(+-*/^%",
                            ".(0123456789xcstal"};

  if (expression_[0] == '(') checkEquilBracket.push(')');

  for (int i = 1; i < lenExp_ && status_; i++) {
    if (expression_[i] == '(') {
      if (checkCorrect[0].find(expression_[i - 1]) != string::npos)
        status_ = false;
      if (checkCorrect[1].find(expression_[i + 1]) != string::npos && expression_[i + 1] != '-')
        status_ = false;
      checkEquilBracket.push(')');
    }
    if (expression_[i] == ')') {
      if (checkCorrect[2].find(expression_[i - 1]) != string::npos)
        status_ = false;
      if (checkCorrect[3].find(expression_[i + 1]) != string::npos)
        status_ = false;
      if (checkEquilBracket.empty() ||
          checkEquilBracket.top() != expression_[i]) {
        status_ = false;
        break;
      }
      checkEquilBracket.pop();
    }
  }

  if (!checkEquilBracket.empty()) status_ = false;
  return status_;
}

bool Model::vOperation() noexcept {
  string operation = "+-/*^%~";
  //string checkCorrect = "0123456789(";
  for (int i = 0; i < lenExp_ && status_; i++) {
    if (operation.find(expression_[i]) != string::npos && i + 1 == lenExp_)
      status_ = false;

    if (operation.find(expression_[i]) != string::npos && i == 0 &&
        expression_[i] != '-')
      status_ = false;

    if (operation.find(expression_[i]) != string::npos &&
        operation.find(expression_[i + 1]) != string::npos)
      status_ = false;

    if (expression_[i] == '/' && expression_[i + 1] == '0') status_ = false;
  }
  return status_;
}

bool Model::vNumber() noexcept {
  string checkCorrect[4] = {")x", "(xcstal", "x)0123456789",
                            "(0123456789cstal"};

  for (int i = 0; i < lenExp_ && status_; i++) {
    if (IsDigit(expression_[i])) {
      if (i != 0 && checkCorrect[0].find(expression_[i - 1]) != string::npos)
        status_ = false;
      if (expression_[i + 1] != '\0' &&
          checkCorrect[1].find(expression_[i + 1]) != string::npos)
        status_ = false;
    } else if (expression_[i] == 'x') {
      if (i != 0 && checkCorrect[2].find(expression_[i - 1]) != string::npos)
        status_ = false;
      if (expression_[i + 1] != '\0' &&
          checkCorrect[3].find(expression_[i + 1]) != string::npos)
        status_ = false;
    }
  }

  for (int i = 0, countPoint = 0; i < lenExp_; i++) {
    if (expression_[i] == '.') countPoint++;
    if (countPoint > 1 || (expression_[i] == '.' && i + 1 == lenExp_)) {
      status_ = false;
      break;
    }
    if (!IsDigit(expression_[i]) && expression_[i] != '.') countPoint = 0;
  }
  return status_;
}

bool Model::vMod() noexcept {
  string checkCorrect = "0123456789";
  size_t it = expression_.find("mod");
  while (it != string::npos) {
    if (checkCorrect.find(expression_[it - 1]) == string::npos ||
        checkCorrect.find(expression_[it + 3]) == string::npos) {
      status_ = false;
      break;
    }
    it = expression_.find("mod", it + 3);
  }
  return status_;
}

bool Model::vFunc() noexcept {
  string funcs[10] = {"cos(",  "sin(",  "tan(", "acos(", "asin(",
                      "atan(", "sqrt(", "ln(",  "log(",  "mod"};
  string checkCorrect = "acgilnoqrst(md";
  string funcName;
  int funcIn = 0;

  for (int i = 0; i < lenExp_ && status_; i++) {
    while (checkCorrect.find(expression_[i]) != string::npos) {
      if (funcIn >= 6) {
        status_ = false;
        break;
      }
      funcName += expression_[i];
      if (funcName[funcIn] == '(') break;
      funcIn++;
      i++;
    }

    if (funcName[0] != '\0' && funcName[0] != '(') {
      for (int j = 0; j < 10 && funcName[0] != '\0'; j++) {
        status_ = false;
        if (!funcName.compare(funcs[j])) {
          status_ = true;
          break;
        }
      }
    }

    funcName.clear();
    funcIn = 0;
  }
  return status_;
}

double Model::parser(string ch, double x) {
  x_ = x;
  Stack stack;
  for (size_t i = 0; i < ch.length(); i++) {
    if (ch[i] == '\n') break;
    if (ch[i] == ' ') {
      continue;
    }
    if (ch[i] == 'x') {
      stack.Stack_n.push(x_);
      continue;
    }
    if (i == 0 && ch[i] == '-') {
      unarFlag = 1;
      continue;
    }

    if (strchr("acgilnoqrst", ch[i])) {
      while (strchr("acgilnoqrst", ch[i])) {
        tmp += ch[i];
        i++;
      }
      i--;
      stack.Stack_o.push(getFunc());
      tmp.clear();
      continue;
    }

    if (strchr("0123456789.", ch[i])) {
      do {
        tmp += ch[i];
        i++;
      } while (!strchr("+-*/~^%()m", ch[i]));
      if (strchr("+-*/~^%()m", ch[i])) i--;
      if (unarFlag) {
        double un = stod(tmp);
        stack.Stack_n.push(un * (-1.0));
        unarFlag = 0;
      } else {
        stack.Stack_n.push(stod(tmp));
      }
      tmp.clear();
    }

    if (strchr("+-*/^m", ch[i])) {
      if (ch[i] == 'm') {
        stack.Stack_o.push(ch[i]);
        i += 2;
        continue;
      }
      if (ch[i] == '-' && strchr("+-*/^%(d", ch[i - 1])) {
        unarFlag = 1;
        continue;
      }
      if (stack.Stack_o.size() == 0 ||
          !(getRang(ch[i]) <= getRang(stack.Stack_o.top()))) {
        stack.Stack_o.push(ch[i]);
      } else {
        if (stack.Stack_o.top() != '^') {
          calculate(stack.Stack_n, stack.Stack_o);
          while (stack.Stack_o.size() != 0 &&
                 getRang(ch[i]) <= getRang(stack.Stack_o.top()) &&
                 stack.Stack_o.top() != '(') {
            calculate(stack.Stack_n, stack.Stack_o);
          }
        }
        stack.Stack_o.push(ch[i]);
      }
    }

    if (ch[i] == '(') {
      stack.Stack_o.push(ch[i]);
    }
    if (ch[i] == ')') {
      while (stack.Stack_o.top() != '(') {
        calculate(stack.Stack_n, stack.Stack_o);
      }
      stack.Stack_o.pop();
      if (stack.Stack_o.size() != 0 &&
          strchr("acgilnoqrstSCLT", stack.Stack_o.top())) {
        calculateFunc(stack.Stack_n, stack.Stack_o);
      }
    }
  }

  while (stack.Stack_o.size() != 0) {
    calculate(stack.Stack_n, stack.Stack_o);
  }

  return stack.Stack_n.top();
}

void Model::calculate(stack<double> &Stack_n, stack<char> &Stack_o) {
  double a = Stack_n.top();
  Stack_n.pop();
  double b = Stack_n.top();
  Stack_n.pop();
  switch (Stack_o.top()) {
    case '+':
      Stack_n.push(a + b);
      break;
    case '-':
      Stack_n.push(b - a);
      break;
    case '^':
      if (b < 0) {
        double tmp = pow(b * (-1.), a);
        Stack_n.push(tmp * -1.);
      } else
        Stack_n.push(pow(b, a));
      break;
    case '*':
      Stack_n.push(a * b);
      break;
    case '/':
      Stack_n.push(b / a);
      break;
    case 'm':
      if (b < 0 && a > 0) {
        Stack_n.push(a - fmod(b * -1, a));
      } else if (a < 0 && b > 0) {
        Stack_n.push(a - fmod(b * -1, a * -1));
      } else {
        Stack_n.push(fmod(b, a));
      }
      break;
    default:
      cerr << "ERROR\n";
  }
  Stack_o.pop();
}

void Model::calculateFunc(stack<double> &Stack_n, stack<char> &Stack_o) {
  double n = Stack_n.top();
  Stack_n.pop();
  switch (Stack_o.top()) {
    case 's':
      Stack_n.push(sin(n));
      break;
    case 'c':
      Stack_n.push(cos(n));
      break;
    case 't':
      Stack_n.push(tan(n));
      break;
    case 'S':
      if (n <= 1 && n >= -1)
        Stack_n.push(asin(n));
      else {
        cerr << "ERROR\n";
      }
      break;
    case 'C':
      if (n <= 1 && n >= -1)
        Stack_n.push(acos(n));
      else {
        cerr << "ERROR\n";
      }
      break;
    case 'T':
      Stack_n.push(atan(n));
      break;
    case 'l':
      Stack_n.push(log(n));
      break;
    case 'L':
      Stack_n.push(log10(n));
      break;
    case 'q':
      if (n >= 0)
        Stack_n.push(sqrt(n));
      else {
        cerr << "ERROR\n";
      }
      break;
    default:
      cerr << "ERROR\n";
  }
  Stack_o.pop();
}

int Model::getRang(char c) noexcept {
  auto res = operation.find(c);
  return res->second;
}

char Model::getFunc() noexcept {
  auto res = func.find(tmp);
  return res->second;
}

bool Model::IsDigit(char ch) const noexcept { return ch >= '0' && ch <= '9'; }
bool Model::getStatus() const noexcept { return status_; }

};  // namespace s21