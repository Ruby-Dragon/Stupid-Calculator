#include "stdio.h"
#include "math.h"
#include "stdlib.h"

double stupidMult(double op1, double op2)
{
  double accum = op1;
  for (int i = op2 -1; i>0;i--)
  {
    accum += op1;
  }
  return accum;
}


int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    printf("Please enter (in the following order): \"operand1 operator operand2\" as arguments to this program\n");
    return 0;
  }

  double op1 = atof(argv[1]);
  char operator = argv[2][0];
  double op2 = atof(argv[3]);
  double out = 0.0f;

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
          out = stupidMult(op1, op2);
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

  if (-9223372036854775808.0 <= out && out < 9223372036854775808.0) {
    if( out == (double)((long long)(out)))
    {
      printf("%lli\n", (long long)out);
    }
    else
    {
      printf("%lf\n", out);
    }
  }

  return 0;
}
