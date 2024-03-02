#include "s21_SmartCalc.h"

int SmartCalc(char *input_str, double *res_num, double resX) {
  int status = 0;
  char str[256];
  if (!check_str(input_str, str)) {
    status = 1;
  } else {
    Stack *stack = NULL;
    Stack *Polish_Stack = NULL;
    inputStr_to_Stack(&stack, str);
    Polish_Stack = Stack_to_polsih(stack);
    Stack *curr = Polish_Stack;
    while (curr != NULL) {
      if (curr->type == s21_x) {
        curr->type = s21_num;
        curr->data = resX;
      }
      curr = curr->next;
    }
    *res_num = calculating(Polish_Stack);
    while (Polish_Stack != NULL) {
      pop(&Polish_Stack);
    }
  }
  return status;
}

// int main() {
//     char input_str[MAX_LENGTH];
//     strcpy(input_str, "2+2");
//     double res_num = 0;
//     double resX = 0;
//     int flag = SmartCalc(input_str, &res_num, resX);
//     printf("%lf\n", res_num);
//     printf("%d", flag);
//     return 0;
// }

void push(Stack **top, double data, int type, int priority) {
  Stack *new_node = (Stack *)malloc(sizeof(Stack));
  if (new_node != NULL) {
    new_node->data = data;
    new_node->type = type;
    new_node->priority = priority;
    new_node->next = *top;
    (*top) = new_node;
  }
}

double pop(Stack **top) {
  int status = OK;
  if (*top == NULL) {
    status = ERROR;
  }
  Stack *temp = *top;
  double data = temp->data;
  if (status == OK) {
    *top = (*top)->next;
    free(temp);
  }
  return data;
}

void stack_free(Stack **top) {
  int status = OK;
  Stack *current = *top;
  Stack *next = NULL;
  if (*top == NULL) {
    status = ERROR;
  }
  if (status == OK) {
    while (current != NULL) {
      next = current->next;
      free(current);
      current = next;
    }
  }
  *top = NULL;
}

void delete_space(char *input_str, char *str) {
  int j = 0;
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
    if (input_str[i] != ' ') {
      str[j++] = input_str[i];
    }
  }
  str[j] = '\0';
}

int check_brackets(char *str) {
  int status = OK;
  int open = 0;
  int close = 0;
  for (long unsigned int i = 0; i < strlen(str) && status == OK; i++) {
    if (str[i] == '(') {
      open++;
      if (str[i + 1] == ')') {
        status = ERROR;
      }
    }
    if (str[i] == ')') {
      close++;
      if (close > open) {
        status = ERROR;
      }
    }
  }
  if (open != close) {
    status = ERROR;
  }
  return status;
}

int check_dots(char *str) {
  int status = OK;
  for (long unsigned int i = 0; i < strlen(str) && status == OK; i++) {
    int dots = 0;
    if ((str[i] >= '0' && str[i] <= '9')) {
      while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
        if (str[i] == '.') {
          dots++;
        }
        i++;
      }
    }
    if (dots > 1) {
      status = ERROR;
    }
    if (str[i - 1] == '.') {
      status = ERROR;
    }
  }
  return status;
}

int check_binary(char *str) {
  int status = OK;
  for (long unsigned int i = 0; i < strlen(str) && status == OK; i++) {
    if (str[i] == '/' || str[i] == '*' || str[i] == '^' || str[i] == '%') {
      if (i == 0 || i == strlen(str) - 1) {
        status = ERROR;
      } else {
        if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
            str[i + 1] == '-' || str[i + 1] == '+' || str[i + 1] == ')' ||
            str[i + 1] == '%') {
          status = ERROR;
        }
        if (str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^' ||
            str[i - 1] == '-' || str[i - 1] == '+' || str[i - 1] == '(' ||
            str[i - 1] == '%') {
          status = ERROR;
        }
      }
    } else if (str[i] == '-' || str[i] == '+') {
      if (i == strlen(str) - 1)
        status = ERROR;
      else if (i != 0) {
        if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
            str[i + 1] == '-' || str[i + 1] == '+' || str[i + 1] == ')' ||
            str[i + 1] == '%') {
          status = ERROR;
        }
        if (str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^' ||
            str[i - 1] == '-' || str[i - 1] == '+' || str[i - 1] == '%') {
          status = ERROR;
        }
      } else {
        status = ERROR;
      }
    }
  }
  return status;
}

