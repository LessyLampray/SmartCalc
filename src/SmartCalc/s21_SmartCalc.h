#ifndef SMART_CALC_MAIN_H
#define SMART_CALC_MAIN_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
#define ERROR 0
#define OK 1

#define UNARY 0
#define POW 1
#define BINARY_FIRST 2
#define BINARY_SECOND 3
#define NUM 4
#define BRACKETS 4

typedef struct Stack {
  double data;
  int type;
  int priority;
  struct Stack *next;
} Stack;

typedef enum Operation {
  s21_num,
  s21_x,
  s21_open,
  s21_close,
  // бинарные
  s21_plus,
  s21_minus,
  s21_mult,
  s21_div,
  s21_pow,
  s21_mod,
  // унарные
  s21_cos,
  s21_sin,
  s21_tan,
  s21_acos,
  s21_asin,
  s21_atan,
  s21_sqrt,
  s21_log,
  s21_ln,
  s21_un_plus,
  s21_un_minus
} Operations;

void push(Stack **top, double data, int type, int priority);
double pop(Stack **top);
void stack_free(Stack **top);
void delete_space(char *input_str, char *str);
int check_brackets(char *str);
int check_dots(char *str);
int check_binary(char *str);
int check_unary(char *str);
int check_operation(char *str);
int check_str(char *input_str, char *str);
void Num_to_Stack(Stack **stack, char *str, long unsigned int *i);
void Binary_to_Stack(Stack **stack, char *str, long unsigned int *i);
void asin_atan_acos_sqrt_to_Stack(Stack **stack, char *str,
                                  long unsigned int *i);
void sin_tan_cos_log_to_Stack(Stack **stack, char *str, long unsigned int *i);
Stack *inputStr_to_Stack(Stack **stack, char *str);
Stack *reverse_stack(Stack **stack);
Stack *Stack_to_polsih(Stack *stack);
double calculating(Stack *stack);
int SmartCalc(char *input_str, double *res_num, double resX);

void display(Stack **top);
#endif  // SMART_CALC_MAIN_H
