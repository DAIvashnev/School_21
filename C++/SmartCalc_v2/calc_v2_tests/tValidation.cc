#include "test.h"

TEST(Calc, tr) {
  string expression[20] = {
      "1+9-5+3",
      "-1+9-5+3",
      "1+9.5-5+3",
      "(1+(9.5-5)+3)",
      "((1+9.5))-(((5+3)))",
      "5^4+5^(4-4)",
      "(5^4)^2+2+4^2-2",
      "5*4+5*3^4",
      "(5*4)*(5*3)^4",
      "(5*4)^3*(5*3)^4",
      "(5/4)/(5/3)^4",
      "(5.43/4.0)^3*(5/3)^4-5/2^4*4",
      "tan(4)/atan(4)+cos(4)",
      "5-x*x+2-tan(4)/atan(x)+cos(4)+x/2",
      "100mod4*4+2^2/4mod2",
      "(55+66^8)/(5mod4)",
      "5mod4*5+(sin(4)/sqrt(3))+sin(4)*(atan(4)+4*cos(4))",
      "3^x+3/x",
      "x+(x)^x",
      "1-(-1)",
  };
  for (int i = 0; i < 20; i++) {
    s21::Controller controller;
    EXPECT_TRUE(controller.InputNewExpression(expression[i]));
  }
}

TEST(Calc, fl) {
  string expression[17] = {"55+66^8)/(5mod4)",
                           "5mod4(4)",
                           "(5/4)^3/(5/3/)^4",
                           "5*4*",
                           "tan4/atan(4)+4cos4",
                           "5*++4",
                           "5^^4",
                           "-5(+3)",
                           "5+6-)(5",
                           "(1+(9(.5)-5)+(-3))",
                           "5*5.",
                           "5*5.5.4",
                           "xx*6",
                           "x3",
                           "x+6*x+",
                           "(5+7)6*5",
                           "6mod-4"};
  for (int i = 0; i < 17; i++) {
    s21::Controller controller;
    EXPECT_FALSE(controller.InputNewExpression(expression[i]));
  }
}