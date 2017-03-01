#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#define DILATE 1.62

int main() {

  ////////////////SETUP////////////////
  screen s;
  clear_screen(s);

  color c;
  c.red = MAX_COLOR;
  c.green = 0;
  c.blue = 0;

  ////////////////Drawing images using one building block in a matrix and applying transformations////////////////
  printf("////////////////Drawing images using one building block in a matrix and applying transformations////////////////\n");
  struct matrix *edges;
  edges = new_matrix(4, 3);
  clear_matrix(edges);

  //building block is in matrix
  add_edge(edges, 10, 10, 0, 20, 20, 0);
  add_edge(edges, 10, 10, 0, 10, 20, 0);
  add_edge(edges, 10, 10, 0, 20, 10, 0);
  printf("Initial Edge Matrix\n");
  print_matrix(edges);

  //will be using scaling and rotation together
  struct matrix *ccw, *cw;
  ccw = new_matrix(4, 4); cw = new_matrix(4, 4);
  ccw->lastcol = cw->lastcol = 4;
  ident(ccw); ident(cw);

  double cosI = 40.0 / 41.0;
  double sinI = 9.0 / 41.0;
  double cos = 2 * cosI * cosI - 1;
  double sin = 2 * cosI * sinI;

  ccw->m[0][0] = cos; cw->m[0][0] = cos;
  ccw->m[1][0] = sin; cw->m[1][0] = -1 * sin;
  ccw->m[0][1] = -1 * sin; cw->m[0][1] = sin;
  ccw->m[1][1] = cos; cw->m[1][1] = cos;

  printf("Matrix for rotation by a small angle counter-clockwise:\n");
  print_matrix(ccw);

  printf("Matrix for rotation by a small angle clockwise:\n");
  print_matrix(cw);

  int count = 0;
  for(; count < 7; count++)
  {
    printf("//////////Iteration %d//////////\n", count + 1);

    printf("Draw figure in edge matrix: \n");
    print_matrix(edges); draw_lines(edges, s, c);

    printf("Rotate figure in edge matrix counter-clockwise around origin:\n");
    matrix_mult(ccw, edges); print_matrix(edges); draw_lines(edges, s, c);

    printf("Rotate figure in edge matrix clockwise around origin, twice:\n");
    matrix_mult(cw, edges); matrix_mult(cw, edges); print_matrix(edges); draw_lines(edges, s, c);

    printf("Bring figure back to center - symmetric w.r.t. y = x - by rotating figure counter-clockwise around origin:\n");
    matrix_mult(ccw, edges); print_matrix(edges);

    printf("Dilated figure in edge matrix (center at the origin) by a factor of %f:\n", DILATE);
    scalar_mult(DILATE, edges); print_matrix(edges);
  }

  free_matrix(edges);
  free_matrix(ccw);
  free_matrix(cw);

  /////////////////////////////////////////Just To Test Matrix Multiplication, Without Drawing/////////////////////////////////////////
  printf("/////////////////////////////////////////Just To Test Matrix Multiplication, Without Drawing/////////////////////////////////////////\n");
  struct matrix *test1, *test2;
  test1 = new_matrix(4, 4);
  clear_matrix(test1);

  test2 = new_matrix(4, 6);
  clear_matrix(test2);

  test1->lastcol = 4; test2->lastcol = 6;

  double **m1 = test1->m;
  m1[0][0] = 1; m1[0][1] = 29; m1[0][2] = 2; m1[0][3] = 3;
  m1[1][0] = 2; m1[1][1] = 36; m1[1][2] = 5; m1[1][3] = 8;
  m1[2][0] = -2; m1[2][1] = 56; m1[2][2] = 13; m1[2][3] = 21;
  m1[3][0] = -20; m1[3][1] = -21; m1[3][2] = 61; m1[3][3] = 88;

  double **m2 = test2->m;
  m2[0][0] = 1; m2[0][1] = 235; m2[0][2] = 111; m2[0][3] = 888; m2[0][4] = 999; m2[0][5] = 151;
  m2[1][0] = 144; m2[1][1] = 89; m2[1][2] = 188; m2[1][3] = 112; m2[1][4] = 295; m2[1][5] = 495;
  m2[2][0] = 55; m2[2][1] = 1024; m2[2][2] = 278; m2[2][3] = 95; m2[2][4] = 86; m2[2][5] = 88;
  m2[3][0] = 100; m2[3][1] = 109; m2[3][2] = 97; m2[3][3] = 120; m2[3][4] = 129; m2[3][5] = 136.5;

  printf("//////////////TEST1/////////////\n");
  print_matrix(test1);
  printf("//////////////TEST2/////////////\n");
  print_matrix(test2);
  printf("//////////////Product/////////////\n");
  matrix_mult(test1, test2); //gives correct result - confirmed with online matrix product calculator
  print_matrix(test2);

  free_matrix(test1);
  free_matrix(test2);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  display(s);
}  