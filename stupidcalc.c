#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "stdbool.h"

bool isInt(double num)
{
  return num == (double)((long long)(num));
}


double stupidMult(double op1, double op2)
{
  double accum = op1;
  for (int i = op2 -1; i>0;i--)
  {
    accum += op1;
  }
  return accum;
}

double fastInvSqrt(double number)
{
  long long i;
  double x2, y;
  const float threeHalfs = 1.5f;

  x2 = number * 0.5f;
  y = number;
  i = *(long long *) &y;
  i = 0x5fe6ec85e7de30da - ( i >> 1 );
  y = * (double *) &i;
  y = y * (threeHalfs - (x2 * y * y));
  y = y * (threeHalfs - (x2 * y * y));
  
  return y;
}

double stupidPow(double op1, double op2)
{
  double result = op1;

 
  for (int i = op2 -1; i > 0; i--)
  {
    if (isInt(result))
    {
      result = stupidMult(result, op1);
    }
    else
    {
      result = result * op1;
    }
  }
  return result;
}

double stupidDiv(double op1, double op2)
{
  double reciprocal = pow(fastInvSqrt(op2), 2.0f);
  
  return reciprocal * op1;
}

void printNum(double num)
{
  if (isInt(num))
  {
    printf("%lli\n", (long long)num);
  }
  else
  {
    printf("%lf\n", num);
  }
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
  void *opLabels[] = {&&add, &&sub, &&mult, &&div, &&pow};

  for (int i = sizeof(possibleOps)-1; i >= 0; i--)
  {
    if (i <= -1)
    {
      printf("what on god's green earth did you type in?\n");
      break;
    }

    if ((operator ^ possibleOps[i]) == 0x00)
    {
      goto *opLabels[i];
    }
  }

add:
  out = op1 + op2;
  goto print;
sub:
  out = op1 - op2;
  goto print;
mult:
  if (isInt(op2))
  {
    out = stupidMult(op1, op2);
  }
  else
  {
    out = op1 * op2;
  }
  goto print;
div:
  out = stupidDiv(op1, op2);
  goto print;
pow:
  if (isInt(op2))
  {
    out = stupidPow(op1, op2);
  }
  else
  {
    out = pow(op1, op2);
  }
  goto print;

print:

  printNum(out);

  return 0;
}
