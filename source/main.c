#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25
#define WIN 21

int racket_left = HEIGHT / 2;
int racket_right = HEIGHT / 2;
int ball_x = WIDTH / 2;
int ball_y = HEIGHT / 2;
int x_velocity = 1;
int y_velocity = 1;
int left_score = 0;
int right_score = 0;

void draw() {
  system("clear");
  printf("Score: %d : %d\n", left_score, right_score);

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {

      // Ball
      if (x == ball_x && y == ball_y) {
        putchar('O');
        continue;
      }
      if (x == 2 &&
          (y == racket_left - 1 || y == racket_left || y == racket_left + 1)) {
        putchar('|');
        continue;
      }

      if (x == WIDTH - 3 && (y == racket_right - 1 || y == racket_right || y == racket_right + 1)) {
        putchar('|');
        continue;
      }

      // Top/bottom border
      if (y == 0 || y == HEIGHT - 1) {
        putchar('-');
        continue;
      }

      putchar(' ');
    }
    putchar('\n');
  }
}
void update_ball() {
  ball_x = ball_x + x_velocity;
  ball_y = ball_y + y_velocity;

  if (ball_y <= 1 || ball_y >= HEIGHT - 2)
    y_velocity = -y_velocity;
  if (ball_x == 3 && ball_y >= racket_left - 1 && ball_y <= racket_left + 1)
    x_velocity = -x_velocity;
  if (ball_x == WIDTH - 4 && ball_y >= racket_right - 1 &&
      ball_y <= racket_right + 1)
    x_velocity = -x_velocity;

  if (ball_x <= 0) {
    right_score += 1;
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    x_velocity = 1;
    if (y_velocity > 0)
      y_velocity = 1;
    else
      y_velocity = -1;
  }
  if (ball_x >= WIDTH - 1) {
    right_score += 1;
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    x_velocity = -1;
    if (y_velocity > 0)
      y_velocity = 1;
    else
      y_velocity = -1;
  }
}
void move_left_racket(int d) {
  racket_left += d;
  if (racket_left < 2)
    racket_left = 2;
  if (racket_left > HEIGHT - 3)
    racket_left = HEIGHT - 3;
}
void move_right_racket(int d) {
  racket_right += d;
  if (racket_right < 2)
    racket_right = 2;
  if (racket_right > HEIGHT - 3)
    racket_right = HEIGHT - 3;
}

int main() {
  char c;
  draw();
  while (left_score < WIN && right_score < WIN) {
    printf("Move (A/Z for left, K/M for right, space_bar to skip: )");
    c = getchar();

    if (c == 'A' || c == 'a')
      move_left_racket(-1);
    if (c == 'Z' || c == 'z')
      move_left_racket(+1);
    if (c == 'K' || c == 'k')
      move_right_racket(-1);
    if (c == 'M' || c == 'm')
      move_right_racket(+1);

    if (c == 27)
      break;
    update_ball();
    draw();
  }

  if (racket_left == WIN)
    printf("Conratulations! Left Player WON!");
  else
    printf("Conratulations! Right Player WON!");

  return 0;
}
