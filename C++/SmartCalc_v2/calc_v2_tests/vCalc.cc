#include "test.h"

TEST(Calc, test) {
  double x = 0;
  string expression[16] = {
      "2^(3+3)^2",
      "2+2*2^3",
      "1-3*-1+2/-2^3",
      "1+2*(3+4/2-1)",
      "6-2*3+(-5-2)",
      "1+2*(3+4/2-(1+2))*2+1",
      "2+2*-2-(4/7)",
      "2+2*-2-(4/7)+10*2/2-(55+-25)-(33+17)",
      "2+2*2+-2555",
      "1+2*(3+4/2-(1+2))*2+1*-1",
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))",
      "2+(2)*2^(3)",
      "(((5.43/4.0)^3)*4*((5/3)^4))-((5/(2^4))*4*4)",
      "1*10^-5",
      "1111111111111111111111111111111111111111111+1",
      "1111111111111111111111111+1111111111111111111111111"};
  double result[16] = {68719476736,
                       18,
                       3.75,
                       9,
                       -7,
                       11,
                       -2.571428571,
                       -72.571428571,
                       -2549,
                       8,
                       9.309278351,
                       18,
                       72.210169271,
                       0.00001,
                       1.1111111111111111e+42,
                       2.2222222222222222e+24};
  for (int i = 0; i < 16; i++) {
    s21::Controller controller;
    if (controller.InputNewExpression(expression[i])) {
      bool a = abs(controller.GetResult(expression[i], x) - (result[i]) < 1e-6);
      EXPECT_NEAR(controller.GetResult(expression[i], x), result[i], a);
    }
  }
}

TEST(Calc, mod) {
  double x = 0;
  string expression[10] = {"5mod4",
                           "-5mod4",
                           "5mod-4",
                           "-5mod-4",
                           "545+63-1*5+(-5mod2)",
                           "545+63-1*5+(5mod-2)",
                           "545+63-1*5+(5mod2)",
                           "545+63-1*5+(-5mod-2)",
                           "(-5mod-2)*2^(3+3)^2",
                           "((5mod2)*(4^2))+2-(4^(2-2))"};
  double result[10] = {1, 3, -3, -1, 604, 602, 604, 602, -68719476736, 17};
  for (int i = 0; i < 10; i++) {
    s21::Controller controller;
    if (controller.InputNewExpression(expression[i])) {
      bool a = abs(controller.GetResult(expression[i], x) - (result[i]) < 1e-6);
      EXPECT_NEAR(controller.GetResult(expression[i], x), result[i], a);
    }
  }
}

TEST(Calc, Func) {
  double x = 0;
  string expression[10] = {
      "-(4.01^-tan(81))",
      "545+63-1*tan(5)-sin(5+-4^2/2)-3/cos(2-1)",
      "-(3*(6000-(223.12/(2^(1+sqrt(16))))))",
      "(3*(6000-(223.12/(2^(1+sqrt(16))))))",
      "-1+((cos(1)^sqrt(1))/2.032)",
      "-1+((cos(1)^asin(1))/2.032)",
      "-1+((cos(1)^acos(1))/2.032)",
      "-1+((cos(1)^atan(1))/2.032)",
      "-1+((cos(1)^ln(1))/2.032)",
      "-1+((cos(1)^log(1))/2.032)",
  };
  double result[10] = {-3.084229, 604.986596, -17979.0825, 17979.0825,
                       -0.734103, -0.812887,  -0.507874,   -0.696548,
                       -0.507874, -0.507874};
  for (int i = 0; i < 10; i++) {
    s21::Controller controller;
    if (controller.InputNewExpression(expression[i])) {
      bool a = abs(controller.GetResult(expression[i], x) - (result[i]) < 1e-6);
      EXPECT_NEAR(controller.GetResult(expression[i], x), result[i], a);
    }
  }
}

TEST(Calc, x) {
  double x = 1;
  string expression[4] = {
      "tan(x)",
      "x+(x+x)+x+x+x*x/x^x",
      "sqrt(x)",
      "cos(x)^sqrt(x)/sin(x)",
  };
  double result[4] = {
      1.557407,
      6,
      1,
      0.642092,
  };
  for (int i = 0; i < 4; i++) {
    s21::Controller controller;
    if (controller.InputNewExpression(expression[i])) {
      bool a = abs(controller.GetResult(expression[i], x) - (result[i]) < 1e-6);
      EXPECT_NEAR(controller.GetResult(expression[i], x), result[i], a);
    }
  }
}