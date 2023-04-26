#include <stdio.h>

void playing_field(int ball_x, int ball_y, int play_1y, int play_2y, int scr_1,
                   int scr_2) {
  char c_long = '_';
  char c_width = '|';
  char f_ball = '*';
  char low_long = '-';
  printf("\n\n                                  Game Ping-Pong\n\n");
  printf("                  A - Up;                                 K - Up;\n");
  printf("                  Z - Down;                               M - "
         "Down;\n\n");
  printf("            Score Player - One                       Score Player - "
         "Two\n\n");
  printf("                    %d                                       %d\n\n",
         scr_1, scr_2);
  if (scr_1 == 21) {
    printf("\n\n                CONGRATULATIONS! - PLAYER - ONE, YOU WIN ! ! ! "
           "                           \n\n");
  } else if (scr_2 == 21) {
    printf("\n\n                CONGRATULATIONS! - PLAYER - TWO, YOU WIN ! ! ! "
           "                           \n\n");
  }
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 80; j++) {
      if (i == ball_y && j == ball_x) {
        printf("%c", f_ball);
      } else if (i == 0) {
        printf("%c", c_long);
      } else if (i == 25 - 1) {
        printf("%c", low_long);
      } else if ((j == 0 || j == 80 - 1 || j == (80 / 2))) {
        printf("%c", c_width);
      } else if ((i == play_1y && j == 1) || (i == play_1y + 1 && j == 1) ||
                 (i == play_1y + 2 && j == 1)) {
        printf("%c", c_width);
      } else if ((i == play_2y && j == 78) || (i == play_2y + 1 && j == 78) ||
                 (i == play_2y + 2 && j == 78)) {
        printf("%c", c_width);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void dinamic_ball(void) {
  int ball_x = 40;
  int ball_y = 13;
  int play_1y = 12;
  int play_2y = 12;
  int scr_1 = 0;
  int scr_2 = 0;
  int vec_x = 1;
  int vec_y = -1;
  int speed = 1;
  while (scr_1 < 21 && scr_2 < 21) {
    playing_field(ball_x, ball_y, play_1y, play_2y, scr_1, scr_2);
    char check;
    check = getchar();
    if ((check == 'A' || check == 'a') && play_1y != 1) {
      play_1y -= 1;
    } else if ((check == 'Z' || check == 'z') && play_1y != 21) {
      play_1y += 1;
    } else if ((check == 'K' || check == 'k') && play_2y != 1) {
      play_2y -= 1;
    } else if ((check == 'M' || check == 'm') && play_2y != 21) {
      play_2y += 1;
    } else if (check != ' ') {
      continue;
    }
    if (ball_x < 3 && ball_y != play_1y && ball_y != play_1y + 1 &&
        ball_y != play_1y + 2) {
      ball_x = 41;
      ball_y = 13;
      vec_x = -1;
      vec_y = 1;
      play_1y = 12;
      play_2y = 12;
      scr_2++;
    }
    if (ball_x > 76 && ball_y != play_2y && ball_y != play_2y + 1 &&
        ball_y != play_2y + 2) {
      ball_x = 39;
      ball_y = 13;
      vec_x = 1;
      vec_y = -1;
      play_1y = 12;
      play_2y = 12;
      scr_1++;
    }
    if (ball_y == 1) {
      vec_y = 1;
    }
    if (ball_y == 23) {
      vec_y = -1;
    }
    if (ball_x == 77) {
      vec_x = -1;
    }
    if (ball_x == 2) {
      vec_x = 1;
    }
    if (vec_y == -1) {
      ball_y -= speed;
    }
    if (vec_y == 1) {
      ball_y += speed;
    }
    if (vec_x == 1) {
      ball_x += speed;
    }
    if (vec_x == -1) {
      ball_x -= speed;
    }
    if (scr_1 == 21) {
      playing_field(ball_x, ball_y, play_1y, play_2y, scr_1, scr_2);
    } else if (scr_2 == 21) {
      playing_field(ball_x, ball_y, play_1y, play_2y, scr_1, scr_2);
    }
  }
}

int main() {
  dinamic_ball();
  return 0;
}
