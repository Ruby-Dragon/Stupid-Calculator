#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "stdbool.h"

double out = 0.0f;
double op1 = 0.0f;
double op2 = 0.0f;

bool isInt(double num)
{
  return num == (double)((long long)(num));
}

double stupidAdd(double op1, double op2)
{
  double whole = 0.0f;
  double frac = modf(op2, &whole);

  double accum = op1;

  for (long long i = llabs((long long) whole); i > 0; i--)
  {
    if ((*(long long *) &whole) >> 63)
      accum--;
    else
      accum++;
  }

  accum += frac;
  return accum;
}

double stupidMult(double op1, double op2)
{
  double whole = 0.0f;
  double frac = modf(op2, &whole);

  double accum = op1;
  for (long long i = llabs((long long) whole) -1ll; i>0;i--)
  {
    accum = stupidAdd(accum, op1);
  }
  return stupidAdd(accum, op1 * frac);
}

double fastInvSqrt(double number)
{
  long long i;
  double x2, y;
  const double threeHalfs = 1.5f;

  x2 = number * 0.5f;
  y = number;
  i = *(long long *) &y;
  i = 0x5fe6ec85e7de30da - ( i >> 1 );
  y = * (double *) &i;
  y = y * (threeHalfs - (x2 * y * y));
  y = y * (threeHalfs - (x2 * y * y));
  
  return y;
}

void stupidPow()
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
  out = result;
}

void stupidDiv()
{
  double reciprocal = pow(fastInvSqrt(op2), 2.0f);
  
  out =  reciprocal * op1;
}

void stupidSub()
{
  long long i;
  double y = op2;

  i = *(long long *) &y;

  i = i ^ 0x8000000000000000; //i might be cooking

  y = *(double *) &i;

  out = stupidAdd(op1, y);
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

  op1 = atof(argv[1]);
  char operator = argv[2][0];
  op2 = atof(argv[3]);

  char possibleOps[] = {0x2B, 0x2D, 0x78, 0x2F, 0x5E};
  void *opLabels[] = {&&add, &&sub, &&mult, &&div, &&pow};

  for (int i = sizeof(possibleOps)-1; i >= 0; i--)
  {
    if (i <= -1)
    {
      goto error;
    }

    if ((operator ^ possibleOps[i]) == 0x00)
    {
      goto *opLabels[i];
    }
  }

error:
  printf("what on god's green earth did you type in?\n");
  return 1;

add:
  out = stupidAdd(op1, op2);
  goto print;
sub:
  stupidSub();
  goto print;
mult:
  out = stupidMult(op1, op2);
  goto print;
div:
  stupidDiv();
  goto print;
pow:
  if (isInt(op2))
  {
    stupidPow();
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
