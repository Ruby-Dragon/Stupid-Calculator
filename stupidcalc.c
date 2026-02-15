#include "stdio.h"
#include "math.h"
#include "stdlib.h"

int main()
{
  printf("Enter the first operand: ");

  float op1 = 0.0f;
  char in[60];
  scanf("%s", in);
  op1 = atof(in);

  printf("\nEnter the operator: ");

  char operator = '+';
  scanf("%s",in);
  operator = in[0];

  printf("\nEnter the second operand: ");

  float op2 = 0.0f;
  scanf("%s", in);
  op2 = atof(in);

  float out = 0.0f;

  switch(operator)
  {
    case '+':
      out = op1 + op2;
      break;
    case '-':
      out = op1 - op2;
      break;
    case '*':
      out = op1-op2;
      break;
    case '/':
      out = op1 / op2;
      break;
    case '^':
      out = pow(op1, op2);
      break;
    default:
      printf("what on god's green earth did you type in you utter lunatic?!?\n");
      return 0;
  }
  printf("%f\n", out);

  return 0;
}