int check_unary(char *str) {
  int status = OK;
  for (long unsigned int i = 0; i < strlen(str) && status == OK; i++) {
    // cos sin tan log
    if (str[i] == 'c' || (str[i] == 's' && str[i + 2] == 'n') ||
        str[i] == 't' || (str[i] == 'l' && str[i + 2] == 'g')) {
      // if(i + 4 == ')') correct = ERROR;
      if (i != 0 &&
          (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'X')) {
        status = ERROR;
      }
      i += 2;
    }
    // asin atan acos sqrt
    else if (str[i] == 'a' || (str[i] == 's' && str[i + 3] == 't')) {
      if (i + 7 == ')') {
        status = ERROR;
      }
      if (i != 0 &&
          (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'X')) {
        status = ERROR;
      }
      i += 3;
    }
    // ln
    else if (str[i] == 'l' && str[i + 1] == 'n') {
      if (i + 3 == ')') status = ERROR;
      if (i != 0 &&
          (str[i - 1] == ')' || isdigit(str[i - 1]) || str[i - 1] == 'X')) {
        status = ERROR;
      }
      i++;
    } else if (isdigit((str[i])) &&
               (str[i + 1] == '(' || (str[i + 1] == 'X'))) {
      status = ERROR;
    } else if (str[i] == 'X' && (str[i + 1] == '(' || isdigit(str[i + 1]))) {
      status = ERROR;
    } else if ((str[i] == 'i' && str[i + 1] == 'n') ||
               (str[i] == 'n' && str[i + 1] == 'a') ||
               (str[i] == 'E' && str[i + 1] == 'R')) {
      status = ERROR;
    }
  }
  return status;
}

int check_operation(char *str) {
  int status = OK;
  if (!check_binary(str)) {
    status = ERROR;
  } else if (!check_unary(str)) {
    status = ERROR;
  }
  return status;
}

int check_str(char *input_str, char *str) {
  int status = OK;
  if (strlen(input_str) > 255) {
    status = ERROR;
  } else {
    delete_space(input_str, str);
    if (!check_brackets(str)) {
      status = ERROR;
    } else if (!check_dots(str)) {
      status = ERROR;
    } else if (!check_operation(str)) {
      status = ERROR;
    }
  }
  return status;
}

void Num_to_Stack(Stack **stack, char *str, long unsigned int *i) {
  char num[MAX_LENGTH] = {"\0"};
  for (int j = 0; isdigit(str[*i]) || str[*i] == '.'; j++) {
    num[j] = str[(*i)];
    (*i)++;
  }
  (*i)--;
  push(stack, atof(num), s21_num, NUM);
}

void Binary_to_Stack(Stack **stack, char *str, long unsigned int *i) {
  if (str[*i] == '^') {
    push(stack, 0, s21_pow, POW);
  } else if (str[*i] == '*') {
    push(stack, 0, s21_mult, BINARY_FIRST);
  } else if (str[*i] == '/') {
    push(stack, 0, s21_div, BINARY_FIRST);
  } else if (str[*i] == '%') {
    push(stack, 0, s21_mod, BINARY_FIRST);
  } else if (str[*i] == '+') {
    push(stack, 0, s21_plus, BINARY_SECOND);
  } else if (str[*i] == '-') {
    if (i == 0 || str[*i - 1] == '(') {
      push(stack, 0, s21_num, NUM);
    }
    push(stack, 0, s21_minus, BINARY_SECOND);
  }
}

void asin_atan_acos_sqrt_to_Stack(Stack **stack, char *str,
                                  long unsigned int *i) {
  if (str[*i] == 'a' && str[*i + 1] == 'c')
    push(stack, 0, s21_acos, UNARY);
  else if (str[*i] == 'a' && str[*i + 1] == 's')
    push(stack, 0, s21_asin, UNARY);
  else if (str[*i] == 'a' && str[*i + 1] == 't')
    push(stack, 0, s21_atan, UNARY);
  else if (str[*i] == 's' && str[*i + 1] == 'q')
    push(stack, 0, s21_sqrt, UNARY);
  i += 3;
}

void sin_tan_cos_log_to_Stack(Stack **stack, char *str, long unsigned int *i) {
  if (str[*i] == 'c')
    push(stack, 0, s21_cos, UNARY);
  else if (str[*i] == 's')
    push(stack, 0, s21_sin, UNARY);
  else if (str[*i] == 't')
    push(stack, 0, s21_tan, UNARY);
  else if (str[*i] == 'l')
    push(stack, 0, s21_log, UNARY);
  i += 2;
}

Stack *reverse_stack(Stack **stack) {
  Stack *new_stack = NULL;
  while (*stack != NULL) {
    push(&new_stack, (*stack)->data, (*stack)->type, (*stack)->priority);
    pop(stack);
  }
  if (*stack) {
    pop(stack);
  }
  return new_stack;
}

