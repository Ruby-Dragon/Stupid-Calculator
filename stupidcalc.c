#include "stdio.h"
#include "math.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    printf("Please enter (in the following order): \"operand1 operator operand2\" as arguments to this program\n");
    return 0;
  }

  float op1 = atof(argv[1]);
  char operator = argv[2][0];
  float op2 = atof(argv[3]);

  /*
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
  */

  float out = 0.0f;

  char possibleOps[] = {0x2B, 0x2D, 0x2A, 0x2F, 0x5E};

  for (int i = sizeof(possibleOps)-1; i >= 0; i--)
  {
    if (i <= -1)
    {
      printf("what on god's green earth did you type in?\n");
      break;
    }

    if ((operator ^ possibleOps[i]) == 0x00)
    {
      switch(i)
      {
        case 4:
          out = pow(op1, op2);
          break;
        case 3:
          out = op1/op2;
          break;
        case 2:
          out = op1 * op2;
          break;
        case 1:
          out = op1 - op2;
          break;
        case 0:
          out = op1 + op2;
          break;
      }
    }
  }

  printf("%f\n", out);

  return 0;
}