Stack *inputStr_to_Stack(Stack **stack, char *str) {
  for (long unsigned int i = 0; i < strlen(str); i++) {
    if (isdigit(str[i])) {
      Num_to_Stack(stack, str, &i);
    } else if (str[i] == 'X' || str[i] == 'x') {
      push(stack, 0, s21_x, NUM);
    } else if (str[i] == '(') {
      push(stack, 0, s21_open, BRACKETS);
    } else if (str[i] == ')') {
      push(stack, 0, s21_close, BRACKETS);
    } else if (str[i] == '^' || str[i] == '*' || str[i] == '/' ||
               str[i] == '%' || str[i] == '+' || str[i] == '-') {
      Binary_to_Stack(stack, str, &i);
    } else if (str[i] == 'a' || (str[i] == 's' && str[i + 3] == 't')) {
      asin_atan_acos_sqrt_to_Stack(stack, str, &i);
    } else if (str[i] == 'c' || (str[i] == 's' && str[i + 2] == 'n') ||
               str[i] == 't' || (str[i] == 'l' && str[i + 2] == 'g')) {
      sin_tan_cos_log_to_Stack(stack, str, &i);
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      push(stack, 0, s21_ln, UNARY);
    }
  }
  (*stack) = reverse_stack(stack);
  return (*stack);
}

Stack *Stack_to_polsih(Stack *stack) {
  Stack *polish_stack = NULL;
  Stack *sign = NULL;
  Stack *temp = stack;
  int priority_now = 10;
  while (temp != NULL) {
    if (temp->type == s21_num || temp->type == s21_x) {
      push(&polish_stack, temp->data, temp->type, temp->priority);
      pop(&stack);
    } else if (temp->priority < priority_now || temp->type == s21_open ||
               temp->type == s21_pow) {
      push(&sign, temp->data, temp->type, temp->priority);
      pop(&stack);
      priority_now = temp->priority;
    } else if (temp->type == s21_close || temp->priority >= priority_now) {
      if (temp->type == s21_close) {
        while (sign != NULL && sign->type != s21_open) {
          push(&polish_stack, sign->data, sign->type, sign->priority);
          pop(&sign);
        }
        pop(&sign);
        if (sign != NULL) {
          priority_now = sign->priority;
        }
      } else {
        while (sign != NULL && sign->priority <= temp->priority) {
          push(&polish_stack, sign->data, sign->type, sign->priority);
          pop(&sign);
        }
        priority_now = temp->priority;
        push(&sign, temp->data, temp->type, temp->priority);
      }
    }
    temp = temp->next;
  }
  while (stack != NULL) {
    pop(&stack);
  }
  temp = sign;
  while (temp != NULL) {
    push(&polish_stack, sign->data, sign->type, sign->priority);
    temp = temp->next;
    pop(&sign);
  }
  polish_stack = reverse_stack(&polish_stack);
  return polish_stack;
}

double calculating(Stack *stack) {
  Stack *temp = stack;
  Stack *result = NULL;
  while (temp != NULL) {
    if (temp->type == s21_num || temp->type == s21_x)
      push(&result, temp->data, temp->type, temp->priority);
    else if (temp->type >= s21_plus && temp->type <= s21_mod) {
      double var_1, var_2;
      if (result)
        var_1 = pop(&result);
      else
        break;
      if (result)
        var_2 = pop(&result);
      else
        break;
      if (temp->type == s21_plus)
        push(&result, var_2 + var_1, temp->type, temp->priority);
      else if (temp->type == s21_minus)
        push(&result, var_2 - var_1, temp->type, temp->priority);
      else if (temp->type == s21_mult)
        push(&result, var_2 * var_1, temp->type, temp->priority);
      else if (temp->type == s21_div)
        push(&result, var_2 / var_1, temp->type, temp->priority);
      else if (temp->type == s21_mod)
        push(&result, fmod(var_2, var_1), temp->type, temp->priority);
      else if (temp->type == s21_pow)
        push(&result, pow(var_2, var_1), temp->type, temp->priority);
    } else {
      double var;
      if (result)
        var = pop(&result);
      else
        break;
      if (temp->type == s21_cos)
        push(&result, cos(var), temp->type, temp->priority);
      else if (temp->type == s21_sin)
        push(&result, sin(var), temp->type, temp->priority);
      else if (temp->type == s21_tan)
        push(&result, tan(var), temp->type, temp->priority);
      else if (temp->type == s21_log)
        push(&result, log10(var), temp->type, temp->priority);
      else if (temp->type == s21_ln)
        push(&result, log(var), temp->type, temp->priority);
      else if (temp->type == s21_acos)
        push(&result, acos(var), temp->type, temp->priority);
      else if (temp->type == s21_atan)
        push(&result, atan(var), temp->type, temp->priority);
      else if (temp->type == s21_asin)
        push(&result, asin(var), temp->type, temp->priority);
      else if (temp->type == s21_sqrt)
        push(&result, sqrt(var), temp->type, temp->priority);
    }
    temp = temp->next;
  }
  double x = result->data;
  while (result != NULL) pop(&result);
  return (x);
}

void display(Stack **top) {
  if (*top == NULL) {
    printf("Стек пуст.\n");
    return;
  }
  Stack *temp = (*top);
  printf("Содержимое стека:\n");
  while (temp != NULL) {
    printf("Data: %.2lf, Type: %d, Priority: %d\n", temp->data, temp->type,
           temp->priority);
    temp = temp->next;
  }
}
